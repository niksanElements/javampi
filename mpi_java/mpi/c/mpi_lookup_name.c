#include "mpi_MPI.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_MPI
 * Method:    _lookup_name
 * Signature: (Ljava/lang/String;J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL 
Java_mpi_MPI__1lookup_1name(
    JNIEnv *env, jclass class, jstring servicename, jlong info)
{
    const char* _servicename;
    char portname[MPI_MAX_PORT_NAME];
    int result;

    _servicename = (*env)->GetStringUTFChars(env,servicename,NULL);
    if(_servicename == NULL){
        return NULL;
    }

    result = MPI_Lookup_name(_servicename,(MPI_Info)info,portname);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Lookup_name");
    }

    (*env)->ReleaseStringUTFChars(env,servicename,_servicename);

    return (*env)->NewStringUTF(env,portname);
}