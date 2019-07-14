#include "mpi_Intracomm.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Intracomm
 * Method:    _topo_test
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL 
Java_mpi_Intracomm__1topo_1test(
    JNIEnv *env, jclass class, jlong comm)
{
    int type;
    int result;

    result = MPI_Topo_test((MPI_Comm)comm,&type);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Topo_test");
        return -1;
    }

    return type;
}