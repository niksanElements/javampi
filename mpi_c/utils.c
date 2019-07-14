#include "utils.h"
#include "jni_mpi.h"

#include <malloc.h>

void jni_mpi_convert_MPI_Status(
    JNIEnv *env,
    jobject obj,
    MPI_Status* status,
    jni_mpi_convert_MPI_Status_flag flag)
{
    if(flag == FROM_JAVA_MPI_STATUS_TO_MPI_STATUS){
        status->count_lo = 
            (*env)->GetIntField(env,obj,JNI_MPI_STATUS_COUNT_LO);
        status->count_hi_and_cancelled = 
            (*env)->GetIntField(env,obj,JNI_MPI_STATUS_COUNT_HI);
        status->MPI_ERROR = 
            (*env)->GetIntField(env,obj,JNI_MPI_STATUS_MPI_ERROR);
        status->MPI_SOURCE = 
            (*env)->GetIntField(env,obj,JNI_MPI_STATUS_MPI_SOURCE);
        status->MPI_TAG = 
            (*env)->GetIntField(env,obj,JNI_MPI_STATUS_MPI_TAG);
    }
    else if(flag == FROM_MPI_STATUS_TO_JAVA_MPI_STATUS){
        (*env)->SetIntField(
            env,obj,JNI_MPI_STATUS_COUNT_HI,status->count_hi_and_cancelled);
        (*env)->SetIntField(
            env,obj,JNI_MPI_STATUS_COUNT_LO,status->count_lo);
        (*env)->SetIntField(
            env,obj,JNI_MPI_STATUS_MPI_ERROR,status->MPI_ERROR);
        (*env)->SetIntField(
            env,obj,JNI_MPI_STATUS_MPI_SOURCE,status->MPI_SOURCE);
        (*env)->SetIntField(
            env,obj,JNI_MPI_STATUS_MPI_TAG,status->MPI_TAG);
    }
}

// void delete_global_com_ref(JNIEnv*env,icom_element_t element,int rel_type)
// {
//     (*env)->ReleaseByteArrayElements(env,element.glob_array_ref,
//         element.buff,rel_type);
//     (*env)->DeleteGlobalRef(env,element.glob_array_ref);

//     element.glob_array_ref = NULL;
//     element.buff = NULL;
//     element.req = -1;
// }
void release_icom_element(
    JNIEnv* env,
    OPA_Queue_info_t* head,
    MPI_Request* req,
    int mode)
{
    icom_element_t *element = NULL;
    icom_element_t *first_element = NULL;

    if(OPA_Queue_is_empty(head)){
        printf("EMPTY!!\n");
        return;
    }
    first_element = OPA_Queue_peek_head(head);
    OPA_Queue_dequeue(head,element,icom_element_t,hdr);
    while(element != NULL){
        if(element->req == *req){
            
            if(element->datatype != org_mpich_MPI_OBJECT){
                jni_mpi_rel_buffer(env,element->glob_array_ref,
                    element->buff,element->datatype,mode);
            }
            else{
                (*env)->CallVoidMethod(env,element->glob_array_ref,
                    JNI_MPI_SERIALIZABLE_SET);
            }
            (*env)->DeleteGlobalRef(env,element->glob_array_ref);
            if(element->sendbuff != NULL){
                /**
                 * If the element contains a 
                 * collective communication data.
                 */
                jni_mpi_rel_buffer(env,element->sendbuff,
                    element->c_sendbuff,element->sendtype,JNI_ABORT);
                (*env)->DeleteGlobalRef(env,element->sendbuff);
            }
            if(element->counts_object != NULL){
                (*env)->ReleaseIntArrayElements(env,
                    element->counts_object,element->counts_buff,JNI_ABORT);
                (*env)->DeleteGlobalRef(env,element->counts_object);
            }
            if(element->disp_object != NULL){
                (*env)->ReleaseIntArrayElements(env,element->disp_object,
                    element->disp_buff,JNI_ABORT);
                (*env)->DeleteGlobalRef(env,element->disp_object);
            }
            if(element->counts2_object != NULL){
                (*env)->ReleaseIntArrayElements(env,
                    element->counts2_object,element->counts2_buff,JNI_ABORT);
                (*env)->DeleteGlobalRef(env,element->counts2_object);
            }
            if(element->disp2_object != NULL){
                (*env)->ReleaseIntArrayElements(env,element->disp2_object,
                    element->disp2_buff,JNI_ABORT);
                (*env)->DeleteGlobalRef(env,element->disp2_object);
            }

            free(element);
            element = NULL;
        }
        else{
            // enqueue the element
            OPA_Queue_enqueue(head,element,icom_element_t,hdr);
            // dequeu the next
            OPA_Queue_dequeue(head,element,icom_element_t,hdr);
        }

        if(first_element == element){
            // we couldn' find a element
            break;
        }
    }
}

int jni_mpi_sizeof(int type)
{
    int size = 0;
    switch (type)
    {
        case org_mpich_MPI_BYTE:
            size = sizeof(jbyte);
            break;
        case org_mpich_MPI_SHORT:
            size = sizeof(jshort);
            break;
        case org_mpich_MPI_INT:
            size = sizeof(jint);
            break;
        case org_mpich_MPI_LONG:
            size = sizeof(jlong);
            break;
        case org_mpich_MPI_FLOAT:
            size = sizeof(jfloat);
            break;
        case org_mpich_MPI_DOUBLE:
            size = sizeof(jdouble);
            break;
        case org_mpich_MPI_BOOL_00415_00410N:
            size = sizeof(jboolean);
            break;
        case org_mpich_MPI_CHAR:
            size = sizeof(jchar);
            break;
        default:
            break;
    }

    return size;
}

void init_icom_element(icom_element_t*ele)
{
    ele->buff = NULL;
    ele->c_sendbuff = NULL;
    ele->datatype = MPI_DATATYPE_NULL;
    ele->glob_array_ref = NULL;
    OPA_Queue_header_init(&ele->hdr);
    ele->req = MPI_REQUEST_NULL;
    ele->sendbuff = NULL;
    ele->sendtype = MPI_DATATYPE_NULL;
    ele->counts_object = NULL;
    ele->counts_buff = NULL;
    ele->disp_buff = NULL;
    ele->disp_object = NULL;
    ele->counts2_object = NULL;
    ele->counts2_buff = NULL;
    ele->disp2_object = NULL;
    ele->disp2_buff = NULL;
}