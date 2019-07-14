#include "mpi_Request.h"
#include "jni_mpi.h"
#include "jni_mpi_request.h"

/*
 * Class:     mpi_Request
 * Method:    _free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Request__1free(
    JNIEnv *env, 
    jclass class, 
    jlong req)
{
    tJniRequest *request = (tJniRequest*)req;
    int result;

    result = MPI_Request_free(&request->request);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Request_free");
        return;
    }
    jniMpiRequestFree(env,request);
}

