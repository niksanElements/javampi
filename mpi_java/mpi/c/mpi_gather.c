#include "mpi_Intracomm.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Intracomm
 * Method:    _gather
 * Signature: (Ljava/lang/Object;IIJLjava/lang/Object;IIJIJ)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Intracomm__1gather(
    JNIEnv *env, jclass class, 
    jobject sendbuff, jint sendoffset, jint sendcount, jlong sendtype, 
    jobject recvbuff, jint recvoffset, jint recvcount, jlong recvtype, 
    jint root, jlong comm)
{
    int result;
    tJniType* _sendtype = (tJniType*)sendtype;
    tJniType* _recvtype = (tJniType*)recvtype;
    void* _sendbuff = NULL;
    void* _recvbuff = NULL;
    int commSize = 0;

    result = MPI_Comm_size(comm,&commSize);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Comm_size");
        return;
    }

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
                return;
            }
#endif
            // copy the buffer
            _sendtype->getBuffAddr(env,sendbuff,sendoffset,sendcount,&_sendbuff,_sendtype->size,0);
        }
        else{
            // if its of type direct buffer
            _sendtype->getBuffAddr(env,sendbuff,sendoffset,sendcount,&_sendbuff,_sendtype->size,0);
            if(_sendbuff == NULL){
                return;
            }
        }
    }

    if(recvbuff != NULL){
        if(_recvtype->isBufferType == JNI_FALSE){
#ifdef JNI_REGION_COPY
            // if the buffer is not of type DirectBuffer
            // allocate _buff
            _recvbuff = malloc(_recvtype->size*recvcount*commSize);
            if(_recvbuff == NULL){
                jniOutOfMemoryException(env,"malloc");
                return;
            }
#elif defined JNI_CRITICAL_SECTION
            _recvtype->getBuffAddr(env,recvbuff,recvoffset,recvcount*commSize,&_recvbuff,_recvtype->size,0);
#endif
        }
        else{
            // if its of type direct buffer
            _recvtype->getBuffAddr(env,recvbuff,recvoffset,recvcount*commSize,&_recvbuff,_recvtype->size,0);
            if(_recvbuff == NULL){
                return;
            }
        }
    }

    result = MPI_Gather(_sendbuff,sendcount,_sendtype->mpi_type,
        _recvbuff,recvcount,_recvtype->mpi_type,root,(MPI_Comm)comm);

    if(recvbuff != NULL){
        if(_recvtype->isBufferType == JNI_FALSE){
            _recvtype->relBuffAddr(env,recvbuff,recvoffset,recvcount*commSize,
                &_recvbuff,_recvtype->size,JNI_COMMIT);
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
}