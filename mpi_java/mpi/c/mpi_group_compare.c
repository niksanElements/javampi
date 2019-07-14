#include "mpi_Group.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Group
 * Method:    _compare
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL 
Java_mpi_Group__1compare(
    JNIEnv *env, jclass class, jlong group1, jlong group2)
{
    int result;
    int tag;

    result = MPI_Group_compare((MPI_Group)group1,(MPI_Group)group2,&tag);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Group_compare");
        return -1;
    }

    return tag;
}