#include "mpi_Comm.h"
#include "mpi.h"
#include "jni_mpi_throw.h"
#include "jni_mpi_types.h"

// TODO: configure malloc.h
#include "malloc.h"

/*
 * Class:     mpi_Comm
 * Method:    _send
 * Signature: (Ljava/lang/Object;IIJIIJ)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Comm__1send(
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
    int result;
    void* _buff = NULL;
    int size;

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

    result = MPI_Send(_buff,count,type->mpi_type,dest,tag,(MPI_Comm)comm);
    if(type->isBufferType == JNI_FALSE)
#ifdef JNI_REGION_COPY
        free(_buff);
#elif defined JNI_CRITICAL_SECTION
        type->relBuffAddr(env,buff,offset,count,&_buff,type->size,JNI_ABORT);
#endif
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Send");
    }
}

/*
 * Class:     mpi_Comm
 * Method:    _bsend
 * Signature: (Ljava/lang/Object;IIJIIJ)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Comm__1bsend(
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
    int result;
    void* _buff = NULL;
    int size;

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

    result = MPI_Bsend(_buff,count,type->mpi_type,dest,tag,(MPI_Comm)comm);
    if(type->isBufferType == JNI_FALSE)
#ifdef JNI_REGION_COPY
        free(_buff);
#elif defined JNI_CRITICAL_SECTION
        type->relBuffAddr(env,buff,offset,count,&_buff,type->size,JNI_ABORT);
#endif
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Bsend");
    }
}

/*
 * Class:     mpi_Comm
 * Method:    _ssend
 * Signature: (Ljava/lang/Object;IIJIIJ)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Comm__1ssend(
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
    int result;
    void* _buff = NULL;
    int size;

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

    result = MPI_Ssend(_buff,count,type->mpi_type,dest,tag,(MPI_Comm)comm);
    if(type->isBufferType == JNI_FALSE)
#ifdef JNI_REGION_COPY
        free(_buff);
#elif defined JNI_CRITICAL_SECTION
        type->relBuffAddr(env,buff,offset,count,&_buff,type->size,JNI_ABORT);
#endif
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Ssend");
    }
}

/*
 * Class:     mpi_Comm
 * Method:    _rsend
 * Signature: (Ljava/lang/Object;IIJIIJ)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Comm__1rsend(
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
    int result;
    void* _buff = NULL;
    int size;

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

    result = MPI_Rsend(_buff,count,type->mpi_type,dest,tag,(MPI_Comm)comm);
    if(type->isBufferType == JNI_FALSE)
#ifdef JNI_REGION_COPY
        free(_buff);
#elif defined JNI_CRITICAL_SECTION
        type->relBuffAddr(env,buff,offset,count,&_buff,type->size,JNI_ABORT);
#endif
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Rsend");
    }
}

