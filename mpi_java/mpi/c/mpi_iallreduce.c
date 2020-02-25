#include "mpi_Comm.h"
#include "jni_mpi.h"
#include "jni_mpi_op.h"
#include "jni_mpi_request.h"

#include "malloc.h"

/*
 * Class:     mpi_Comm
 * Method:    _iallreduce
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;IIIJJJ)Lmpi/Request;
 */
JNIEXPORT jobject 
JNICALL Java_mpi_Comm__1iallreduce(
    JNIEnv *env, jclass class, jobject sendbuff, jobject recvbuff, 
    jint sendoffset, jint recvoffset, jint count, jlong datatype, jlong op, jlong comm)
{
    tJniRequest *request = calloc(1,sizeof(tJniRequest));
    tJniOp *_op = (tJniOp*)op;
    int result;
    int commSize = 0;

    if(request == NULL){
        jniOutOfMemoryException(env,"calloc");
        return NULL;
    }

    // set datatypes for the request
    request->type[JNI_ISEND_BUFFER] = (tJniType*)datatype;
    request->type[JNI_IRECV_BUFFER] = (tJniType*)datatype;


    if(sendbuff != NULL){
        if(request->type[JNI_ISEND_BUFFER]->isBufferType){
            // direct buffer
            request->type[JNI_ISEND_BUFFER]->getBuffAddr(env,sendbuff,sendoffset,count*commSize,
                &request->address[JNI_ISEND_BUFFER],request->type[JNI_ISEND_BUFFER]->size,0);
            request->offset[JNI_ISEND_BUFFER] = sendoffset;
            request->count[JNI_ISEND_BUFFER] = count;
        }
        else{
            // create new global array
            // TODO: check NewGlobalRef
            request->buffers[JNI_ISEND_BUFFER] = (*env)->NewGlobalRef(env,
                sendbuff);
            request->offset[JNI_ISEND_BUFFER] = sendoffset;
            request->count[JNI_ISEND_BUFFER] = count; 
            request->address[JNI_ISEND_BUFFER] = malloc(
                request->type[JNI_ISEND_BUFFER]->size*request->count[JNI_ISEND_BUFFER]);
            // allocate buffer
            if(request->address[JNI_ISEND_BUFFER] == NULL){
                jniOutOfMemoryException(env,"malloc");
                jniMpiRequestFree(env,request);
                return NULL;
            }
            // copy the data
            request->type[JNI_ISEND_BUFFER]->copyBuffer(env,request->buffers[JNI_ISEND_BUFFER],
                request->offset[JNI_ISEND_BUFFER],request->count[JNI_ISEND_BUFFER],
                &request->address[JNI_ISEND_BUFFER],request->type[JNI_ISEND_BUFFER]->size,0);
        }
    }

    if(recvbuff != NULL){
        if(request->type[JNI_IRECV_BUFFER]->isBufferType){
            // direct buffer
            request->type[JNI_IRECV_BUFFER]->getBuffAddr(env,recvbuff,recvoffset,count*commSize,
                &request->address[JNI_IRECV_BUFFER],request->type[JNI_IRECV_BUFFER]->size,0);
            request->offset[JNI_IRECV_BUFFER] = recvoffset;
            request->count[JNI_IRECV_BUFFER] = count;
        }
        else{
            // create new global array
            // TODO: check NewGlobalRef
            request->buffers[JNI_IRECV_BUFFER] = (*env)->NewGlobalRef(env,
                recvbuff);
            request->offset[JNI_IRECV_BUFFER] = recvoffset;
            request->count[JNI_IRECV_BUFFER] = count; 
            request->address[JNI_IRECV_BUFFER] = malloc(
                request->type[JNI_IRECV_BUFFER]->size*request->count[JNI_IRECV_BUFFER]);
            // allocate buffer
            if(request->address[JNI_IRECV_BUFFER] == NULL){
                jniOutOfMemoryException(env,"malloc");
                jniMpiRequestFree(env,request);
                return NULL;
            }
            // copy the data
            request->type[JNI_IRECV_BUFFER]->copyBuffer(env,request->buffers[JNI_IRECV_BUFFER],
                request->offset[JNI_IRECV_BUFFER],request->count[JNI_IRECV_BUFFER],
                &request->address[JNI_IRECV_BUFFER],request->type[JNI_IRECV_BUFFER]->size,0);
        }
    }

    // MPI_Iallgather
    result = MPI_Iallreduce(
        request->address[JNI_ISEND_BUFFER],request->address[JNI_IRECV_BUFFER],count,
        request->type[JNI_IRECV_BUFFER]->mpi_type,_op->mpi_op,
        (MPI_Comm)comm,&request->request);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Ireduce");
        jniMpiRequestFree(env,request);
        return NULL;
    }

    return (*env)->NewObject(env,gJniRequestClass,
        gJniRequestConstructor,(jlong)request);
}