#include "mpi_Comm.h"
#include "jni_mpi.h"
#include "jni_mpi_status.h"

#ifdef JNI_REGION_COPY
#include "malloc.h"
#endif


/*
 * Class:     mpi_Comm
 * Method:    _sendrecv
 * Signature: (Ljava/lang/Object;IIJIILjava/lang/Object;IIJIIJ)Lmpi/Status;
 */
JNIEXPORT jobject JNICALL 
Java_mpi_Comm__1sendrecv(
    JNIEnv *env, jclass class, 
    jobject sendbuff,jint sendoffset,jint sendcount,jlong sendtype, 
    jint dest, jint sendtag, 
    jobject recvbuff, jint recvoffset, jint recvcount, jlong recvtype, 
    jint source, jint recvtag, 
    jlong comm)
{
    tJniType *_sendtype = (tJniType*)sendtype;
    tJniType *_recvtype = (tJniType*)recvtype;
    int result;
    void* _sendbuff = NULL;
    void* _recvbuff = NULL;
    int size;
    MPI_Status stat;

    /**
     * MPI doesn't require a send buffer and recieve buffer
     * in the same function call. For example you don't have to 
     * set sendbuffer in the recieve process or the way around. 
     */

    if(sendbuff != NULL){
        if(_sendtype->isBufferType == JNI_FALSE){
#ifdef JNI_REGION_COPY
            // if the buffer is not of type DirectBuffer
            // allocate _buff
            _sendbuff = malloc(_sendtype->size*sendcount);
            if(_sendbuff == NULL){
                jniOutOfMemoryException(env,"malloc");
                return NULL;
            }
#endif
            // copy the buffer
            _sendtype->getBuffAddr(env,sendbuff,sendoffset,sendcount,&_sendbuff,_sendtype->size,0);
        }
        else{
            // if its of type direct buffer
            _sendtype->getBuffAddr(env,sendbuff,sendoffset,sendcount,&_sendbuff,_sendtype->size,0);
            if(_sendbuff == NULL){
                return NULL;
            }
        }
    }

    if(recvbuff != NULL){
        if(_recvtype->isBufferType == JNI_FALSE){
#ifdef JNI_REGION_COPY
            // if the buffer is not of type DirectBuffer
            // allocate _buff
            _recvbuff = malloc(_recvtype->size*recvcount);
            if(_recvbuff == NULL){
                jniOutOfMemoryException(env,"malloc");
                return NULL;
            }
#elif defined JNI_CRITICAL_SECTION
            _recvtype->getBuffAddr(env,recvbuff,recvoffset,recvcount,&_recvbuff,_recvtype->size,0);
#endif
        }
        else{
            // if its of type direct buffer
            _recvtype->getBuffAddr(env,recvbuff,recvoffset,recvcount,&_recvbuff,_recvtype->size,0);
            if(_recvbuff == NULL){
                return NULL;
            }
        }
    }
    // printf("send: %p %d %d %d %d\n recv: %p %d %d %d %d\n",
    //     _sendbuff,sendcount,_sendtype->mpi_type,dest,sendtag,
    //     _recvbuff,recvcount,_recvtype->mpi_type,source,recvtag);
    result = MPI_Sendrecv(_sendbuff,sendcount,_sendtype->mpi_type,
        dest,sendtag,
        _recvbuff,recvcount,_recvtype->mpi_type,
        source,recvtag,(MPI_Comm)comm,&stat);

    if(recvbuff != NULL){
        if(_recvtype->isBufferType == JNI_FALSE){
            _recvtype->relBuffAddr(env,recvbuff,recvoffset,recvcount,&_recvbuff,_recvtype->size,JNI_COMMIT);
#ifdef JNI_REGION_COPY
            free(_recvbuff);
#endif
        }
    }
    if(sendbuff != NULL){
         if(_sendtype->isBufferType == JNI_FALSE)
#ifdef JNI_REGION_COPY
            free(_sendbuff);
#elif defined JNI_CRITICAL_SECTION
            _sendtype->relBuffAddr(env,sendbuff,sendoffset,sendcount,&_sendbuff,_sendtype->size,JNI_ABORT);
#endif
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