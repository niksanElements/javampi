#include "mpi_MPI.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_MPI
 * Method:    _isInitialized
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL 
Java_mpi_MPI__1isInitialized(
    JNIEnv *env, jclass class)
{
    int tag;

    MPI_Initialized(&tag);

    return (jboolean)tag;
}