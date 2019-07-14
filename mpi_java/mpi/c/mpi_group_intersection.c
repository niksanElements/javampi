#include "mpi_Group.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Group
 * Method:    _intersection
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Group__1intersection(
    JNIEnv *env, jclass class, jlong group1, jlong group2)
{
    long new_group = 0;
    int result;

    result = MPI_Group_intersection((MPI_Group)group1,(MPI_Group)group2,
        (MPI_Group*)&new_group);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Group_intersection");
        return -1;
    }

    return new_group;
}