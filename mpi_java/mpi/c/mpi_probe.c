#include "mpi_Comm.h"
#include "jni_mpi_status.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Comm
 * Method:    _probe
 * Signature: (IIJ)Lmpi/Status;
 */
JNIEXPORT jobject JNICALL 
Java_mpi_Comm__1probe(
    JNIEnv *env, 
    jclass class, 
    jint source, 
    jint tag, 
    jlong comm)
{
    int result;
    MPI_Status stat;

    result = MPI_Probe(source,tag,(MPI_Comm)comm,&stat);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Probe");
        return NULL;
    }

    return (*env)->NewObject(env,gJniStatusClass,gJniStatusConstructor,
        stat.count_lo,stat.count_hi_and_cancelled,
        stat.MPI_SOURCE,stat.MPI_TAG,stat.MPI_ERROR);
}