#include "mpi_Comm.h"
#include "jni_mpi.h"
#include "jni_mpi_status.h"

/*
 * Class:     mpi_Comm
 * Method:    _sendrecv_replace
 * Signature: (Ljava/lang/Object;IIJIIIIJ)Lmpi/Status;
 */
JNIEXPORT jobject JNICALL 
Java_mpi_Comm__1sendrecv_1replace(
    JNIEnv *env, jclass class, 
    jobject buff,jint offset, jint count, jlong datatype, 
    jint dest, jint sendtag, jint source, jint recvtag, 
    jlong comm)
{
    tJniType *type = (tJniType*)datatype;
    int result;
    void* _buff = NULL;
    int size;
    MPI_Status stat;

    if(type->isBufferType == JNI_FALSE){
#ifdef JNI_REGION_COPY
        // if the buffer is not of type DirectBuffer
        // allocate _buff
        _buff = malloc(type->size*count);
        if(_buff == NULL){
            jniOutOfMemoryException(env,"malloc");
            return NULL;
        }
#endif
        // copy the buffer
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
    }
    else{
        // driect buffer
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
        if(_buff == NULL){
            return NULL;
        }
    }

    result = MPI_Sendrecv_replace(_buff,count,type->mpi_type,
        dest,sendtag,source,recvtag,(MPI_Comm)comm,&stat);

    if(buff != NULL){
        if(type->isBufferType == JNI_FALSE){
            type->relBuffAddr(env,buff,offset,count,&_buff,type->size,JNI_COMMIT);
#ifdef JNI_REGION_COPY
            free(_buff);
#endif
        }
    }
    // rase exception if there is one
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Sendrecv");
    }

    // the return object corresponds to the recieve operation
    return (*env)->NewObject(env,gJniStatusClass,gJniStatusConstructor,
        stat.count_lo,stat.count_hi_and_cancelled,
        stat.MPI_SOURCE,stat.MPI_TAG,stat.MPI_ERROR);
}