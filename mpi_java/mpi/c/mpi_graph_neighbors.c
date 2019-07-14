#include "mpi_Graph.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Graph
 * Method:    _neighbors
 * Signature: (JIII[I)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Graph__1neighbors(
    JNIEnv *env, jclass class, jlong comm, 
        jint rank, jint offset, jint maxneighbors, jintArray neighbors)
{
    int result;
    jint *_neighbors;
    int size;

#ifdef JNI_REGION_COPY  
    // if the buffer is DirectBuffer
    // allocate _buff
    size = sizeof(jint);
    _neighbors = malloc(size*maxneighbors);
    
    if(_neighbors == NULL){
        jniOutOfMemoryException(env,"malloc");
        return -1;
    }
#elif defined JNI_CRITICAL_SECTION
    getCriticalSection(env,neighbors,offset,maxneighbors,
        (void**)&_neighbors,sizeof(jint),0);
#endif

    result = MPI_Graph_neighbors((MPI_Comm)comm,rank,maxneighbors,_neighbors);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Graph_neighbors");
    }

#ifdef JNI_REGION_COPY
    setIntRegion(env,neighbors,offset,maxneighbors,(void**)&_neighbors,JNI_COMMIT);
    free(_neighbors);
#elif defined JNI_CRITICAL_SECTION
    relCriticalSection(env,neighbors,offset,maxneighbors,
        (void**)&_neighbors,sizeof(jint),JNI_COMMIT);
#endif

}