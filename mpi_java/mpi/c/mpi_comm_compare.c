#include "mpi_Comm.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Comm
 * Method:    _compare
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL 
Java_mpi_Comm__1compare(
    JNIEnv *env, jclass class, jlong comm1, jlong comm2)
{
    int result;
    int tag;

    result = MPI_Comm_compare((MPI_Comm)comm1,(MPI_Comm)comm2,&tag);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Comm_compare");
        return -1;
    }

    return tag;
}
