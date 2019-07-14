#include "mpi_Win.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Win
 * Method:    _get_info
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Win__1get_1info(
  JNIEnv *env, jclass class, jlong win)
{
  int result;
  long info = 0;

  result = MPI_Win_get_info((MPI_Win)win,(MPI_Info*)&info);

  if(result != MPI_SUCCESS){
    mpiErr(env,result,"MPI_Win_get_info");
  }

  return info;
}