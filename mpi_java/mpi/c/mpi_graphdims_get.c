#include "mpi_Graph.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Intracomm
 * Method:    _get_graphdims
 * Signature: (JZ)I
 */
JNIEXPORT jint JNICALL 
Java_mpi_Graph__1get_1graphdims(
    JNIEnv *env, jclass class, jlong comm, jboolean isEdges)
{
    int edges;
    int nodes;
    int result;

    result = MPI_Graphdims_get((MPI_Comm)comm,&nodes,&edges);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Graphdims_get");
        return -1;
    }

    if(isEdges == JNI_TRUE){
        return edges;
    }
    
    return nodes;
}