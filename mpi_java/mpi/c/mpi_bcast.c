#include "mpi_Intracomm.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Intracomm
 * Method:    _bcast
 * Signature: (Ljava/lang/Object;IIJIJ)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Intracomm__1bcast(
    JNIEnv *env, 
    jclass class, 
    jobject buff, jint offset, jint count, jlong datatype, 
    jint root, jlong comm)
{
    tJniType *type = (tJniType*)datatype;
    int result;
    void* _buff = NULL;
    int size;
    MPI_Status stat;

    if(type->isBufferType == JNI_FALSE){
#ifdef JNI_REGION_COPY
        // if the buffer is not of type DirectBuffer
        // allocate _buff
        _buff = malloc(type->size*count);
        if(_buff == NULL){
            jniOutOfMemoryException(env,"malloc");
            return;
        }
#endif
        // copy the buffer
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
    }
    else{
        type->getBuffAddr(env,buff,offset,count,&_buff,type->size,0);
        if(_buff == NULL){
            return;
        }
    }
    
    result = MPI_Bcast(_buff,count,type->mpi_type,root,(MPI_Comm)comm);

    if(buff != NULL){
        if(type->isBufferType == JNI_FALSE){
            type->relBuffAddr(env,buff,offset,count,&_buff,type->size,JNI_COMMIT);
#ifdef JNI_REGION_COPY
            free(_buff);
#endif
        }
    }
    // rase exception if there is one
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Bcast");
    }
}