#include "mpi_Info.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Info
 * Method:    _get_nthkey
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL 
Java_mpi_Info__1get_1nthkey(
    JNIEnv *env, jclass class, jlong info, jint n)
{
    char key[MPI_MAX_INFO_KEY];
    int result;

    result = MPI_Info_get_nthkey((MPI_Info)info,n,key);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Info_get");
        return NULL;
    }

    return (*env)->NewStringUTF(env,key);
}