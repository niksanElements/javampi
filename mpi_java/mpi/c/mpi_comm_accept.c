#include "mpi_Intracomm.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Intracomm
 * Method:    _accept
 * Signature: (Ljava/lang/String;JIJ)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Intracomm__1accept(
    JNIEnv *env, jclass class, jstring portname, jlong info, jint root, jlong comm)
{
    const char *_portname;
    int result;
    jlong new_comm = 0;


    _portname = (*env)->GetStringUTFChars(env,portname,NULL);
    if(_portname == NULL){
        return -1;
    }

    result = MPI_Comm_accept(_portname,(MPI_Info)info,root,(MPI_Comm)comm,(MPI_Comm*)&new_comm);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Comm_accept");
    }

    (*env)->ReleaseStringUTFChars(env,portname,_portname);

    return new_comm;
}