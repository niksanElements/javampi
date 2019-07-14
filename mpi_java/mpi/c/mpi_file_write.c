#include "mpi_File.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_File
 * Method:    _write
 * Signature: (JLjava/lang/Object;IIJLmpi/Status;)V
 */
JNIEXPORT void JNICALL 
Java_mpi_File__1write(
    JNIEnv *env, jclass class, jlong file, jobject buff, jint offset, jint count, jlong datatype, jobject status)
{
    tJniType *type = (tJniType*)datatype;
    MPI_File *_file = (MPI_File*)file;
    int result;
    void* _buff = NULL;
    int size;

    MPI_Status _status;

   int access_mode;
   MPI_File_get_amode(*_file,&access_mode);
   if((access_mode & (MPI_MODE_WRONLY | MPI_MODE_RDWR)) == 0){
       mpiPermissionsException(env,"Premission denied!");
       return;
   }

    if(type->isBufferType == JNI_FALSE){
#ifdef JNI_REGION_COPY
        // if the buffer is not of type DirectBuffer
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
#endif
        // copy the buffer
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
    }
    else{
        // direct buffer
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
        if(_buff == NULL){
            return;
        }
    }
    if(status == NULL){
        result = MPI_File_write(*_file,_buff,count,type->mpi_type,&_status);
    }
    else{
        result = MPI_File_write(*_file,_buff,count,type->mpi_type,MPI_STATUS_IGNORE);
    }
    if(type->isBufferType == JNI_FALSE)
#ifdef JNI_REGION_COPY
        free(_buff);
#elif defined JNI_CRITICAL_SECTION
        type->relBuffAddr(env,buff,offset,count,&_buff,type->size,JNI_ABORT);
#endif
    if(result != MPI_SUCCESS){
        mpiFileException(env,"MPI_File_write");
    }

    if(status != NULL){
        setStatus(env,status,&_status,JNI_TRUE);
    }
}

/*
 * Class:     mpi_File
 * Method:    _write_at
 * Signature: (JJLjava/lang/Object;IIJLmpi/Status;)V
 */
JNIEXPORT void JNICALL
Java_mpi_File__1write_1at(
    JNIEnv *env, jclass class, jlong file, jlong offset_file, jobject buff, 
    jint offset, jint count, jlong datatype, jobject status)
{
    tJniType *type = (tJniType*)datatype;
    MPI_File *_file = (MPI_File*)file;
    int result;
    void* _buff = NULL;
    int size;

    MPI_Status _status;

    if(type->isBufferType == JNI_FALSE){
#ifdef JNI_REGION_COPY
        // if the buffer is not of type DirectBuffer
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
#endif
        // copy the buffer
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
    }
    else{
        // direct buffer
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
        if(_buff == NULL){
            return;
        }
    }
    if(status == NULL){
        result = MPI_File_write_at(*_file,offset_file,_buff,count,type->mpi_type,&_status);
    }
    else{
        result = MPI_File_write_at(*_file,offset_file,_buff,count,type->mpi_type,MPI_STATUS_IGNORE);
    }
    if(type->isBufferType == JNI_FALSE)
#ifdef JNI_REGION_COPY
        free(_buff);
#elif defined JNI_CRITICAL_SECTION
        type->relBuffAddr(env,buff,offset,count,&_buff,type->size,JNI_ABORT);
#endif
    if(result != MPI_SUCCESS){
        mpiFileException(env,"MPI_File_write_at");
    }

    if(status != NULL){
        setStatus(env,status,&_status,JNI_TRUE);
    }
}

/*
 * Class:     mpi_File
 * Method:    _write_shared
 * Signature: (JLjava/lang/Object;IIJLmpi/Status;)V
 */
JNIEXPORT void JNICALL 
Java_mpi_File__1write_1shared(
    JNIEnv *env, jclass class, 
    jlong file, jobject buff, jint offset, jint count, 
    jlong datatype, jobject status)
{
    tJniType *type = (tJniType*)datatype;
    MPI_File *_file = (MPI_File*)file;
    int result;
    void* _buff = NULL;
    int size;

    MPI_Status _status;

   int access_mode;
   MPI_File_get_amode(*_file,&access_mode);
   if((access_mode & (MPI_MODE_WRONLY | MPI_MODE_RDWR)) == 0){
       mpiPermissionsException(env,"Premission denied!");
       return;
   }

    if(type->isBufferType == JNI_FALSE){
#ifdef JNI_REGION_COPY
        // if the buffer is not of type DirectBuffer
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
#endif
        // copy the buffer
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
    }
    else{
        // direct buffer
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
        if(_buff == NULL){
            return;
        }
    }
    if(status == NULL){
        result = MPI_File_write_shared(*_file,_buff,count,type->mpi_type,&_status);
    }
    else{
        result = MPI_File_write_shared(*_file,_buff,count,type->mpi_type,MPI_STATUS_IGNORE);
    }
    if(type->isBufferType == JNI_FALSE)
#ifdef JNI_REGION_COPY
        free(_buff);
#elif defined JNI_CRITICAL_SECTION
        type->relBuffAddr(env,buff,offset,count,&_buff,type->size,JNI_ABORT);
#endif
    if(result != MPI_SUCCESS){
        mpiFileException(env,"MPI_File_write_shared");
    }

    if(status != NULL){
        setStatus(env,status,&_status,JNI_TRUE);
    }
}

/*
 * Class:     mpi_File
 * Method:    _write_all
 * Signature: (JLjava/lang/Object;IIJLmpi/Status;)V
 */
JNIEXPORT void JNICALL 
Java_mpi_File__1write_1all(
    JNIEnv *env, jclass class, 
    jlong file, jobject buff, jint offset, jint count, 
    jlong datatype, jobject status)
{
    tJniType *type = (tJniType*)datatype;
    MPI_File *_file = (MPI_File*)file;
    int result;
    void* _buff = NULL;
    int size;

    MPI_Status _status;

   int access_mode;
   MPI_File_get_amode(*_file,&access_mode);
   if((access_mode & (MPI_MODE_WRONLY | MPI_MODE_RDWR)) == 0){
       mpiPermissionsException(env,"Premission denied!");
       return;
   }

    if(type->isBufferType == JNI_FALSE){
#ifdef JNI_REGION_COPY
        // if the buffer is not of type DirectBuffer
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
#endif
        // copy the buffer
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
    }
    else{
        // direct buffer
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
        if(_buff == NULL){
            return;
        }
    }
    if(status == NULL){
        result = MPI_File_write_all(*_file,_buff,count,type->mpi_type,&_status);
    }
    else{
        result = MPI_File_write_all(*_file,_buff,count,type->mpi_type,MPI_STATUS_IGNORE);
    }
    if(type->isBufferType == JNI_FALSE)
#ifdef JNI_REGION_COPY
        free(_buff);
#elif defined JNI_CRITICAL_SECTION
        type->relBuffAddr(env,buff,offset,count,&_buff,type->size,JNI_ABORT);
#endif
    if(result != MPI_SUCCESS){
        mpiFileException(env,"MPI_File_write_all");
    }

    if(status != NULL){
        setStatus(env,status,&_status,JNI_TRUE);
    }
}