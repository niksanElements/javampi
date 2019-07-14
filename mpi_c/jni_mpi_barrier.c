#include "jni_mpi.h"
#include "jni_mpi_exception.h"

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Barrier
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Barrier(
    JNIEnv *env, 
    jclass class, 
    jint comm)
{
    int result = MPI_Barrier(comm);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Ibarrier
 * Signature: (ILorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Ibarrier(
    JNIEnv *env, 
    jclass class, 
    jint comm, 
    jobject request)
{
    int result;
    MPI_Request req;

    result = MPI_Ibarrier(comm,&req);
    (*env)->SetIntField(env,request,JNI_MPI_REQUEST_HANDLER,req);

    JNI_MPI_RETURN(result);
}

