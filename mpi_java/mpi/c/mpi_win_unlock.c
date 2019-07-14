#include "mpi_Win.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Win
 * Method:    _unlock
 * Signature: (IJ)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Win__1unlock(
    JNIEnv *env, jclass class , jint rank, jlong win)
{
    int result;

    result = MPI_Win_unlock(rank,(MPI_Win)win);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Win_unlock");
    }
}

/*
 * Class:     mpi_Win
 * Method:    _unlock_all
 * Signature: (J)V
 */
JNIEXPORT void JNICALL
Java_mpi_Win__1unlock_1all(
    JNIEnv *env, jclass class, jlong win)
{
    int result;

    result = MPI_Win_unlock_all((MPI_Win)win);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Win_unlock_all");
    }
}