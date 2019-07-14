#include "mpi_Info.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Info
 * Method:    _nkeys
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL 
Java_mpi_Info__1nkeys(
    JNIEnv *env, jclass class, jlong info)
{
    int result;
    int size;

    result = MPI_Info_get_nkeys((MPI_Info)info,&size);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Info_get_nkeys");
        return -1;
    }

    return size;
}