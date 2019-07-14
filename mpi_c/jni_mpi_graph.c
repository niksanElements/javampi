#include "jni_mpi.h"
#include "jni_mpi_exception.h"

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Graph_create
 * Signature: (II[I[II)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Graph_1create(
    JNIEnv *env, 
    jclass class, 
    jint comm_old, 
    jint nnodes, 
    jintArray indx, 
    jintArray edges, 
    jint reorder)
{
    int comm_graph;
    int result;
    jint* _indx;
    jint* _edges;

    _indx = (*env)->GetIntArrayElements(env,indx,NULL);
    _edges = (*env)->GetIntArrayElements(env,edges,NULL);

    result = MPI_Graph_create(comm_old,nnodes,_indx,_edges,reorder,
        &comm_graph);
    (*env)->ReleaseIntArrayElements(env,indx,_indx,JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env,edges,_edges,JNI_ABORT);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return comm_graph;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Dist_graph_create_adjacent
 * Signature: (II[I[II[I[III)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Dist_1graph_1create_1adjacent(
    JNIEnv *env, 
    jclass class, 
    jint comm_old, 
    jint indegree, 
    jintArray sources, 
    jintArray sourceweights, 
    jint outdegree , 
    jintArray destinations, 
    jintArray destweights, 
    jint info, 
    jint reorder)
{
    int result;
    int comm_dist_graph;
    jint* _sources;
    jint* _sourceweights;
    jint* _destinations;
    jint* _destweights;

    _sources = (*env)->GetIntArrayElements(env,sources,NULL);
    _sourceweights = (*env)->GetIntArrayElements(env,sourceweights,
        NULL);
    _destinations = (*env)->GetIntArrayElements(env,destinations,NULL);
    _destweights = (*env)->GetIntArrayElements(env,destweights,NULL);

    result = MPI_Dist_graph_create_adjacent(comm_old,indegree,
        _sources,_sourceweights,outdegree,_destinations,_destweights,
        info,reorder,&comm_dist_graph);
    
    (*env)->ReleaseIntArrayElements(env,sources,_sources,
        JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env,sourceweights,_sourceweights,
        JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env,destinations,_destinations,
        JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env,destweights,_destweights,
        JNI_ABORT);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return comm_dist_graph;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Dist_graph_create
 * Signature: (II[I[I[I[III)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Dist_1graph_1create(
    JNIEnv *env, 
    jclass class, 
    jint comm_old, 
    jint n,
    jintArray sources, 
    jintArray degrees, 
    jintArray destinations, 
    jintArray weights, 
    jint info, 
    jint reorder)
{
    int result;
    int comm_dist_graph;
    jint* _sources;
    jint* _degrees;
    jint* _destinations;
    jint* _weights;
    _sources = (*env)->GetIntArrayElements(env,sources,NULL);
    _degrees = (*env)->GetIntArrayElements(env,degrees,NULL);
    _destinations = (*env)->GetIntArrayElements(env,destinations,
        NULL);
    _weights = (*env)->GetIntArrayElements(env,weights,NULL);

    result = MPI_Dist_graph_create(comm_old,n,_sources,_degrees,
        _destinations,_weights,info,reorder,&comm_dist_graph);
    
    (*env)->ReleaseIntArrayElements(env,sources,_sources,
        JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env,degrees,_degrees,
        JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env,destinations,_destinations,
        JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env,weights,_weights,
        JNI_ABORT);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return comm_dist_graph;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Graphdims_get
 * Signature: (ILorg/mpich/MPI_Integer_ref;Lorg/mpich/MPI_Integer_ref;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Graphdims_1get(
    JNIEnv *env, 
    jclass class, 
    jint comm, 
    jobject nnodes, 
    jobject nedges)
{
    int result;
    int _nnodes;
    int __nedges;

    result = MPI_Graphdims_get(comm,&_nnodes,&__nedges);
    (*env)->SetIntField(env,nedges,JNI_MPI_INTEGER_VALUE,_nnodes);
    (*env)->SetIntField(env,nedges,JNI_MPI_INTEGER_VALUE,__nedges);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Graph_get
 * Signature: (III[I[I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Graph_1get(
    JNIEnv *env, 
    jclass class, 
    jint comm, 
    jint maxindex,
    jint maxedges, 
    jintArray indx, 
    jintArray edges)
{
    int result;
    jint* _indx;
    jint* _edges;
    _indx = (*env)->GetIntArrayElements(env,indx,NULL);
    _edges = (*env)->GetIntArrayElements(env,edges,NULL);

    result = MPI_Graph_get(comm,maxindex,maxedges,_indx,_edges);

    (*env)->ReleaseIntArrayElements(env,indx,_indx,JNI_COMMIT);
    (*env)->ReleaseIntArrayElements(env,edges,_edges,JNI_COMMIT);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Graph_neighbors_count
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Graph_1neighbors_1count(
    JNIEnv *env, 
    jclass class, 
    jint comm, 
    jint rank)
{
    int neighbors;
    int result;

    result = MPI_Graph_neighbors_count(comm,rank,&neighbors);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return neighbors;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Graph_neighbors
 * Signature: (III[I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Graph_1neighbors(
    JNIEnv *env, 
    jclass class, 
    jint comm, 
    jint rank, 
    jint maxneighbors, 
    jintArray neighbors)
{
    int result;
    jint* _neighbors;

    _neighbors = (*env)->GetIntArrayElements(env,neighbors,NULL);
    result = MPI_Graph_neighbors(comm,rank,maxneighbors,_neighbors);
    (*env)->ReleaseIntArrayElements(env,neighbors,_neighbors,
        JNI_COMMIT);
    
    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Dist_graph_neighbors_count
 * Signature: (ILorg/mpich/MPI_Integer_ref;Lorg/mpich/MPI_Integer_ref;Lorg/mpich/MPI_Integer_ref;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Dist_1graph_1neighbors_1count(
    JNIEnv *env, 
    jclass class, 
    jint comm, 
    jobject indegree, 
    jobject outdegree, 
    jobject weighted)
{
    int result;
    int _indegree;
    int _outdegree;
    int _weighted;

    result = MPI_Dist_graph_neighbors_count(comm,&_indegree,
        &_outdegree,&_weighted);
    
    (*env)->SetIntField(env,indegree,JNI_MPI_INTEGER_VALUE,_indegree);
    (*env)->SetIntField(env,outdegree,JNI_MPI_INTEGER_VALUE,_outdegree);
    (*env)->SetIntField(env,weighted,JNI_MPI_INTEGER_VALUE,_weighted);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Dist_graph_neighbors
 * Signature: (II[I[II[I[I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Dist_1graph_1neighbors(
    JNIEnv *env, 
    jclass class, 
    jint comm, 
    jint maxindegree, 
    jintArray sources, 
    jintArray sourceweights, 
    jint maxoutdegree, 
    jintArray destinations, 
    jintArray destweights)
{
    int result;
    jint* _sources;
    jint* _sourceweights;
    jint* _destinations;
    jint* _destweights;
    
    _sources = (*env)->GetIntArrayElements(env,sources,
        NULL);
    _sourceweights = (*env)->GetIntArrayElements(env,sourceweights,
        NULL);
    _destinations = (*env)->GetIntArrayElements(env,destinations,
        NULL);
    _destweights = (*env)->GetIntArrayElements(env,destweights,
        NULL);

    result = MPI_Dist_graph_neighbors(comm,maxindegree,_sources,
        _sourceweights,maxoutdegree,_destinations,_destweights);

    (*env)->ReleaseIntArrayElements(env,sources,_sources,
        JNI_COMMIT);
    (*env)->ReleaseIntArrayElements(env,sourceweights,_sourceweights,
        JNI_COMMIT);
    (*env)->ReleaseIntArrayElements(env,destinations,_destinations,
        JNI_COMMIT);
    (*env)->ReleaseIntArrayElements(env,destweights,_destweights,
        JNI_COMMIT);

    JNI_MPI_RETURN(result);
}
