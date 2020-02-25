#include "jni_mpi.h"
#include "jni_mpi_exception.h"

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Cancel
 * Signature: (Lorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Cancel(
    JNIEnv *env, 
    jclass class, 
    jobject request)
{
    MPI_Request req;
    int result;

    req = (*env)->GetIntField(env,request,JNI_MPI_REQUEST_HANDLER);
    result = MPI_Cancel(&req);

    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }
    return result;
}

void some()
{
    MPI_Comm comm; // Communicator
    MPI_Datatype datatype; // Datatype
    MPI_Op operation; // Operation
    MPI_Request req; // Request
    MPI_File file; // File
    ...
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Test_cancelled
 * Signature: (Lorg/mpich/MPI_Status;)Z
 */
JNIEXPORT jboolean JNICALL 
Java_org_mpich_MPI_MPI_1Test_1cancelled(
    JNIEnv *env, 
    jclass class, 
    jobject status)
{
    MPI_Status stat;
    int result;
    int flag;

    jni_mpi_convert_MPI_Status(env,status,&stat,
        FROM_JAVA_MPI_STATUS_TO_MPI_STATUS);
    
    result = MPI_Test_cancelled(&stat,&flag);

    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    if(flag == 1){
        return JNI_TRUE;
    }
    else{
        return JNI_FALSE;
    }
}

