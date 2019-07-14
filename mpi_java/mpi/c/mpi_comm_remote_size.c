#include "mpi_Intercomm.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Intercomm
 * Method:    _remote_size
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL 
Java_mpi_Intercomm__1remote_1size(
    JNIEnv *env, jclass class, jlong comm)
{
    int size = 0;

    MPI_Comm_remote_size((MPI_Comm)comm,&size);
    // TODO: check for errors

    return size;
}