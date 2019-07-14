#include "jni_mpi.h"

JNIEXPORT jint JNICALL
Java_org_mpich_MPI_MPI_1Finalize(JNIEnv *env, jclass obj)
{
    return MPI_Finalize();
}