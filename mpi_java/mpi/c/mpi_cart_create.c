#include "mpi_Intracomm.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Intracomm
 * Method:    _cart_create
 * Signature: (JII[II[IZ)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Intracomm__1cart_1create(
    JNIEnv *env, jclass class, jlong comm_old, jint dims_offset, jint n, jintArray dims, 
        jint per_offset,jintArray periods, jboolean reorder)
{
    jint *_dims,*_periods;
    int size;
    int result;
    long cart_comm = 0;

#ifdef JNI_REGION_COPY
    // if the buffer is DirectBuffer
    // allocate _buff
    size = sizeof(jint);
    _dims = malloc(size*n);
    
    if(_dims == NULL){
        jniOutOfMemoryException(env,"malloc");
        return -1;
    }
    _periods = malloc(size*n)
    if(_periods == NULL){
        free(_dims);
        jniOutOfMemoryException(env,"malloc");
        return -1;
    }
    getIntRegion(env,dims,dims_offset,n,(void**)&_dims,0);
    getIntRegion(env,periods,per_offset,n,(void**)&_periods,0);
#elif defined JNI_CRITICAL_SECTION
    getCriticalSection(env,dims,dims_offset,n,(void**)&_dims,sizeof(jint),0);
    getCriticalSection(env,periods,per_offset,n,(void**)&_periods,sizeof(jint),0);
#endif

    result = MPI_Cart_create((MPI_Comm)comm_old,n,_dims,_periods,(int)reorder,(MPI_Comm*)&cart_comm);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Cart_create");
    }

#ifdef JNI_REGION_COPY
    free(_dims);
    free(_periods)
#elif defined JNI_CRITICAL_SECTION
    relCriticalSection(env,dims,dims_offset,n,(void**)&_dims,sizeof(jint),JNI_ABORT);
    relCriticalSection(env,periods,per_offset,n,(void**)&_periods,sizeof(jint),JNI_ABORT);
#endif

    return cart_comm;
}