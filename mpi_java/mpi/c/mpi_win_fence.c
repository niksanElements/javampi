#include "mpi_Win.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Win
 * Method:    _fence
 * Signature: (IJ)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Win__1fence(
    JNIEnv *env, jclass class, jint assert, jlong win)
{
    int result;

    result = MPI_Win_fence(assert,(MPI_Win)win);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Win_fence");
    }
}