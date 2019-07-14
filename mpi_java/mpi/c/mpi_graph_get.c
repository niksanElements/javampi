#include "mpi_Graph.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Graph
 * Method:    _graph_get
 * Signature: (JIIII[I[I)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Graph__1graph_1get(
    JNIEnv *env, jclass class, jlong comm, jint offsetindxes, jint maxindxes, 
    jint offsetedges , jint maxedges, jintArray indxes, jintArray edges)
{
    int size;
    int result;
    jint *_indexes,*_edges;

#ifdef JNI_REGION_COPY
    // if the buffer is DirectBuffer
    // allocate _buff
    size = sizeof(jint);
    _indexes = malloc(size*maxindxes);

    if(_indexes == NULL){
        jniOutOfMemoryException(env,"malloc");
        return;
    }
    _edges = malloc(size*maxedges);
    if(_edges == NULL){
        free(_indexes);
        jniOutOfMemoryException(env,"malloc");
        return;
    }

#elif defined JNI_CRITICAL_SECTION
    getCriticalSection(env,indxes,offsetindxes,maxindxes,(void**)&_indexes,sizeof(jint),0);
    getCriticalSection(env,edges,offsetedges,maxedges,(void**)&_edges,sizeof(jint),0);
#endif
    result = MPI_Graph_get((MPI_Comm)comm,maxindxes,maxedges,_indexes,_edges);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_cart_get");
    }

#ifdef JNI_REGION_COPY
    setIntRegion(env,indxes,offsetindxes,maxindxes,(void**)&_indexes,JNI_COMMIT);
    free(_indexes);
    setIntRegion(env,edges,offsetedges,maxedges,(void**)&_edges,JNI_COMMIT);
    free(_edges);
#elif defined JNI_CRITICAL_SECTION
    relCriticalSection(env,indxes,offsetindxes,maxindxes,(void**)&_indexes,sizeof(jint),JNI_COMMIT);
    relCriticalSection(env,edges,offsetedges,maxedges,(void**)&_edges,sizeof(jint),JNI_COMMIT);
#endif
}