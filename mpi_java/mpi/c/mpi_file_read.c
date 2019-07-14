#include "mpi_File.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_File
 * Method:    _read
 * Signature: (JLjava/lang/Object;IIJLmpi/Status;)V
 */
JNIEXPORT void JNICALL 
Java_mpi_File__1read(
    JNIEnv *env, jclass class, jlong fh, 
    jobject buff, jint offset, jint count, jlong datatype, jobject status)
{
    MPI_Status _status;
    int result;
    tJniType *type = (tJniType*)datatype;
    MPI_File *file = (MPI_File*)fh;
    void* _buff = NULL;
    int size;

    if(type->isBufferType == JNI_FALSE){
#ifdef JNI_REGION_COPY
        // if the buffer is DirectBuffer
        // allocate _buff
        size = mpi_sizeof(type->mpi_type,env);
        if(size != -1){
            _buff = malloc(size*count);
        }
        else{
            return;
        }
        
        if(_buff == NULL){
            jniOutOfMemoryException(env,"malloc");
            return;
        }
#elif defined JNI_CRITICAL_SECTION
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
#endif
    }
    else{
        // if its of type direct buffer
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
        if(_buff == NULL){
            return;
        }
    }

    if(status == NULL){
        result = MPI_File_read(*file,_buff,count,type->mpi_type,MPI_STATUS_IGNORE);
    }
    else{
        result = MPI_File_read(*file,_buff,count,type->mpi_type,&_status);
    }
    
    if(type->isBufferType == JNI_FALSE){
        type->relBuffAddr(env,buff,offset,count,&_buff,type->size,JNI_COMMIT);
#ifdef JNI_REGION_COPY
            free(_buff);
#endif
    }

    if(result != MPI_SUCCESS){
        mpiFileException(env,"MPI_File_read");
    }

    if(status != NULL){
        setStatus(env,status,&_status,JNI_TRUE);
    }
}

/*
 * Class:     mpi_File
 * Method:    _read_at
 * Signature: (JJLjava/lang/Object;IIJLmpi/Status;)V
 */
JNIEXPORT void JNICALL 
Java_mpi_File__1read_1at(
    JNIEnv *env, jclass class, jlong file, jlong offset_file, 
    jobject buff, jint offset, jint count, jlong datatype, jobject status)
{
    MPI_Status _status;
    int result;
    tJniType *type = (tJniType*)datatype;
    MPI_File *_file = (MPI_File*)file;
    void* _buff = NULL;
    int size;

    if(type->isBufferType == JNI_FALSE){
#ifdef JNI_REGION_COPY
        // if the buffer is DirectBuffer
        // allocate _buff
        size = mpi_sizeof(type->mpi_type,env);
        if(size != -1){
            _buff = malloc(size*count);
        }
        else{
            return;
        }
        
        if(_buff == NULL){
            jniOutOfMemoryException(env,"malloc");
            return;
        }
#elif defined JNI_CRITICAL_SECTION
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
#endif
    }
    else{
        // if its of type direct buffer
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
        if(_buff == NULL){
            return;
        }
    }

    if(status == NULL){
        result = MPI_File_read_at(*_file,offset_file,_buff,count,type->mpi_type,MPI_STATUS_IGNORE);
    }
    else{
        result = MPI_File_read_at(*_file,offset_file,_buff,count,type->mpi_type,&_status);
    }
    
    if(type->isBufferType == JNI_FALSE){
        type->relBuffAddr(env,buff,offset,count,&_buff,type->size,JNI_COMMIT);
#ifdef JNI_REGION_COPY
            free(_buff);
#endif
    }

    if(result != MPI_SUCCESS){
        mpiFileException(env,"MPI_File_read_at");
    }

    if(status != NULL){
        setStatus(env,status,&_status,JNI_TRUE);
    }
}

/*
 * Class:     mpi_File
 * Method:    _read_shared
 * Signature: (JLjava/lang/Object;IIJLmpi/Status;)V
 */
JNIEXPORT void JNICALL 
Java_mpi_File__1read_1shared(
    JNIEnv *env, jclass class, 
    jlong file, jobject buff, jint offset, jint count, 
    jlong datatype, jobject status)
{
    MPI_Status _status;
    int result;
    tJniType *type = (tJniType*)datatype;
    MPI_File *_file = (MPI_File*)file;
    void* _buff = NULL;
    int size;

    if(type->isBufferType == JNI_FALSE){
#ifdef JNI_REGION_COPY
        // if the buffer is DirectBuffer
        // allocate _buff
        size = mpi_sizeof(type->mpi_type,env);
        if(size != -1){
            _buff = malloc(size*count);
        }
        else{
            return;
        }
        
        if(_buff == NULL){
            jniOutOfMemoryException(env,"malloc");
            return;
        }
#elif defined JNI_CRITICAL_SECTION
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
#endif
    }
    else{
        // if its of type direct buffer
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
        if(_buff == NULL){
            return;
        }
    }

    if(status == NULL){
        result = MPI_File_read_shared(*_file,_buff,count,type->mpi_type,MPI_STATUS_IGNORE);
    }
    else{
        result = MPI_File_read_shared(*_file,_buff,count,type->mpi_type,&_status);
    }
    
    if(type->isBufferType == JNI_FALSE){
        type->relBuffAddr(env,buff,offset,count,&_buff,type->size,JNI_COMMIT);
#ifdef JNI_REGION_COPY
            free(_buff);
#endif
    }

    if(result != MPI_SUCCESS){
        mpiFileException(env,"MPI_File_read_shared");
    }

    if(status != NULL){
        setStatus(env,status,&_status,JNI_TRUE);
    }
}

/*
 * Class:     mpi_File
 * Method:    _read_all
 * Signature: (JLjava/lang/Object;IIJLmpi/Status;)V
 */
JNIEXPORT void JNICALL 
Java_mpi_File__1read_1all(
    JNIEnv *env, jclass class, 
    jlong file, jobject buff, jint offset, jint count, 
    jlong datatype, jobject status)
{
    MPI_Status _status;
    int result;
    tJniType *type = (tJniType*)datatype;
    MPI_File *_file = (MPI_File*)file;
    void* _buff = NULL;
    int size;

    if(type->isBufferType == JNI_FALSE){
#ifdef JNI_REGION_COPY
        // if the buffer is DirectBuffer
        // allocate _buff
        size = mpi_sizeof(type->mpi_type,env);
        if(size != -1){
            _buff = malloc(size*count);
        }
        else{
            return;
        }
        
        if(_buff == NULL){
            jniOutOfMemoryException(env,"malloc");
            return;
        }
#elif defined JNI_CRITICAL_SECTION
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
#endif
    }
    else{
        // if its of type direct buffer
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
        if(_buff == NULL){
            return;
        }
    }

    if(status == NULL){
        result = MPI_File_read_all(*_file,_buff,count,type->mpi_type,MPI_STATUS_IGNORE);
    }
    else{
        result = MPI_File_read_all(*_file,_buff,count,type->mpi_type,&_status);
    }
    
    if(type->isBufferType == JNI_FALSE){
#ifdef JNI_CRITICAL_SECTION
        type->relBuffAddr(env,buff,offset,count,&_buff,type->size,JNI_COMMIT);
#elif defined JNI_REGION_COPY
            free(_buff);
#endif
    }

    if(result != MPI_SUCCESS){
        mpiFileException(env,"MPI_File_read_all");
    }

    if(status != NULL){
        setStatus(env,status,&_status,JNI_TRUE);
    }
}