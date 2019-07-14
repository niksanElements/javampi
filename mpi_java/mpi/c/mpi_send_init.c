#include "mpi_Comm.h"
#include "jni_mpi.h"
#include "jni_mpi_request.h"

#include "malloc.h"

/*
 * Class:     mpi_Comm
 * Method:    _send_init
 * Signature: (Ljava/lang/Object;IIJIIJ)Lmpi/Request;
 * // TODO: Implement algorithm for regular types.
 */
JNIEXPORT jobject JNICALL 
Java_mpi_Comm__1send_1init(
    JNIEnv *env, 
    jclass class, 
    jobject buff, 
    jint offset, 
    jint count, 
    jlong datatype, 
    jint dest, 
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
    request->type[JNI_ISEND_BUFFER] = type;
    request->isPersistentRequest = JNI_TRUE;
    type->getBuffAddr(env,buff,offset,count,
        &request->address[JNI_ISEND_BUFFER],type->size,0);

    result = MPI_Send_init(request->address[JNI_ISEND_BUFFER],count,
        request->type[JNI_ISEND_BUFFER]->mpi_type,dest,tag,(MPI_Comm)comm,&request->request);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Send_init");
        jniMpiRequestFree(env,request);
        return NULL;
    }

    return (*env)->NewObject(env,gJniRequestClass,
        gJniRequestConstructor,(jlong)request);
}

/*
 * Class:     mpi_Comm
 * Method:    _bsend_init
 * Signature: (Ljava/lang/Object;IIJIIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL
Java_mpi_Comm__1bsend_1init(
    JNIEnv *env, 
    jclass class, 
    jobject buff, 
    jint offset, 
    jint count, 
    jlong datatype, 
    jint dest, 
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
    request->type[JNI_ISEND_BUFFER] = type;
    request->isPersistentRequest = JNI_TRUE;
    type->getBuffAddr(env,buff,offset,count,
        &request->address[JNI_ISEND_BUFFER],type->size,0);

    result = MPI_Bsend_init(request->address[JNI_ISEND_BUFFER],count,
        request->type[JNI_ISEND_BUFFER]->mpi_type,dest,tag,(MPI_Comm)comm,&request->request);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Bsend_init");
        jniMpiRequestFree(env,request);
        return NULL;
    }

    return (*env)->NewObject(env,gJniRequestClass,
        gJniRequestConstructor,(jlong)request);
}

/*
 * Class:     mpi_Comm
 * Method:    _ssend_init
 * Signature: (Ljava/lang/Object;IIJIIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL
Java_mpi_Comm__1ssend_1init(
    JNIEnv *env, 
    jclass class, 
    jobject buff, 
    jint offset, 
    jint count, 
    jlong datatype, 
    jint dest, 
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
    request->type[JNI_ISEND_BUFFER] = type;
    request->isPersistentRequest = JNI_TRUE;
    type->getBuffAddr(env,buff,offset,count,
        &request->address[JNI_ISEND_BUFFER],type->size,0);

    result = MPI_Ssend_init(request->address[JNI_ISEND_BUFFER],count,
        request->type[JNI_ISEND_BUFFER]->mpi_type,dest,tag,(MPI_Comm)comm,&request->request);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Ssend_init");
        jniMpiRequestFree(env,request);
        return NULL;
    }

    return (*env)->NewObject(env,gJniRequestClass,
        gJniRequestConstructor,(jlong)request);
}

/*
 * Class:     mpi_Comm
 * Method:    _rsend_init
 * Signature: (Ljava/lang/Object;IIJIIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL
Java_mpi_Comm__1rsend_1init(
    JNIEnv *env, 
    jclass class, 
    jobject buff, 
    jint offset, 
    jint count, 
    jlong datatype, 
    jint dest, 
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
    request->type[JNI_ISEND_BUFFER] = type;
    request->isPersistentRequest = JNI_TRUE;
    type->getBuffAddr(env,buff,offset,count,
        &request->address[JNI_ISEND_BUFFER],type->size,0);

    result = MPI_Rsend_init(request->address[JNI_ISEND_BUFFER],count,
        request->type[JNI_ISEND_BUFFER]->mpi_type,dest,tag,(MPI_Comm)comm,&request->request);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Rsend_init");
        jniMpiRequestFree(env,request);
        return NULL;
    }

    return (*env)->NewObject(env,gJniRequestClass,
        gJniRequestConstructor,(jlong)request);
}
