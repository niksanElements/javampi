#include "mpi_Graph.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Graph
 * Method:    _neighbors_count
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL 
Java_mpi_Graph__1neighbors_1count(
    JNIEnv *env, jclass class, jlong comm, jint rank)
{
    int result;
    int count;

    result = MPI_Graph_neighbors_count((MPI_Comm)comm,rank,&count);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Graph_neighbors_count");
    }

    return count;
}
