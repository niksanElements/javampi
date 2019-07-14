#include "mpi_Intracomm.h"
#include "jni_mpi.h"
#include "jni_mpi_op.h"

#include "malloc.h"

/*
 * Class:     mpi_Intracomm
 * Method:    _exscan
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;IIIJJJ)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Intracomm__1exscan(
    JNIEnv *env, jclass class, 
    jobject sendbuff, jobject recvbuff, jint sendoffset, jint recvoffset, 
    jint sendcount, jlong datatype, jlong op, jlong comm)
{
    tJniType *type = (tJniType*)datatype;
    tJniOp *_op = (tJniOp*)op;
    int result;
    void* _sendbuff = NULL;
    void* _recvbuff = NULL;
    int size;

    /**
     * MPI doesn't require a send buffer and recieve buffer
     * in the same function call. For example you don't have to 
     * set sendbuffer in the recieve process or the way around. 
     */
    if(sendbuff != NULL){
        if(type->isBufferType == JNI_FALSE){
            // if the buffer is not of type DirectBuffer
            // allocate _buff
            _sendbuff = malloc(type->size*sendcount);
            if(_sendbuff == NULL){
                jniOutOfMemoryException(env,"malloc");
                return;
            }

            // copy the buffer
            type->copyBuffer(env,sendbuff,sendoffset,sendcount,&_sendbuff,type->size,0);
        }
        else{
            // if its of type direct buffer
            type->getBuffAddr(env,sendbuff,sendoffset,sendcount,&_sendbuff,type->size,0);
            if(_sendbuff == NULL){
                return;
            }
        }
    }

    if(recvbuff != NULL){
        if(type->isBufferType == JNI_FALSE){
            // if the buffer is not of type DirectBuffer
            // allocate _buff
            _recvbuff = malloc(type->size*sendcount);
            if(_recvbuff == NULL){
                jniOutOfMemoryException(env,"malloc");
                return;
            }

        }
        else{
            // if its of type direct buffer
            type->getBuffAddr(env,recvbuff,recvoffset,sendcount,&_recvbuff,type->size,0);
            if(_recvbuff == NULL){
                return;
            }
        }
    }

    result = MPI_Exscan(_sendbuff,_recvbuff,sendcount,
        type->mpi_type,_op->mpi_op,(MPI_Comm)comm);

    if(recvbuff != NULL){
        if(type->isBufferType == JNI_FALSE){
            type->setBuffer(env,recvbuff,recvoffset,sendcount,&_recvbuff,type->size,JNI_COMMIT);
            free(_recvbuff);
        }
    }
    if(sendbuff != NULL){
         if(type->isBufferType == JNI_FALSE)
            free(_sendbuff);
    }
    // rase exception if there is one
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Exscan");
    }
}