#include "jni_mpi.h"
#include "mpi_MPI.h"

/*
 * Class:     mpi_MPI
 * Method:    _buffer_attach
 * Signature: (Ljava/nio/ByteBuffer;)V
 */
JNIEXPORT void JNICALL 
Java_mpi_MPI__1buffer_1attach(
    JNIEnv *env, 
    jclass class, 
    jobject buff)
{
    void* address;
    int result;
    int capacity;

    address = (*env)->GetDirectBufferAddress(env,buff);
    capacity = (*env)->GetDirectBufferCapacity(env,buff);
     if(address == NULL){
        jniUndefinedMemException(env,"JNI GetDirectBufferAddress");
        return;
    }
    
    result = MPI_Buffer_attach(address,capacity);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Buffer_attach");
    }
}

/*
 * Class:     mpi_MPI
 * Method:    _buffer_detach
 * Signature: (Ljava/nio/ByteBuffer;)V
 */
JNIEXPORT void JNICALL Java_mpi_MPI__1buffer_1detach(
    JNIEnv *env, 
    jclass class, 
    jobject buff)
{
    void* address;
    int result;
    int capacity;

    address = (*env)->GetDirectBufferAddress(env,buff);
    capacity = (*env)->GetDirectBufferCapacity(env,buff);
     if(address == NULL){
        jniUndefinedMemException(env,"JNI GetDirectBufferAddress");
        return;
    }
    
    result = MPI_Buffer_detach(address,&capacity);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Buffer_detach");
    }
}
