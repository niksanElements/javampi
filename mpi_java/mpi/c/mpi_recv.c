#include "mpi_Comm.h"
#include "jni_mpi.h"
#include "jni_mpi_status.h"

#include "malloc.h"

/*
 * Class:     mpi_Comm
 * Method:    _recv
 * Signature: (Ljava/lang/Object;IIJIIJ)Lmpi/Status;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1recv(
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
    MPI_Status stat;
    int result;
    tJniType *type = (tJniType*)datatype;
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
            return NULL;
        }
        
        if(_buff == NULL){
            jniOutOfMemoryException(env,"malloc");
            return NULL;
        }
#elif defined JNI_CRITICAL_SECTION
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
#endif
    }
    else{
        // if its of type direct buffer
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
        if(_buff == NULL){
            return NULL;
        }
    }

    result = MPI_Recv(_buff,count,type->mpi_type,source,tag,comm,&stat);
    
    if(type->isBufferType == JNI_FALSE){
        type->relBuffAddr(env,buff,offset,count,&_buff,type->size,JNI_ABORT);
#ifdef JNI_REGION_COPY
        free(_buff);
#endif
    }

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Recv");
        return NULL;
    }

    return (*env)->NewObject(env,gJniStatusClass,gJniStatusConstructor,
        stat.count_lo,stat.count_hi_and_cancelled,
        stat.MPI_SOURCE,stat.MPI_TAG,stat.MPI_ERROR);
}