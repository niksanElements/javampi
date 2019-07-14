#include "mpi_Message.h"
#include "jni_mpi.h"
#include "jni_mpi_status.h"

#ifdef JNI_REGION_COPY
#include "malloc.h"
#endif


/*
 * Class:     mpi_Message
 * Method:    _mrecv
 * Signature: (Ljava/lang/Object;IIJJLmpi/Status;)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Message__1mrecv(
    JNIEnv *env, 
    jclass class, 
    jobject buff, 
    jint offset, 
    jint count, 
    jlong datatype, 
    jlong message,
    jobject status)
{
    MPI_Status stat;
    int result;
    tJniType *type = (tJniType*)datatype;
    void* _buff = NULL;
    int size;
    MPI_Message msg = (MPI_Message)message;

    if(type->isBufferType == JNI_FALSE){
#ifdef JNI_REGION_COPY
        // if the buffer is DirectBuffer
        // allocate _buff
        size = mpi_sizeof(type->mpi_type,env);
        if(size != -1){
            _buff = malloc(size*count);
        }
        else{
            return -1;
        }
        
        if(_buff == NULL){
            jniOutOfMemoryException(env,"malloc");
            return -1;
        }
#elif defined JNI_CRITICAL_SECTION
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
#endif
    }
    else{
         // if its of type direct buffer
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
        if(_buff == NULL){
            return -1;
        }
    }

    result = MPI_Mrecv(_buff,count,type->mpi_type,&msg,&stat);

if(type->isBufferType == JNI_FALSE){
        type->relBuffAddr(env,buff,offset,count,&_buff,type->size,JNI_ABORT);
#ifdef JNI_REGION_COPY
        free(_buff);
#endif
    }
    
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Mrecv");
        return -1;
    }

    // populate the stat
    (*env)->CallVoidMethod(env,status,gJniStatusGetStatus,
        stat.count_lo,stat.count_hi_and_cancelled,stat.MPI_SOURCE,
        stat.MPI_TAG,stat.MPI_ERROR,JNI_TRUE);
    return (jlong)msg;
}