#include "mpi_Intracomm.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Intracomm
 * Method:    _graph_create
 * Signature: (JII[II[IZ)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Intracomm__1graph_1create(
    JNIEnv *env, jclass class, jlong comm_old, jint offset_nodes, jint nnodes, 
    jintArray indexes, jint offset_edges, jintArray edges, jboolean reorder)
{
    jint *_indexes,*_edges;
    int size;
    int size_edges;
    int result;
    jlong new_comm = 0;

/**
 * First we have to get the indexes size so that we can
 * determine the size of the  edges.
 */
#ifdef JNI_REGION_COPY
    // if the buffer is DirectBuffer
    // allocate _buff
    size = sizeof(jint);
    _indexes = malloc(size*nnodes);
    
    if(_indexes == NULL){
        jniOutOfMemoryException(env,"malloc");
        return -1;
    }

    getIntRegion(env,indexes,offset_nodes,nnodes,(void**)&_indexes,0);
#elif defined JNI_CRITICAL_SECTION
    getCriticalSection(env,indexes,offset_nodes,nnodes,(void**)&_indexes,sizeof(jint),0);
#endif

    // calculateing the size of the edges
    size_edges = _indexes[0];
    for(int i = 1;i < nnodes;i++){
        size_edges += (_indexes[i]-_indexes[i-1]);
    }

#ifdef JNI_REGION_COPY
    // if the buffer is DirectBuffer
    // allocate _buff
    _edges = malloc(size*size_edges);
    
    if(_edges == NULL){
        jniOutOfMemoryException(env,"malloc");
        return -1;
    }

    getIntRegion(env,edges,offset_edges,size_edges,(void**)&_edges,0);
#elif defined JNI_CRITICAL_SECTION
    getCriticalSection(env,edges,offset_edges,size_edges,(void**)&_edges,sizeof(jint),0);
#endif

    result = MPI_Graph_create((MPI_Comm)comm_old,nnodes,_indexes,_edges,
        (int)reorder,(MPI_Comm*)&new_comm);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_graph_create");
    }

#ifdef JNI_REGION_COPY
    free(_indexes);
    free(_edges);
#elif defined JNI_CRITICAL_SECTION
    relCriticalSection(env,indexes,offset_nodes,nnodes,
        (void**)&_indexes,sizeof(jint),JNI_ABORT);
    relCriticalSection(env,edges,offset_edges,size_edges,
        (void**)&_edges,sizeof(jint),JNI_ABORT);
#endif
    return new_comm;
}