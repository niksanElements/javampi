#include "mpi_Group.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Group
 * Method:    _translate_ranks
 * Signature: (JII[IJI[I)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Group__1translate_1ranks(
    JNIEnv *env, jclass class, jlong group1, jint offset1, jint n, 
    jintArray ranks1, jlong group2, jint offset2, jintArray ranks2)
{
    jint *_ranks1;
    jint *_ranks2;
    int result;
    int size;

#ifdef JNI_REGION_COPY
    // if the buffer is DirectBuffer
    // allocate _buff
    size = sizeof(jint);
    if(size != -1){
        _ranks1 = malloc(size*n);
        _ranks2 = malloc(size*n);
    }
    else{
        return -1;
    }
    
    if(_ranks1 == NULL){
        jniOutOfMemoryException(env,"malloc");
        return -1;
    }
    if(_ranks2 == NULL){
        free(_ranks1);
        jniOutOfMemoryException(env,"malloc");
        return -1;
    }
    getIntRegion(env,ranks1,offset1,n,(void**)&_ranks1,0);
    getIntRegion(env,ranks2,offset2,n,(void**)&_ranks2,0);
#elif defined JNI_CRITICAL_SECTION
    getCriticalSection(env,ranks1,offset1,n,(void**)&_ranks1,sizeof(jint),0);
    getCriticalSection(env,ranks2,offset2,n,(void**)&_ranks2,sizeof(jint),0);
#endif

    result = MPI_Group_translate_ranks((MPI_Group)group1,n,_ranks1,(MPI_Group)group2,_ranks2);
    // TODO: check for exception
    
#ifdef JNI_REGION_COPY
    free(_ranks1);
    free(_ranks2)
#elif defined JNI_CRITICAL_SECTION
    relCriticalSection(env,ranks1,offset1,n,(void**)&_ranks1,sizeof(jint),JNI_ABORT);
    relCriticalSection(env,ranks2,offset2,n,(void**)&_ranks2,sizeof(jint),JNI_COMMIT);
#endif

}