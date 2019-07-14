#include "jni_mpi.h"
#include "jni_mpi_exception.h"

JNIEXPORT jint JNICALL
Java_org_mpich_MPI_MPI_1Comm_1rank(JNIEnv *env, jclass obj,jint comm)
{
    int rank;

    MPI_Comm_rank(comm,&rank);

    return rank;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_size
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Comm_1size(
    JNIEnv *env, jclass class, jint comm)
{
    int size;

    int result = MPI_Comm_size(comm,&size);

    fn_exit:
        if(result != MPI_SUCCESS){
            jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
        }
        return size;
    fn_fail:
        return -1;
}