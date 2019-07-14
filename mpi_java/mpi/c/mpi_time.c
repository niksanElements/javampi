#include "mpi_MPI.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_MPI
 * Method:    _wtime
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL 
Java_mpi_MPI__1wtime(
    JNIEnv *env, jclass class)
{
    return MPI_Wtime();
}

/*
 * Class:     mpi_MPI
 * Method:    _wtick
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL 
Java_mpi_MPI__1wtick(
    JNIEnv *env, jclass class)
{
    return MPI_Wtick();
}