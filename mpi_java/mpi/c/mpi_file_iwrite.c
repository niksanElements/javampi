#include "mpi_File.h"
#include "jni_mpi.h"
#include "jni_mpi_request.h"

#include "malloc.h"

/*
 * Class:     mpi_File
 * Method:    _iwrite
 * Signature: (JLjava/lang/Object;IIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL 
Java_mpi_File__1iwrite(
    JNIEnv *env, jclass class, 
    jlong file, jobject buff, jint offset, jint count, jlong datatype)
{
    tJniType *type = (tJniType*)datatype;
    MPI_File *_file = (MPI_File*)file;
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

    result = MPI_File_iwrite(*_file,request->address[JNI_ISEND_BUFFER],count,
        type->mpi_type,&request->request);

    if(result != MPI_SUCCESS){
        mpiFileException(env,"MPI_File_iwrite");
        jniMpiRequestFree(env,request);
        return NULL;
    }

    return (*env)->NewObject(env,gJniRequestClass,
        gJniRequestConstructor,(jlong)request);  
}

/*
 * Class:     mpi_File
 * Method:    _iwrite_shared
 * Signature: (JLjava/lang/Object;IIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL 
Java_mpi_File__1iwrite_1shared(
    JNIEnv *env, jclass class, 
    jlong file, jobject buff, jint offset, jint count, jlong datatype)
{
    tJniType *type = (tJniType*)datatype;
    MPI_File *_file = (MPI_File*)file;
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

    result = MPI_File_iwrite_shared(*_file,request->address[JNI_ISEND_BUFFER],count,
        type->mpi_type,&request->request);

    if(result != MPI_SUCCESS){
        mpiFileException(env,"MPI_File_iwrite_shared");
        jniMpiRequestFree(env,request);
        return NULL;
    }

    return (*env)->NewObject(env,gJniRequestClass,
        gJniRequestConstructor,(jlong)request);  
}

/*
 * Class:     mpi_File
 * Method:    _iwrite_at
 * Signature: (JJLjava/lang/Object;IIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL 
Java_mpi_File__1iwrite_1at(
    JNIEnv *env, jclass class, 
    jlong file, jlong offset_file, jobject buff, jint offset, jint count, jlong datatype)
{
    tJniType *type = (tJniType*)datatype;
    MPI_File *_file = (MPI_File*)file;
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

    result = MPI_File_iwrite_at(*_file,(MPI_Offset)offset_file,
        request->address[JNI_ISEND_BUFFER],count,type->mpi_type,&request->request);

    if(result != MPI_SUCCESS){
        mpiFileException(env,"MPI_File_iwrite_at");
        jniMpiRequestFree(env,request);
        return NULL;
    }

    return (*env)->NewObject(env,gJniRequestClass,
        gJniRequestConstructor,(jlong)request);  
}