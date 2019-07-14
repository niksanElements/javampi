#include "mpi_Cart.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Cart
 * Method:    _dims
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL 
Java_mpi_Cart__1dims(
    JNIEnv *env, jclass class, jlong comm)
{
    int size;

    MPI_Cartdim_get((MPI_Comm)comm,&size);

    return size;
}