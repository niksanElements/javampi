#include "mpi_Group.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Group
 * Method:    _difference
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Group__1difference(
    JNIEnv *env, jclass class, jlong group1, jlong group2)
{
    long new_group = 0;
    int result;

    result = MPI_Group_difference((MPI_Group)group1,(MPI_Group)group2,
        (MPI_Group*)&new_group);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Group_difference");
        return -1;
    }

    return new_group;
}