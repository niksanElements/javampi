#include "mpi_Info.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Info
 * Method:    _get
 * Signature: (JLjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL 
Java_mpi_Info__1get(
    JNIEnv *env, jclass class, jlong info, jstring key)
{
    const char *_key;
    char value[MPI_MAX_INFO_VAL];
    int result;
    int flag;

    _key = (*env)->GetStringUTFChars(env,key,NULL);  

    result = MPI_Info_get((MPI_Info)info,_key,MPI_MAX_INFO_VAL,value,&flag);

    (*env)->ReleaseStringUTFChars(env,key,_key); 

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Info_get");
        return NULL;
    }

    return (*env)->NewStringUTF(env,value);
}