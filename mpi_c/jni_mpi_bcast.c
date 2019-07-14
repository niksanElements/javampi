#include "jni_mpi.h"
#include "jni_mpi_exception.h"

#include <malloc.h>

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Bcast
 * Signature: (Ljava/lang/Object;III)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Bcast(
    JNIEnv *env, 
    jclass class, 
    jobject buff, 
    jint datatype, 
    jint root, 
    jint comm)
{
    int result;
    int mpi_type;
    void* c_buff;
    int count;

    if(datatype != org_mpich_MPI_OBJECT){
        count = (*env)->GetArrayLength(env,buff);
        jni_mpi_get_buffer(env,buff,c_buff,datatype,mpi_type);
    }
    else{
        int rank;
        MPI_Comm_rank(comm,&rank);
        if(root != rank){
            jni_mpi_get_obj_addr(env,buff,c_buff,count,datatype,mpi_type,JNI_FALSE);
        }
        else{
            jni_mpi_get_obj_addr(env,buff,c_buff,count,datatype,mpi_type,JNI_TRUE);
        }
    }

    result = MPI_Bcast(c_buff,count,mpi_type,root,comm);

    if(datatype != org_mpich_MPI_OBJECT){
        jni_mpi_rel_buffer(env,buff,c_buff,datatype,JNI_COMMIT);
    }
    else{
        (*env)->CallVoidMethod(env,buff,JNI_MPI_SERIALIZABLE_SET);
    }

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Ibcast
 * Signature: (Ljava/lang/Object;IIILorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Ibcast(
    JNIEnv *env, 
    jclass class, 
    jobject buff, 
    jint datatype, 
    jint root, 
    jint comm, 
    jobject req)
{
    int result = 0;

    icom_element_t *element;
    int mpi_type;
    int count;

    element = malloc(sizeof(icom_element_t));
    if(element == NULL){
        goto fn_fail;
    }
    init_icom_element(element);
    element->datatype = datatype;  
    if(datatype != org_mpich_MPI_OBJECT){                         
        element->glob_array_ref = (*env)->NewGlobalRef(env,buff);        
        jni_mpi_get_buffer(env,element->glob_array_ref,
            element->buff,datatype,mpi_type);
        count =                                                         
            (*env)->GetArrayLength(env,element->glob_array_ref);  
    }
    else{
        int rank;
        MPI_Comm_rank(comm,&rank);
        if(root != rank){
            jni_mpi_gobj_addr(env,buff,element->glob_array_ref,
                element->buff,count,datatype,mpi_type,JNI_FALSE);
        }
        else{
            jni_mpi_gobj_addr(env,buff,element->glob_array_ref,
                element->buff,count,datatype,mpi_type,JNI_TRUE);
        }
    }
                           
    OPA_Queue_enqueue(&JNI_MPI_QHEAD_IRECV,element,icom_element_t,hdr);    
          
    result = MPI_Ibcast(
        element->buff,count,datatype,root,comm,&element->req);

    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_HANDLER,
        element->req);                          
    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_TYPE,               
        JNI_MPI_REQUEST_TYPE_RECV);                              

    JNI_MPI_RETURN(result);
}
