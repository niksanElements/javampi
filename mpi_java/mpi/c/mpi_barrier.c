#include "mpi_Comm.h"
#include "jni_mpi.h"
#include "jni_mpi_request.h"

#include "malloc.h"

/*
 * Class:     mpi_Comm
 * Method:    _barrier
 * Signature: (J)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Comm__1barrier(
    JNIEnv *env, 
    jclass class, 
    jlong comm)
{
    int result;

    result = MPI_Barrier((MPI_Comm)comm);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Barrier");
    }
}

/*
 * Class:     mpi_Comm
 * Method:    _ibarrier
 * Signature: (J)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL 
Java_mpi_Comm__1ibarrier(
    JNIEnv *env, 
    jclass class, 
    jlong comm)
{
    int result;
    tJniRequest* req = calloc(1,sizeof(tJniRequest));

    if(req == NULL){
        jniOutOfMemoryException(env,"calloc");
        return NULL;
    }
    result = MPI_Ibarrier((MPI_Comm)comm,&req->request);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Barrier");
    }

    return (*env)->NewObject(env,gJniRequestClass,gJniRequestConstructor,
        (jlong)req);
}