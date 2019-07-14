#include "mpi_Comm.h"
#include "jni_mpi.h"
#include "jni_mpi_message.h"

/*
 * Class:     mpi_Comm
 * Method:    _mprobe
 * Signature: (IIJ)Lmpi/Message;
 */
JNIEXPORT jobject JNICALL 
Java_mpi_Comm__1mprobe(
    JNIEnv *env, 
    jclass class, 
    jint source, 
    jint tag, 
    jlong comm)
{
    MPI_Message msg;
    MPI_Status stat;

    MPI_Mprobe(source,tag,(MPI_Comm)comm,&msg,&stat);

    // construct a message Object
    return newJniMpiMessage(env,&msg,&stat,JNI_TRUE);
}