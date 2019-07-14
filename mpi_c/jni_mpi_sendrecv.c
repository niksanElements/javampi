#include "jni_mpi.h"
#include "jni_mpi_exception.h"

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Sendrecv
 * Signature: (Ljava/lang/Object;IIILjava/lang/Object;IIIILorg/mpich/MPI_Status;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Sendrecv(
    JNIEnv *env, 
    jclass class, 
    jobject sendBuff, 
    jint sendType, 
    jint dest, 
    jint sendTag, 
    jobject recvBuff, 
    jint recvType, 
    jint source, 
    jint recvTag, 
    jint comm, 
    jobject status)
{
    int result;

    int count = (*env)->GetArrayLength(env,sendBuff);
    MPI_Status stat;
    void *_s;
    void *_r;
    int mpi_send_type = 0;
    int mpi_recv_type = 0;

    // get the buffers
    jni_mpi_get_buffer(env,sendBuff,_s,sendType,mpi_send_type);
    jni_mpi_get_buffer(env,recvBuff,_r,recvType,mpi_recv_type);
    
    if(count != (*env)->GetArrayLength(env,recvBuff)){
        goto fn_fail;
    }

    result = MPI_Sendrecv(_s,count,mpi_send_type,dest,sendTag,
        _r,count,mpi_recv_type,source,recvTag,comm,&stat);

    jni_mpi_convert_MPI_Status(env,status,&stat,
        FROM_MPI_STATUS_TO_JAVA_MPI_STATUS);

    // release buffers
    jni_mpi_rel_buffer(env,sendBuff,_s,sendType,JNI_ABORT);
    jni_mpi_rel_buffer(env,recvBuff,_r,recvType,JNI_COMMIT);

    JNI_MPI_RETURN(result);
}


/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Sendrecv_replace
 * Signature: (Ljava/lang/Object;IIIIIILorg/mpich/MPI_Status;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Sendrecv_1replace(
    JNIEnv *env, 
    jclass class, 
    jobject buff, 
    jint datatype, 
    jint dest, 
    jint sendtag, 
    jint source, 
    jint recvtag, 
    jint comm, 
    jobject status)
{
    void* buffer;
    int count = (*env)->GetArrayLength(env,buff);
    int mpi_type;
    int result;
    MPI_Status stat;

    jni_mpi_get_buffer(env,buff,buffer,datatype,mpi_type);

    result = MPI_Sendrecv_replace(buffer,count,mpi_type,dest,sendtag,source,recvtag,comm,&stat);
    jni_mpi_convert_MPI_Status(env,status,&stat,
        FROM_MPI_STATUS_TO_JAVA_MPI_STATUS);

    jni_mpi_rel_buffer(env,buff,buffer,datatype,JNI_COMMIT);

    JNI_MPI_RETURN(result);
}