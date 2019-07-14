#include "mpi_Intercomm.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Intercomm
 * Method:    _remote_group
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Intercomm__1remote_1group(
    JNIEnv *env, jclass class, jlong comm)
{
    int result;
    long group = 0;

    result = MPI_Comm_remote_group((MPI_Comm)comm,(MPI_Group*)&group);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Comm_remote_group");
        return -1;
    }

    return group;
}