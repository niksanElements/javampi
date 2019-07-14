#include "mpi_MPI.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_MPI
 * Method:    _unpublish_name
 * Signature: (Ljava/lang/String;JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL 
Java_mpi_MPI__1unpublish_1name(
    JNIEnv *env, jclass class, jstring servicename, jlong info, jstring portname)
{
    const char *_servicename;
    const char *_portname;

    _servicename = (*env)->GetStringUTFChars(env,servicename,NULL);
    _portname = (*env)->GetStringUTFChars(env,portname,NULL);
    if(_servicename == NULL || _portname == NULL){
        return;
    }

    MPI_Unpublish_name(_servicename,(MPI_Info)info,_portname);

    (*env)->ReleaseStringUTFChars(env,servicename,_servicename);
    (*env)->ReleaseStringUTFChars(env,portname,_portname);
}