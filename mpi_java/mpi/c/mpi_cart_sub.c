#include "mpi_Cart.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Cart
 * Method:    _sub
 * Signature: (JII[I)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Cart__1sub(
    JNIEnv *env, jclass class, jlong comm, jint offset, jint size, 
        jintArray remain)
{
    long new_comm = 0;
    int result;
    int type_size;
    jint *_remain;

#ifdef JNI_REGION_COPY
    // if the buffer is DirectBuffer
    // allocate _buff
    type_size = sizeof(jint);
    if(size != -1){
        _remain = malloc(type_size*size);
    }
    else{
        return -1;
    }
    
    if(_remain == NULL){
        jniOutOfMemoryException(env,"malloc");
        return -1;
    }
    getIntRegion(env,remain,offset,size,(void**)&_remain,0);
#elif defined JNI_CRITICAL_SECTION
    getCriticalSection(env,remain,offset,size,(void**)&_remain,sizeof(jint),0);
#endif

    result = MPI_Cart_sub((MPI_Comm)comm,_remain,(MPI_Comm*)&new_comm);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Cart_sub");
    }

#ifdef JNI_REGION_COPY
    free(_remain);
#elif defined JNI_CRITICAL_SECTION
    relCriticalSection(env,remain,offset,size,(void**)&_remain,sizeof(jint),JNI_ABORT);
#endif

    return new_comm;
}