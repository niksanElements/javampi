#include "mpi_MPI.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_MPI
 * Method:    _processor_name
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL 
Java_mpi_MPI__1processor_1name(
    JNIEnv *env, jclass class)
{
    char proc_name[MPI_MAX_PROCESSOR_NAME];
    int len;

    MPI_Get_processor_name(proc_name,&len);

    return (*env)->NewStringUTF(env,proc_name);
}