#include "mpi_MPI.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_MPI
 * Method:    _dims_create
 * Signature: (III[I)V
 */
JNIEXPORT void JNICALL 
Java_mpi_MPI__1dims_1create(
    JNIEnv *env, jclass class, jint nnodes, jint offset, jint ndims, jintArray dims)
{
    jint* _dims;
    int size;

#ifdef JNI_REGION_COPY
    // if the buffer is DirectBuffer
    // allocate _buff
    size = sizeof(jint);
    if(size != -1){
        _dims = malloc(size*ndims);
    }
    else{
        return -1;
    }
    
    if(_dims == NULL){
        jniOutOfMemoryException(env,"malloc");
        return -1;
    }

    getIntRegion(env,dims,offset,ndims,(void**)&_dims,0);
#elif defined JNI_CRITICAL_SECTION
    getCriticalSection(env,dims,offset,ndims,(void**)&_dims,sizeof(jint),0);
#endif

    MPI_Dims_create(nnodes,ndims,_dims);

#ifdef JNI_REGION_COPY
    free(_dims);
#elif defined JNI_CRITICAL_SECTION
    relCriticalSection(env,dims,offset,ndims,(void**)&_dims,sizeof(jint),JNI_COMMIT);
#endif

}