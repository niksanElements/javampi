#include "jni_mpi.h"
#include "jni_mpi_exception.h"

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Buffer_attach
 * Signature: (Ljava/nio/ByteBuffer;)I
 */
JNIEXPORT jint JNICALL Java_org_mpich_MPI_MPI_1Buffer_1attach(
    JNIEnv *env, 
    jclass class, 
    jobject buffer)
{
    jbyte* buff_ptr = (jbyte*)(*env)->GetDirectBufferAddress(env,buffer);
    int buff_size = (*env)->GetDirectBufferCapacity(env,buffer);
    int result;
    if(buff_ptr == NULL || buff_size == -1){
        goto fn_fail;
    }

    result = MPI_Buffer_attach(buff_ptr,buff_size);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Buffer_detach
 * Signature: (Ljava/nio/ByteBuffer;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Buffer_1detach(
    JNIEnv *env, 
    jclass class, 
    jobject buffer)
{
    jbyte* buff_ptr = (jbyte*)(*env)->GetDirectBufferAddress(env,buffer);
    int result;
    int buff_size = (*env)->GetDirectBufferCapacity(env,buffer);
    if(buff_ptr == NULL || buff_size == -1){
        goto fn_fail;
    }

    result = MPI_Buffer_detach(buff_ptr,&buff_size);

    fn_exit:
        if(result != MPI_SUCCESS){
            jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
        }
        return buff_size;
    fn_fail:
        return -1;
}