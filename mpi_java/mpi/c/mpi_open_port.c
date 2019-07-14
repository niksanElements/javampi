#include "mpi_MPI.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_MPI
 * Method:    _open_port
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL 
Java_mpi_MPI__1open_1port(
    JNIEnv *env, jclass class, jlong info)
{
    char portname[MPI_MAX_PORT_NAME];

    MPI_Open_port((MPI_Info)info,portname);

    return (*env)->NewStringUTF(env,portname);
}
