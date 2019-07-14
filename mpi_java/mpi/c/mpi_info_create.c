#include "mpi_Info.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Info
 * Method:    _create
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Info__1create(
    JNIEnv *env, jclass class)
{
    jlong info = 0;

    MPI_Info_create((MPI_Info*)&info); 

    return info;
}