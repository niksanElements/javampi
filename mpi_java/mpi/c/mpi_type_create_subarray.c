#include "mpi_datatype_Subarray.h"
#include "jni_mpi.h"

#include "malloc.h"

/*
 * Class:     mpi_datatype_Subarray
 * Method:    _create_subarray
 * Signature: (I[I[I[IIJ)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_datatype_Subarray__1create_1subarray(
    JNIEnv *env, jclass class, 
    jint ndims, jintArray sizes, jintArray subsizes, jintArray starts, 
    jint order, jlong old_type)
{
    tJniType *new_type = NULL;
    tJniType *_old_type = (tJniType*)old_type;
    jint *_sizes;
    jint *_subsizes;
    jint *_starts;
    int result;

    // allocate the new type structure memory
    new_type = calloc(1,sizeof(tJniType));
    if(new_type == NULL){
        jniOutOfMemoryException(env,"calloc");
        return -1;
    }

    // get all data
#ifdef JNI_REGION_COPY
    // TODO: Java_mpi_datatype_Subarray__1create_1subarray JNI_REGION_COPY
#elif defined JNI_CRITICAL_SECTION
    getCriticalSection(env,sizes,0,ndims,(void **)&_sizes,sizeof(jint),0);
    getCriticalSection(env,subsizes,0,ndims,(void **)&_subsizes,sizeof(jint),0);
    getCriticalSection(env,starts,0,ndims,(void **)&_starts,sizeof(jint),0);
#endif

    // main call
    result = MPI_Type_create_subarray(ndims,_sizes,_subsizes,_starts,
        order,_old_type->mpi_type,&new_type->mpi_type);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Type_create_subarray");
        free(new_type);
    }

    // get all data
#ifdef JNI_REGION_COPY
    // TODO: Java_mpi_datatype_Subarray__1create_1subarray JNI_REGION_COPY
#elif defined JNI_CRITICAL_SECTION
    relCriticalSection(env,sizes,0,ndims,(void **)&_sizes,sizeof(jint),JNI_ABORT);
    relCriticalSection(env,subsizes,0,ndims,(void **)&_subsizes,sizeof(jint),JNI_ABORT);
    relCriticalSection(env,starts,0,ndims,(void **)&_starts,sizeof(jint),JNI_ABORT);
#endif
    return (jlong)new_type;
}