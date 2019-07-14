#include "mpi_Info.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Info
 * Method:    _dup
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Info__1dup(
    JNIEnv *env, jclass class, jlong info)
{
    int result;
    long new_info = 0;

    result = MPI_Info_dup((MPI_Info)info,(MPI_Info*)&new_info);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Info_dup");
        return -1;
    }

    return new_info;
}