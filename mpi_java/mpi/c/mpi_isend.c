#include "jni_mpi.h"
#include "mpi_Comm.h"
#include "jni_mpi_request.h"

#include "malloc.h"

/*
 * Class:     mpi_Comm
 * Method:    _isend
 * Signature: (Ljava/lang/Object;IIJIIJ)Lmpi/Request;
 * TODO: Error checking for the _isend
 */
JNIEXPORT jobject JNICALL 
Java_mpi_Comm__1isend(
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
    tJniType *type = (tJniType*)datatype;
    tJniRequest *request = calloc(1,sizeof(tJniRequest));
    int result;

    if(request == NULL){
        jniOutOfMemoryException(env,"calloc");
        return NULL;
    }

    // set datatype for the request
    request->type[JNI_ISEND_BUFFER] = type;
    // request type
    request->isSendRequest = JNI_TRUE;
    // request type
    request->isSendRequest = JNI_TRUE;

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

    result = MPI_Isend(request->address[JNI_ISEND_BUFFER],count,
        type->mpi_type,dest,tag,(MPI_Comm)comm,&request->request);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Isend");
        jniMpiRequestFree(env,request);
        return NULL;
    }

    return (*env)->NewObject(env,gJniRequestClass,
        gJniRequestConstructor,(jlong)request);
}

/*
 * Class:     mpi_Comm
 * Method:    _ibsend
 * Signature: (Ljava/lang/Object;IIJIIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL 
Java_mpi_Comm__1ibsend(
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
    tJniType *type = (tJniType*)datatype;
    tJniRequest *request = calloc(1,sizeof(tJniRequest));
    int result;

    if(request == NULL){
        jniOutOfMemoryException(env,"calloc");
        return NULL;
    }

    // set datatype for the request
    request->type[JNI_ISEND_BUFFER] = type;
    // request type
    request->isSendRequest = JNI_TRUE;

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
            jniMpiRequestFree(env,request);
            return NULL;
        }
        // copy the data
        request->type[JNI_ISEND_BUFFER]->copyBuffer(env,request->buffers[JNI_ISEND_BUFFER],
            offset,count,&request->address[JNI_ISEND_BUFFER],request->type[JNI_ISEND_BUFFER]->size,0);
    }

    result = MPI_Ibsend(request->address[JNI_ISEND_BUFFER],count,
        type->mpi_type,dest,tag,(MPI_Comm)comm,&request->request);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Ibsend");
        jniMpiRequestFree(env,request);
        return NULL;
    }

    return (*env)->NewObject(env,gJniRequestClass,
        gJniRequestConstructor,(jlong)request);
}

/*
 * Class:     mpi_Comm
 * Method:    _issend
 * Signature: (Ljava/lang/Object;IIJIIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL 
Java_mpi_Comm__1issend(
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
    tJniType *type = (tJniType*)datatype;
    tJniRequest *request = calloc(1,sizeof(tJniRequest));
    int result;

    if(request == NULL){
        jniOutOfMemoryException(env,"calloc");
        return NULL;
    }

    // set datatype for the request
    request->type[JNI_ISEND_BUFFER] = type;
    // request type
    request->isSendRequest = JNI_TRUE;

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
            jniMpiRequestFree(env,request);
            return NULL;
        }
        // copy the data
        request->type[JNI_ISEND_BUFFER]->copyBuffer(env,request->buffers[JNI_ISEND_BUFFER],
            offset,count,&request->address[JNI_ISEND_BUFFER],request->type[JNI_ISEND_BUFFER]->size,0);
    }

    result = MPI_Issend(request->address[JNI_ISEND_BUFFER],count,
        type->mpi_type,dest,tag,(MPI_Comm)comm,&request->request);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Issend");
        jniMpiRequestFree(env,request);
        return NULL;
    }

    return (*env)->NewObject(env,gJniRequestClass,
        gJniRequestConstructor,(jlong)request);
}

/*
 * Class:     mpi_Comm
 * Method:    _irsend
 * Signature: (Ljava/lang/Object;IIJIIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL 
Java_mpi_Comm__1irsend(
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
    tJniType *type = (tJniType*)datatype;
    tJniRequest *request = calloc(1,sizeof(tJniRequest));
    int result;

    if(request == NULL){
        jniOutOfMemoryException(env,"calloc");
        return NULL;
    }

    // set datatype for the request
    request->type[JNI_ISEND_BUFFER] = type;
    // request type
    request->isSendRequest = JNI_TRUE;

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
            jniMpiRequestFree(env,request);
            return NULL;
        }
        // copy the data
        request->type[JNI_ISEND_BUFFER]->copyBuffer(env,request->buffers[JNI_ISEND_BUFFER],
            offset,count,&request->address[JNI_ISEND_BUFFER],request->type[JNI_ISEND_BUFFER]->size,0);
    }

    result = MPI_Irsend(request->address[JNI_ISEND_BUFFER],count,
        type->mpi_type,dest,tag,(MPI_Comm)comm,&request->request);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Irsend");
        jniMpiRequestFree(env,request);
        return NULL;
    }

    return (*env)->NewObject(env,gJniRequestClass,
        gJniRequestConstructor,(jlong)request);
}

