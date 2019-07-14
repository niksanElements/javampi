#include "jni_mpi.h"
#include "jni_mpi_exception.h"

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Request_get_status
 * Signature: (Lorg/mpich/MPI_Request;Lorg/mpich/MPI_Status;)Z
 */
JNIEXPORT jboolean JNICALL 
Java_org_mpich_MPI_MPI_1Request_1get_1status(
    JNIEnv *env, 
    jclass class, 
    jobject request, 
    jobject status)
{
    MPI_Request req;
    MPI_Status stat;
    int req_type;
    int result;
    int flag;

    if(request != NULL){
        req = (*env)->GetIntField(env,request,JNI_MPI_REQUEST_HANDLER);
        req_type = (*env)->GetIntField(env,request,JNI_MPI_REQUEST_TYPE);

        if(status == NULL){
            result = MPI_Request_get_status(req,&flag,MPI_STATUS_IGNORE);
        }
        else{
            result = MPI_Request_get_status(req,&flag,&stat);
            jni_mpi_convert_MPI_Status(env,status,&stat,
                FROM_MPI_STATUS_TO_JAVA_MPI_STATUS);
        }
        if(flag == 1){
            if(req_type == JNI_MPI_REQUEST_TYPE_RECV){
                release_icom_element(env,&JNI_MPI_QHEAD_IRECV,&req,JNI_COMMIT);
            }
            else if(req_type == JNI_MPI_REQUEST_TYPE_SEND){
                release_icom_element(env,&JNI_MPI_QHEAD_ISEND,&req,JNI_ABORT);
            }
        }
    }
    else{

        if(status == NULL){
            result = MPI_Request_get_status(MPI_REQUEST_NULL,&flag,MPI_STATUS_IGNORE);
        }
        else{
            result = MPI_Request_get_status(MPI_REQUEST_NULL,&flag,&stat);
            jni_mpi_convert_MPI_Status(env,status,&stat,
                FROM_MPI_STATUS_TO_JAVA_MPI_STATUS);
        }
    }
    
    fn_exit:
        if(result != MPI_SUCCESS){
            jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
        }
        if(flag == 1){
            return JNI_TRUE;
        }
        return JNI_FALSE;
    fn_fail:
        return JNI_FALSE;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Request_free
 * Signature: (Lorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Request_1free(
    JNIEnv *env, 
    jclass class, 
    jobject request)
{
    MPI_Request req;
    int result;

    req = (*env)->GetIntField(env,request,JNI_MPI_REQUEST_HANDLER);
    result = MPI_Request_free(&req);
    (*env)->SetIntField(env,request,JNI_MPI_REQUEST_HANDLER,req);

    fn_exit:
        if(result != MPI_SUCCESS){
            jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
        }
        return MPI_SUCCESS;
    fn_fail:
        return -1;
}