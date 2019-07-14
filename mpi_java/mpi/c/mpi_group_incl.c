#include "mpi_Group.h"
#include "jni_mpi.h"

#include "malloc.h"

/*
 * Class:     mpi_Group
 * Method:    _incl
 * Signature: (JII[I)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Group__1incl(
    JNIEnv *env, jclass class, jlong group, jint offset, jint n, jintArray ranks)
{
    void *buff;
    int size;
    int result;
    long new_group;

#ifdef JNI_REGION_COPY
    // if the buffer is DirectBuffer
    // allocate _buff
    size = sizeof(jint);
    if(size != -1){
        buff = malloc(size*n);
    }
    else{
        return -1;
    }
    
    if(buff == NULL){
        jniOutOfMemoryException(env,"malloc");
        return -1;
    }
    getIntRegion(env,ranks,offset,n,&buff,0);
#elif defined JNI_CRITICAL_SECTION
    getCriticalSection(env,ranks,offset,n,&buff,sizeof(jint),0);
#endif

    // jint* v = (jint*)buff;

    // for(int i = 0;i < n;i++){
    //     printf("-------------- %d\n",v[i]);
    // }

    result = MPI_Group_incl((MPI_Group)group,n,(jint*)buff,
        (MPI_Group*)&new_group);
    // TODO: check for exception
    
#ifdef JNI_REGION_COPY
    free(buff);
#elif defined JNI_CRITICAL_SECTION
    relCriticalSection(env,ranks,offset,n,&buff,sizeof(jint),JNI_ABORT);
#endif

    return new_group;
}