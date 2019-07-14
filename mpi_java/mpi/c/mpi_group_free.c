#include "mpi_Group.h"
#include "jni_mpi.h"


/*
 * Class:     mpi_Group
 * Method:    _free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Group__1free(
    JNIEnv *env, jclass class, jlong group)
{
    int result;

    result = MPI_Group_free((MPI_Group*)&group);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Group_free");
        return;
    }
}