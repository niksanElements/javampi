#include "jni_mpi.h"
#include "jni_mpi_exception.h"

#include <malloc.h>


#define JNI_MPI_SEND_INIT(env,buff,dest,tag,comm,request,mpi_send)          \
{                                                                           \
    jbyte* buff_ptr = (*env)->GetDirectBufferAddress(env,buff);             \
    int buff_size = (*env)->GetDirectBufferCapacity(env,buff);              \
    MPI_Request req;                                                        \
    if(buff_ptr == NULL || buff_size == -1){                                \
        goto fn_fail;                                                       \
    }                                                                       \
    result = mpi_send(buff_ptr,buff_size,MPI_BYTE,dest,tag,comm,&req);      \
    (*env)->SetIntField(env,request,JNI_MPI_REQUEST_HANDLER,req);           \
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Send_init
 * Signature: (Ljava/lang/Object;IIIILorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Send_1init(
    JNIEnv *env, 
    jclass class, 
    jobject buff, 
    jint dest, 
    jint tag, 
    jint comm, 
    jobject request)
{
    int result;

    JNI_MPI_SEND_INIT(env,buff,dest,tag,comm,request,MPI_Send_init);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Bsend_init
 * Signature: (Ljava/nio/ByteBuffer;IIILorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Bsend_1init(
    JNIEnv *env, 
    jclass class, 
    jobject buffer, 
    jint dest, 
    jint tag, 
    jint comm, 
    jobject request)
{
    int result;

    JNI_MPI_SEND_INIT(env,buffer,dest,tag,comm,request,MPI_Bsend_init);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Ssend_init
 * Signature: (Ljava/nio/ByteBuffer;IIILorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Ssend_1init(
    JNIEnv *env, 
    jclass class, 
    jobject buffer, 
    jint dest, 
    jint tag, 
    jint comm, 
    jobject request)
{
    int result;

    JNI_MPI_SEND_INIT(env,buffer,dest,tag,comm,request,MPI_Ssend_init);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Rsend_init
 * Signature: (Ljava/nio/ByteBuffer;IIILorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Rsend_1init(
    JNIEnv *env, 
    jclass class, 
    jobject buffer, 
    jint dest, 
    jint tag, 
    jint comm, 
    jobject request)
{
    int result;

    JNI_MPI_SEND_INIT(env,buffer,dest,tag,comm,request,MPI_Rsend_init);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Recv_init
 * Signature: (Ljava/lang/Object;IIIILorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Recv_1init(
    JNIEnv *env, 
    jclass class, 
    jobject buff, 
    jint source, 
    jint tag, 
    jint comm, 
    jobject request)
{
    int result;

    jbyte* buff_ptr = (*env)->GetDirectBufferAddress(env,buff);
    int buff_size = (*env)->GetDirectBufferCapacity(env,buff);
    MPI_Request req;

    if(buff_ptr == NULL || buff_size == -1){
        goto fn_fail;
    }

    result = MPI_Recv_init(buff_ptr,buff_size,MPI_BYTE,source,tag,comm,&req);
    (*env)->SetIntField(env,request,JNI_MPI_REQUEST_HANDLER,req);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Start
 * Signature: (Lorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Start(
    JNIEnv *env, 
    jclass class, 
    jobject request)
{
    MPI_Request req;
    int result;

    req = (*env)->GetIntField(env,request,JNI_MPI_REQUEST_HANDLER);
    result = MPI_Start(&req);

    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }
    return result;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Startall
 * Signature: (Lorg/mpich/[MPI_Request;)I
 */
JNIEXPORT jint JNICALL
Java_org_mpich_MPI_MPI_1Startall(
    JNIEnv *env, 
    jclass class, 
    jobjectArray requests)
{
    int count = (*env)->GetArrayLength(env,requests);
    MPI_Request *reqs = malloc(sizeof(MPI_Request)*count);
    int result;
    if(reqs == NULL){
        goto fn_fail;
    }

    for(int i = 0;i < count;i++){
        jobject temp_obj = (*env)->GetObjectArrayElement(env,requests,i);
        reqs[i] = (*env)->GetIntField(env,temp_obj,JNI_MPI_REQUEST_HANDLER);
        (*env)->DeleteLocalRef(env,temp_obj);
    }

    result = MPI_Startall(count,reqs);

    free(reqs);

    JNI_MPI_RETURN(result);
}