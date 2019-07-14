#include "mpi_Intracomm.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Intracomm
 * Method:    _create_group
 * Signature: (JJI)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Intracomm__1create_1group(
    JNIEnv *env, jclass class, jlong comm, jlong group,jint tag)
{
    jlong new_comm = 0;
    int result;

    result = MPI_Comm_create_group((MPI_Comm)comm,(MPI_Group)group,tag,
        (MPI_Comm*)&new_comm);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Comm_create_group");
        return -1;
    }

    return new_comm;
}

