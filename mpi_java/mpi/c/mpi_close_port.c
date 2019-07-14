#include "mpi_MPI.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_MPI
 * Method:    _close_port
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL 
Java_mpi_MPI__1close_1port(
    JNIEnv *env, jclass class, jstring portname)
{   
    const char *_portname;

    _portname = (*env)->GetStringUTFChars(env,portname,NULL);
    if(_portname == NULL){
        return;
    }

    MPI_Close_port(_portname);

    (*env)->ReleaseStringUTFChars(env,portname,_portname);
}