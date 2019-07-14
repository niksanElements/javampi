#include "mpi_Comm.h"
#include "jni_mpi.h"
#include "jni_mpi_request.h"

#include "malloc.h"

/*
 * Class:     mpi_Comm
 * Method:    _recv_init
 * Signature: (Ljava/lang/Object;IIJIIJ)Lmpi/Request;
 * // TODO: Implement algorithm for regular types.
 */
JNIEXPORT jobject JNICALL 
Java_mpi_Comm__1recv_1init(
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
    tJniType* type = (tJniType*)datatype;
    tJniRequest* request;
    int result;

    if(!type->isBufferType){
        mpiErrType(env,"Unsupported datatype!");
        return NULL;
    }

    request = calloc(1,sizeof(tJniRequest));
    if(request == NULL){
        jniOutOfMemoryException(env,"calloc");
        return NULL;
    }

    // create the request
    // set datatype for the request
    request->isPersistentRequest = JNI_TRUE;
    request->type[JNI_IRECV_BUFFER] = type;
    type->getBuffAddr(env,buff,offset,count,
        &request->address[JNI_IRECV_BUFFER],type->size,0);

    result = MPI_Recv_init(request->address[JNI_IRECV_BUFFER],count,
        request->type[JNI_IRECV_BUFFER]->mpi_type,source,tag,(MPI_Comm)comm,&request->request);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Recv_init");
        jniMpiRequestFree(env,request);
        return NULL;
    }

    return (*env)->NewObject(env,gJniRequestClass,
        gJniRequestConstructor,(jlong)request);
}