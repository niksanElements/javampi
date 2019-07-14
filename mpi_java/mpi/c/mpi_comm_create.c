#include "mpi_Intracomm.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Intracomm
 * Method:    _create
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Intracomm__1create(
    JNIEnv *env, jclass class, jlong comm, jlong group)
{
    long new_comm = 0;
    int result;

    result = MPI_Comm_create((MPI_Comm)comm,(MPI_Group)group,
        (MPI_Comm*)&new_comm);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Comm_create");
        return -1;
    }

    return new_comm;
}