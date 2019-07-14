#include "mpi_Win.h"
#include "jni_mpi.h"

// TODO: test them

/*
 * Class:     mpi_Win
 * Method:    _flush
 * Signature: (IJ)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Win__1flush(
    JNIEnv *env, jclass class, jint rank , jlong win)
{
    int result = MPI_Win_flush(rank,(MPI_Win)win);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Win_flush");
    }
}

/*
 * Class:     mpi_Win
 * Method:    _flush_all
 * Signature: (J)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Win__1flush_1all(
    JNIEnv *env, jclass class, jlong win)
{
    int result = MPI_Win_flush_all((MPI_Win)win);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Win_flush_all");
    }
}

/*
 * Class:     mpi_Win
 * Method:    _flush_local
 * Signature: (IJ)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Win__1flush_1local(
    JNIEnv *env, jclass class, jint rank, jlong win)
{
    int result = MPI_Win_flush_local(rank,(MPI_Win)win);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Win_flush_local");
    }
}

/*
 * Class:     mpi_Win
 * Method:    _flush_local_all
 * Signature: (J)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Win__1flush_1local_1all(
    JNIEnv *env, jclass class, jlong win)
{
    int result = MPI_Win_flush_local_all((MPI_Win)win);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Win_flush_local_all");
    }
}