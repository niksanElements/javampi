#include "jni_mpi.h"
#include "jni_mpi_exception.h"

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Get_version
 * Signature: ()I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Get_1version(
    JNIEnv *env, jclass class)
{
    // TODO: desont make sense
    return -1;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Get_library_version
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL 
Java_org_mpich_MPI_MPI_1Get_1library_1version(
    JNIEnv *env, 
    jclass class)
{
    char version[MPI_MAX_LIBRARY_VERSION_STRING];
    int length;
    int result;

    result = MPI_Get_library_version(version,&length);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return (*env)->NewStringUTF(env,version);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Get_process_name
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL 
Java_org_mpich_MPI_MPI_1Get_1process_1name(
    JNIEnv *env, 
    jclass class)
{
    int result;
    int length;
    char name[MPI_MAX_PROCESSOR_NAME];

    result = MPI_Get_processor_name(name,&length);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return (*env)->NewStringUTF(env,name);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Wtime
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL 
Java_org_mpich_MPI_MPI_1Wtime(
    JNIEnv *env, 
    jclass class)
{
    return MPI_Wtime();
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Wtick
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL 
Java_org_mpich_MPI_MPI_1Wtick(
    JNIEnv *env, 
    jclass class)
{
    return MPI_Wtick();
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Initialized
 * Signature: ()I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Initialized(
    JNIEnv *env, 
    jclass class)
{
    int result;
    int flag;

    result = MPI_Initialized(&flag);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return flag;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Abort
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Abort(
    JNIEnv *env, 
    jclass class, 
    jint comm, 
    jint errorcode)
{
    int result = MPI_Abort(comm,errorcode);
    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Finalized
 * Signature: ()I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Finalized(
    JNIEnv *env, 
    jclass class)
{
    int result;
    int flag;

    result = MPI_Finalized(&flag);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return flag;
}
