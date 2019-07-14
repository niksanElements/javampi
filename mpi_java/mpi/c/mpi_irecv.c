#include "jni_mpi.h"
#include "mpi_Comm.h"
#include "jni_mpi_request.h"

#include "malloc.h"


/*
 * Class:     mpi_Comm
 * Method:    _irecv
 * Signature: (Ljava/lang/Object;IIJIIJ)Lmpi/Request;
 * 
 * // TODO: send objects
 */
JNIEXPORT jobject JNICALL 
Java_mpi_Comm__1irecv(
    JNIEnv *env, 
    jclass class, 
    jobject buff, 
    jint offset, 
    jint count, 
    jlong datatype, 
    jint source, 
    jint tag, 
    jlong comm)
{
    tJniType *type = (tJniType*)datatype;
    tJniRequest *request = calloc(1,sizeof(tJniRequest));
    int result;

    if(request == NULL){
        jniOutOfMemoryException(env,"calloc");
        return NULL;
    }

    // set datatype for the request
    request->type[JNI_IRECV_BUFFER] = type;

    if(type->isBufferType){
        // direct buffer
        type->getBuffAddr(env,buff,offset,count,
            &request->address[JNI_IRECV_BUFFER],type->size,0);
    }
    else{
        // create new global array
        request->buffers[JNI_IRECV_BUFFER] = (*env)->NewGlobalRef(env,
            buff);
        request->offset[JNI_IRECV_BUFFER] = offset;
        request->count[JNI_IRECV_BUFFER] = count; 
        request->address[JNI_IRECV_BUFFER] = malloc(type->size*count);
        // allocate buffer
        if(request->address[JNI_IRECV_BUFFER] == NULL){
            jniOutOfMemoryException(env,"malloc");
            free(request);
            return NULL;
        }
    }

    result = MPI_Irecv(request->address[JNI_IRECV_BUFFER],count,
        type->mpi_type,source,tag,(MPI_Comm)comm,&request->request);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Irecv");
        free(request);
        return NULL;
    }

    return (*env)->NewObject(env,gJniRequestClass,
        gJniRequestConstructor,(jlong)request);
}
