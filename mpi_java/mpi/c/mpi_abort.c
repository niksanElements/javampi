#include "mpi_Comm.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Comm
 * Method:    _abort
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Comm__1abort(
    JNIEnv *env, jclass class, jlong comm, jint error)
{
    MPI_Abort((MPI_Comm)comm,error);
}
