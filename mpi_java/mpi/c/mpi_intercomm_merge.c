#include "mpi_Intercomm.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Intercomm
 * Method:    _merge
 * Signature: (JZ)J
 */
JNIEXPORT jlong JNICALL
Java_mpi_Intercomm__1merge(
    JNIEnv *env, jclass class, jlong intercomm, jboolean high)
{
    int result;
    long new_comm = 0;

    result = MPI_Intercomm_merge((MPI_Comm)intercomm,high,(MPI_Comm*)&new_comm);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Intercomm_merge");
        return -1;
    }

    return new_comm;
}