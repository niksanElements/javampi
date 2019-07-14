#include "mpi_Request.h"
#include "jni_mpi.h"
#include "jni_mpi_status.h"
#include "jni_mpi_request.h"

/*
 * Class:     mpi_Request
 * Method:    _get_status
 * Signature: (J)Lmpi/Status;
 */
JNIEXPORT jobject JNICALL 
Java_mpi_Request__1get_1status(
    JNIEnv *env, 
    jclass class, 
    jlong req)
{
    MPI_Status stat;
    int result;
    tJniRequest* request = (tJniRequest*)req;
    int flag;

    result = MPI_Request_get_status(request->request,&flag,&stat);
    // there is no error code

     return (*env)->NewObject(env,gJniStatusClass,
            gJniStatusConstructorReq,stat.count_lo,
            stat.count_hi_and_cancelled,stat.MPI_SOURCE,
            stat.MPI_TAG,stat.MPI_ERROR,(jboolean)flag);
}