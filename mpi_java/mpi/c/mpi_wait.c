#include "jni_mpi.h"
#include "mpi_Request.h"
#include "jni_mpi_request.h"
#include "jni_mpi_status.h"

#include "malloc.h"

/*
 * Class:     mpi_Request
 * Method:    _wait
 * Signature: (J)Lmpi/Status;
 */
JNIEXPORT jobject JNICALL 
Java_mpi_Request__1wait(
    JNIEnv *env, 
    jclass class, 
    jlong req)
{
    tJniRequest *request = (tJniRequest*)req;
    MPI_Status stat;
    int result;

    result = MPI_Wait(&request->request,&stat);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Wait");
        return NULL;
    }
    // We are deliting the request if it isn't a persistent one!
    if(!request->isPersistentRequest){
        jniMpiRequestFree(env,request);
    }

    return (*env)->NewObject(env,gJniStatusClass,
        gJniStatusConstructorReq,stat.count_lo,
        stat.count_hi_and_cancelled,stat.MPI_SOURCE,
        stat.MPI_TAG,stat.MPI_ERROR,JNI_TRUE);
}

