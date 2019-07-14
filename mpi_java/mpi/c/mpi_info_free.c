#include "mpi_Info.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Info
 * Method:    _free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Info__1free(
    JNIEnv *env, jclass class, jlong info)
{
    int result = MPI_Info_free((MPI_Info*)&info);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Info_free");
    }
}