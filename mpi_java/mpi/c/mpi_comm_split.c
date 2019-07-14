#include "mpi_Intracomm.h"
#include "jni_mpi.h"


/*
 * Class:     mpi_Intracomm
 * Method:    _split
 * Signature: (JII)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Intracomm__1split(
    JNIEnv *env, jclass class, jlong comm, jint color, jint key)
{
    long new_comm = 0;
    int result;

    result = MPI_Comm_split((MPI_Comm)comm,color,key,(MPI_Comm*)&new_comm);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Comm_split");
        return -1;
    }


    return new_comm;
}

/*
 * Class:     mpi_Intracomm
 * Method:    _split_type
 * Signature: (JIIJ)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Intracomm__1split_1type(
    JNIEnv *env, jclass class, jlong comm, jint split_type, jint key, jlong info)
{
    long new_comm = 0;
    int result;

    result = MPI_Comm_split_type((MPI_Comm)comm,split_type,key,(MPI_Info)info,(MPI_Comm*)&new_comm);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Comm_split_type");
        return -1;
    }


    return new_comm;
}