#include "mpi_Win.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Win
 * Method:    _lock
 * Signature: (IIIJ)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Win__1lock(
    JNIEnv *env, jclass class, jint lock_type, jint rank, jint _assert, jlong win)
{
  int result;

  result = MPI_Win_lock(lock_type,rank,_assert,(MPI_Win)win);
  if(result != MPI_SUCCESS){
    mpiErr(env,result,"MPI_Win_lock");
  }
}

/*
 * Class:     mpi_Win
 * Method:    _lock_all
 * Signature: (IJ)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Win__1lock_1all(
  JNIEnv *env, jclass class, jint _assert, jlong win)
{
  int result;

  result = MPI_Win_lock_all(_assert,(MPI_Win)win);
  if(result != MPI_SUCCESS){
    mpiErr(env,result,"MPI_Win_lock_all");
  }
}
