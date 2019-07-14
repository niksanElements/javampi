#include "mpi_Info.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Info
 * Method:    _set
 * Signature: (JLjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Info__1set(
    JNIEnv *env, jclass class, jlong info, jstring key, jstring value)
{
    const char *_key;
    const char *_value;
    int result;

    _key = (*env)->GetStringUTFChars(env,key,NULL); 
    _value = (*env)->GetStringUTFChars(env,value,NULL); 

    result = MPI_Info_set((MPI_Info)info,_key,_value);

    (*env)->ReleaseStringUTFChars(env,key,_key); 
    (*env)->ReleaseStringUTFChars(env,value,_value);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Info_get");
    }
}