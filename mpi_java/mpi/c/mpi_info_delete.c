#include "mpi_Info.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Info
 * Method:    _delete
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Info__1delete(
    JNIEnv *env, jclass class,jlong info, jstring key)
{
    const char *_key;

    _key = (*env)->GetStringUTFChars(env,key,NULL);   

    MPI_Info_delete((MPI_Info)info,_key);

    (*env)->ReleaseStringUTFChars(env,key,_key); 
}