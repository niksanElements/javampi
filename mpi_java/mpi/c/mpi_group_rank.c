#include "mpi_Group.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Group
 * Method:    _rank
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL 
Java_mpi_Group__1rank(
    JNIEnv *env, jclass class, jlong group)
{
    int result;
    int rank;

    result = MPI_Group_rank((MPI_Group)group,&rank);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Group_rank");
        return -1;
    }

    return rank;
}