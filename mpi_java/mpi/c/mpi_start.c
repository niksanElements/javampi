#include "mpi_Request.h"
#include "jni_mpi.h"
#include "jni_mpi_request.h"

/*
 * Class:     mpi_Request
 * Method:    _start
 * Signature: (J)V
 */
JNIEXPORT void JNICALL
Java_mpi_Request__1start(
    JNIEnv *env, 
    jclass class, 
    jlong req)
{
    int result;
    tJniRequest* request = (tJniRequest*)req;
    result = MPI_Start(&request->request);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Start");
    }
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
}