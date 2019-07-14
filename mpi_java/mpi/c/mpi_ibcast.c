#include "mpi_Intracomm.h"
#include "jni_mpi.h"
#include "jni_mpi_request.h"

#include "malloc.h"

/*
 * Class:     mpi_Intracomm
 * Method:    _ibcast
 * Signature: (Ljava/lang/Object;IIJIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL 
Java_mpi_Intracomm__1ibcast(
    JNIEnv *env, jclass class, 
    jobject buff, jint offset, jint count, jlong datatype, 
    jint root, jlong comm)
{
    tJniType *type = (tJniType*)datatype;
    tJniRequest *request = calloc(1,sizeof(tJniRequest));
    int result;

    if(request == NULL){
        jniOutOfMemoryException(env,"calloc");
        return NULL;
    }

    // set datatype for the request
    request->type[JNI_ISEND_BUFFER] = type;

    if(type->isBufferType){
        // direct buffer
        type->getBuffAddr(env,buff,offset,count,
            &request->address[JNI_ISEND_BUFFER],type->size,0);
    }
    else{
        // create new global array
        // TODO: check NewGlobalRef
        request->buffers[JNI_ISEND_BUFFER] = (*env)->NewGlobalRef(env,
            buff);
        request->offset[JNI_ISEND_BUFFER] = offset;
        request->count[JNI_ISEND_BUFFER] = count; 
        request->address[JNI_ISEND_BUFFER] = malloc(type->size*count);
        // allocate buffer
        if(request->address[JNI_ISEND_BUFFER] == NULL){
            jniOutOfMemoryException(env,"malloc");
            jniMpiRequestFree(env,request);
            return NULL;
        }
        // copy the data
        request->type[JNI_ISEND_BUFFER]->copyBuffer(env,request->buffers[JNI_ISEND_BUFFER],
            offset,count,&request->address[JNI_ISEND_BUFFER],request->type[JNI_ISEND_BUFFER]->size,0);
    }

    result = MPI_Ibcast(request->address[JNI_ISEND_BUFFER],count,
        type->mpi_type,root,(MPI_Comm)comm,&request->request);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Isend");
        jniMpiRequestFree(env,request);
        return NULL;
    }

    return (*env)->NewObject(env,gJniRequestClass,
        gJniRequestConstructor,(jlong)request);
}