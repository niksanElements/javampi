#include "mpi_Cart.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Cart
 * Method:    _cart_rank
 * Signature: (JII[I)I
 */
JNIEXPORT jint JNICALL 
Java_mpi_Cart__1cart_1rank(
    JNIEnv *env, jclass class, jlong comm, jint offset,jint ndims,jintArray coords)
{
    jint* _coords;
    int rank;
    int result;
    int size;

#ifdef JNI_REGION_COPY
    // if the buffer is DirectBuffer
    // allocate _buff
    size = sizeof(jint);
    if(size != -1){
        _coords = malloc(size*ndims);
    }
    else{
        return -1;
    }
    
    if(_coords == NULL){
        jniOutOfMemoryException(env,"malloc");
        return -1;
    }

    getIntRegion(env,coords,offset,ndims,(void**)&_coords,0);
#elif defined JNI_CRITICAL_SECTION
    getCriticalSection(env,coords,offset,ndims,(void**)&_coords,sizeof(jint),0);
#endif

    result = MPI_Cart_rank((MPI_Comm)comm,_coords,&rank);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Cart_create");
    }

#ifdef JNI_REGION_COPY
    free(_coords);
#elif defined JNI_CRITICAL_SECTION
    relCriticalSection(env,coords,offset,ndims,(void**)&_coords,sizeof(jint),JNI_ABORT);
#endif

    return rank;
}