#include "mpi_Intercomm.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Intercomm
 * Method:    _disconnect
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Intercomm__1disconnect(
    JNIEnv *env, jclass class, jlong comm)
{
    MPI_Comm_disconnect((MPI_Comm*)&comm);

    return comm;
}