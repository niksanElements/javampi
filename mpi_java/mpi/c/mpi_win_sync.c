#include "mpi_Win.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Win
 * Method:    _sync
 * Signature: (J)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Win__1sync(
    JNIEnv *env, jclass class, jlong win)
{
    int result = MPI_Win_sync((MPI_Win)win);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Win_sync");
    }
}