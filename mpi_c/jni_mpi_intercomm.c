#include "jni_mpi.h"
#include "jni_mpi_exception.h"

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Intercomm_create
 * Signature: (IIIII)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Intercomm_1create(
    JNIEnv *env, 
    jclass class, 
    jint local_comm, 
    jint local_leader, 
    jint peer_comm, 
    jint remote_leader, 
    jint tag)
{
    int result;
    int newcomm;

    result = MPI_Intercomm_create(local_comm,local_leader,
        peer_comm,remote_leader,tag,&newcomm);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return newcomm;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Intercomm_merge
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Intercomm_1merge(
    JNIEnv *env, 
    jclass class, 
    jint intercomm, 
    jint high)
{
    int newintercomm;
    int result;

    result = MPI_Intercomm_merge(intercomm,high,&newintercomm);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return newintercomm;
}
