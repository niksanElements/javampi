#include "mpi_Comm.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Comm
 * Method:    _dup
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Comm__1dup(
    JNIEnv *env, jclass class, jlong comm)
{
    long new_comm = 0;
    int result;

    result = MPI_Comm_dup((MPI_Comm)comm,(MPI_Comm*)&new_comm);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Comm_dup");
        return -1;
    }

    return new_comm;
}