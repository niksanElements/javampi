#include "mpi_Request.h"
#include "jni_mpi.h"
#include "jni_mpi_request.h"

/*
 * Class:     mpi_Request
 * Method:    _cancel
 * Signature: (J)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Request__1cancel(
    JNIEnv *env, 
    jclass class, 
    jlong req)
{
    tJniRequest* request = (tJniRequest*)req;
    int result;

    result = MPI_Cancel(&request->request);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Cancel");
        return;
    }

    jniMpiRequestFree(env,request);
}