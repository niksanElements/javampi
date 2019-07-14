#include "mpi_Intercomm.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Intercomm
 * Method:    _intercomm_create
 * Signature: (JIJII)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Intercomm__1intercomm_1create(
    JNIEnv *env, jclass class, jlong local_comm, jint local_leader, 
    jlong peek_comm, jint remote_leader, jint tag)
{
    int result;
    long new_comm = 0;

    result = MPI_Intercomm_create((MPI_Comm)local_comm,local_leader,
        (MPI_Comm)peek_comm,remote_leader,tag,(MPI_Comm*)&new_comm);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Intercomm_create");
        return -1;
    }

    return new_comm;
}