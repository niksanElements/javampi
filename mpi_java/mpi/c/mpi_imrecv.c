#include "mpi_Message.h"
#include "jni_mpi.h"
#include "jni_mpi_request.h"

#include "malloc.h"

/*
 * Class:     mpi_Message
 * Method:    _imrecv
 * Signature: (Ljava/lang/Object;IIJJLmpi/Request;)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Message__1imrecv(
    JNIEnv *env, 
    jclass class, 
    jobject buff, 
    jint offset, 
    jint count, 
    jlong datatype, 
    jlong message, 
    jobject req)
{
    tJniType *type = (tJniType*)datatype;
    tJniRequest *request = calloc(1,sizeof(tJniRequest));
    int result;
    MPI_Message msg = (MPI_Message)message;

    if(request == NULL){
        jniOutOfMemoryException(env,"calloc");
        return -1;
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
        request->buffers[JNI_ISEND_BUFFER] = (*env)->NewGlobalRef(env,
            buff);
        request->offset[JNI_ISEND_BUFFER] = offset;
        request->count[JNI_ISEND_BUFFER] = count; 
        request->address[JNI_ISEND_BUFFER] = malloc(type->size*count);
        // allocate buffer
        if(request->address[JNI_ISEND_BUFFER] == NULL){
            jniOutOfMemoryException(env,"malloc");
            free(request);
            return -1;
        }
    }

    result = MPI_Imrecv(request->address[JNI_ISEND_BUFFER],count,
        type->mpi_type,&msg,&request->request);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Imrecv");
        free(request);
        return -1;
    }

    // populate the request
    (*env)->SetLongField(env,req,gJniRequestHandler,(long)request);

    return (jlong)msg;
}