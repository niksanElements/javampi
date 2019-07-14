#include "jni_mpi_collective.h"

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Scan
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;IIII)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Scan(JNIEnv *env, 
    jclass class,
    jobject sendbuff, 
    jobject recvbuff, 
    jint count, 
    jint type, 
    jint op, 
    jint comm)
{
    FUNCTION_REDBLOCK_SCAN(MPI_Scan);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Iscan
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;IIIILorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Iscan(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jobject recvbuff, 
    jint count, 
    jint type, 
    jint op, 
    jint comm, 
    jobject req)
{
    FUNCTION_IREDBLOCK_SCAN(MPI_Iscan);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Exscan
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;IIII)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Exscan(
    JNIEnv *env, 
    jclass class,
    jobject sendbuff, 
    jobject recvbuff, 
    jint count, 
    jint type, 
    jint op, 
    jint comm)
{
    FUNCTION_REDBLOCK_SCAN(MPI_Exscan);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Iexscan
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;IIIILorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Iexscan(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jobject recvbuff, 
    jint count, 
    jint type, 
    jint op, 
    jint comm, 
    jobject req)
{
    FUNCTION_IREDBLOCK_SCAN(MPI_Iexscan);
}