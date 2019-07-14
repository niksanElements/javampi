#include "mpi_Comm.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Comm
 * Method:    _free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Comm__1free(
    JNIEnv *env, jclass class, jlong comm)
{
    int result;

    result = MPI_Comm_free((MPI_Comm*)&comm);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Comm_free");
        return;
    }
}