#include "mpi_Comm.h"
#include "jni_mpi.h"
#include "jni_mpi_message.h"

/*
 * Class:     mpi_Comm
 * Method:    _improbe
 * Signature: (IIJ)Lmpi/Message;
 */
JNIEXPORT jobject JNICALL 
Java_mpi_Comm__1improbe(
    JNIEnv *env, 
    jclass class, 
    jint source, 
    jint tag, 
    jlong comm)
{
    MPI_Message msg;
    MPI_Status stat;
    int flag;

    int result = MPI_Improbe(source,tag,(MPI_Comm)comm,&flag,&msg,&stat);

    // construct a message Object
    return newJniMpiMessage(env,&msg,&stat,(jboolean)flag);
}