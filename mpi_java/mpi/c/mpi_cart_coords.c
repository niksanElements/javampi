#include "mpi_Cart.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Cart
 * Method:    _cart_coords
 * Signature: (JIII[I)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Cart__1cart_1coords(
    JNIEnv *env, jclass class, jlong comm, 
    jint rank, jint offset, jint maxdims, jintArray coords)
{
    jint* _coords;
    int result;
    int size;

#ifdef JNI_REGION_COPY
    // if the buffer is DirectBuffer
    // allocate _buff
    size = sizeof(jint);
    if(size != -1){
        _coords = malloc(size*maxdims);
    }
    else{
        return -1;
    }
    
    if(_coords == NULL){
        jniOutOfMemoryException(env,"malloc");
        return -1;
    }
    // getIntRegion(env,coords,offset,maxdims,(void**)&_coords,0);
#elif defined JNI_CRITICAL_SECTION
    getCriticalSection(env,coords,offset,maxdims,(void**)&_coords,sizeof(jint),0);
#endif

    result = MPI_Cart_coords((MPI_Comm)comm,rank,maxdims,_coords);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Cart_create");
    }

#ifdef JNI_REGION_COPY
    setIntRegion(env,coords,offset,maxdims,(void**)&_coords,JNI_COMMIT);
    free(_coords);
#elif defined JNI_CRITICAL_SECTION
    relCriticalSection(env,coords,offset,maxdims,(void**)&_coords,sizeof(jint),JNI_COMMIT);
#endif
}