#include "mpi_Intracomm.h"
#include "jni_mpi.h"
#include "jni_mpi_request.h"

#include "malloc.h"

/*
 * Class:     mpi_Intracomm
 * Method:    _iallgather
 * Signature: (Ljava/lang/Object;IIJLjava/lang/Object;IIJJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL 
Java_mpi_Intracomm__1iallgather(
    JNIEnv *env, jclass class, 
    jobject sendbuff, jint sendoffset, jint sendcount, jlong sendtype, 
    jobject recvbuff, jint recvoffset, jint recvcount, jlong recvtype, 
    jlong comm)
{
        tJniRequest *request = calloc(1,sizeof(tJniRequest));
    int result;
    int commSize = 0;

    if(request == NULL){
        jniOutOfMemoryException(env,"calloc");
        return NULL;
    }

    result = MPI_Comm_size((MPI_Comm)comm,&commSize);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Comm_size");
        return NULL;
    }

    // set datatypes for the request
    request->type[JNI_ISEND_BUFFER] = (tJniType*)sendtype;
    request->type[JNI_IRECV_BUFFER] = (tJniType*)recvtype;


    if(sendbuff != NULL){
        if(request->type[JNI_ISEND_BUFFER]->isBufferType){
            // direct buffer
            request->type[JNI_ISEND_BUFFER]->getBuffAddr(env,sendbuff,sendoffset,sendcount,
                &request->address[JNI_ISEND_BUFFER],request->type[JNI_ISEND_BUFFER]->size,0);
            request->offset[JNI_ISEND_BUFFER] = sendoffset;
            request->count[JNI_ISEND_BUFFER] = sendcount;
        }
        else{
            // create new global array
            // TODO: check NewGlobalRef
            request->buffers[JNI_ISEND_BUFFER] = (*env)->NewGlobalRef(env,
                sendbuff);
            request->offset[JNI_ISEND_BUFFER] = sendoffset;
            request->count[JNI_ISEND_BUFFER] = sendcount; 
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
            request->type[JNI_IRECV_BUFFER]->getBuffAddr(env,recvbuff,recvoffset,recvcount*commSize,
                &request->address[JNI_IRECV_BUFFER],request->type[JNI_IRECV_BUFFER]->size,0);
            request->offset[JNI_IRECV_BUFFER] = recvoffset;
            request->count[JNI_IRECV_BUFFER] = recvcount;
        }
        else{
            // create new global array
            // TODO: check NewGlobalRef
            request->buffers[JNI_IRECV_BUFFER] = (*env)->NewGlobalRef(env,
                recvbuff);
            request->offset[JNI_IRECV_BUFFER] = recvoffset;
            request->count[JNI_IRECV_BUFFER] = recvcount*commSize; 
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
    result = MPI_Iallgather(
        request->address[JNI_ISEND_BUFFER],request->count[JNI_ISEND_BUFFER],
        request->type[JNI_ISEND_BUFFER]->mpi_type,
        request->address[JNI_IRECV_BUFFER],recvcount,
        request->type[JNI_IRECV_BUFFER]->mpi_type,
        (MPI_Comm)comm,&request->request);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Isend");
        jniMpiRequestFree(env,request);
        return NULL;
    }

    return (*env)->NewObject(env,gJniRequestClass,
        gJniRequestConstructor,(jlong)request);
}