#include "mpi_MPI.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_MPI
 * Method:    _parent
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_MPI__1parent(
    JNIEnv *env, jclass class)
{
    long new_comm = 0;

    MPI_Comm_get_parent((MPI_Comm*)&new_comm);

    return new_comm;
}
