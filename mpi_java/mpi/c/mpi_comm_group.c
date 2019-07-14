#include "mpi_Comm.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Comm
 * Method:    _group
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Comm__1group(
    JNIEnv *env, jclass class, jlong comm)
{
    long group;
    int result;

    result = MPI_Comm_group((MPI_Comm)comm,(MPI_Group*)&group);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Comm_group");
        return -1;
    }

    return group;
}
