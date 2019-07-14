#include "mpi_File.h"
#include "jni_mpi.h"
#include "jni_mpi_request.h"

#include "malloc.h"

/*
 * Class:     mpi_File
 * Method:    _iread
 * Signature: (JLjava/lang/Object;IIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL 
Java_mpi_File__1iread(
    JNIEnv *env, jclass class, 
    jlong file, jobject buff, jint offset, jint count, jlong datatype)
{
    MPI_File *_file = (MPI_File*)file;
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

    result = MPI_File_iread(*_file,request->address[JNI_IRECV_BUFFER],count,type->mpi_type,&request->request);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_File_iread");
        free(request);
        return NULL;
    }

    return (*env)->NewObject(env,gJniRequestClass,
        gJniRequestConstructor,(jlong)request);
}

/*
 * Class:     mpi_File
 * Method:    _iread_shared
 * Signature: (JLjava/lang/Object;IIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL 
Java_mpi_File__1iread_1shared(
    JNIEnv *env, jclass class, 
    jlong file, jobject buff, jint offset, jint count, jlong datatype)
{
    MPI_File *_file = (MPI_File*)file;
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

    result = MPI_File_iread_shared(*_file,request->address[JNI_IRECV_BUFFER],count,type->mpi_type,&request->request);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_File_iread_shared");
        free(request);
        return NULL;
    }

    return (*env)->NewObject(env,gJniRequestClass,
        gJniRequestConstructor,(jlong)request);
}

/*
 * Class:     mpi_File
 * Method:    _iread_at
 * Signature: (JJLjava/lang/Object;IIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL 
Java_mpi_File__1iread_1at(
    JNIEnv *env, jclass class, 
    jlong file, jlong offset_file, jobject buff, jint offset, jint count, jlong datatype)
{
    MPI_File *_file = (MPI_File*)file;
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

    result = MPI_File_iread_at(*_file,(MPI_Offset)offset_file,
        request->address[JNI_IRECV_BUFFER],count,type->mpi_type,&request->request);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_File_iread_at");
        free(request);
        return NULL;
    }

    return (*env)->NewObject(env,gJniRequestClass,
        gJniRequestConstructor,(jlong)request);
}