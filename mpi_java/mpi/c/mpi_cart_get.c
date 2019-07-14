#include "mpi_Cart.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Cart
 * Method:    _cart_get
 * Signature: (JII[II[II[I)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Cart__1cart_1get(
    JNIEnv *env, jclass class, jlong comm, jint offsetdims, 
    jint maxdims, jintArray dims, jint offsetperiods, jintArray periods, 
    jint offsetcoords, jintArray coords)
{
    int size;
    int result;
    jint *_dims,*_periods,*_coords;

#ifdef JNI_REGION_COPY
    // if the buffer is DirectBuffer
    // allocate _buff
    size = sizeof(jint);
    _dims = malloc(size*maxdims);

    if(_dims == NULL){
        jniOutOfMemoryException(env,"malloc");
        return;
    }
    _periods = malloc(size*maxdims);
    if(_periods == NULL){
        free(_dims);
        jniOutOfMemoryException(env,"malloc");
        return;
    }
    _coords = malloc(size*maxdims);
    if(_coords == NULL){
        free(_dims);
        free(_periods);
        jniOutOfMemoryException(env,"malloc");
        return -1;
    }

#elif defined JNI_CRITICAL_SECTION
    getCriticalSection(env,dims,offsetdims,maxdims,(void**)&_dims,sizeof(jint),0);
    getCriticalSection(env,periods,offsetperiods,maxdims,(void**)&_periods,sizeof(jint),0);
    getCriticalSection(env,coords,offsetcoords,maxdims,(void**)&_coords,sizeof(jint),0);
#endif
    result = MPI_Cart_get((MPI_Comm)comm,maxdims,_dims,_periods,_coords);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_cart_get");
    }

#ifdef JNI_REGION_COPY
    setIntRegion(env,dims,offsetdims,maxdims,(void**)&_dims,JNI_COMMIT);
    free(_dims);
    setIntRegion(env,periods,offsetperiods,maxdims,(void**)&_periods,JNI_COMMIT);
    free(_periods);
    setIntRegion(env,coords,offsetcoords,maxdims,(void**)&_coords,JNI_COMMIT);
    free(_coords);
#elif defined JNI_CRITICAL_SECTION
    relCriticalSection(env,dims,offsetdims,maxdims,(void**)&_dims,sizeof(jint),JNI_COMMIT);
    relCriticalSection(env,periods,offsetperiods,maxdims,(void**)&_periods,sizeof(jint),JNI_COMMIT);
    relCriticalSection(env,coords,offsetcoords,maxdims,(void**)&_coords,sizeof(jint),JNI_COMMIT);
#endif
}