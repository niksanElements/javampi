#include "mpi_Win.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Win
 * Method:    _free
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Win__1free(
    JNIEnv *env, jclass clas, jlong win)
{
    int result;

    result = MPI_Win_free((MPI_Win*)&win);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Win_free");
    }

    return win;
}