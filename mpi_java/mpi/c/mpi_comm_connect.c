#include "mpi_Intracomm.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Intracomm
 * Method:    _connect
 * Signature: (Ljava/lang/String;JIJ)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Intracomm__1connect(
    JNIEnv *env, jclass class, jstring portname, jlong info, jint root, jlong comm)
{
    long new_comm = 0;
    int result;
    const char *_portname;

    _portname = (*env)->GetStringUTFChars(env,portname,NULL);
    if(_portname == NULL){
        return -1;
    }

    result = MPI_Comm_connect(_portname,(MPI_Info)info,root,(MPI_Comm)comm,(MPI_Comm*)&new_comm);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Comm_connect");
    }

    (*env)->ReleaseStringUTFChars(env,portname,_portname);

    return new_comm;
}