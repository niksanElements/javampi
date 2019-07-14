#include "mpi_Win.h"
#include "jni_mpi.h"


/*
 * Class:     mpi_Win
 * Method:    _get_group
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL
Java_mpi_Win__1get_1group(
    JNIEnv *env, jclass class, jlong win)
{
    int result;
    long group = 0;

    result = MPI_Win_get_group((MPI_Win)win,(MPI_Group*)&group);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Win_get_group");
    }

    return group;
}