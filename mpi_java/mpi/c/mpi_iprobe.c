#include "mpi_Comm.h"
#include "jni_mpi.h"
#include "jni_mpi_status.h"

/*
 * Class:     mpi_Comm
 * Method:    _iprobe
 * Signature: (IIJ)Lmpi/Status;
 */
JNIEXPORT jobject JNICALL 
Java_mpi_Comm__1iprobe(
    JNIEnv *env, 
    jclass class, 
    jint source, 
    jint tag, 
    jlong comm)
{
    int result;
    int flag;
    MPI_Status stat;

    result = MPI_Iprobe(source,tag,(MPI_Datatype)comm,&flag,&stat);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Iprobe");
        return NULL;
    }

    return (*env)->NewObject(env,gJniStatusClass,
        gJniStatusConstructorReq,stat.count_lo,
        stat.count_hi_and_cancelled,stat.MPI_SOURCE,
        stat.MPI_TAG,stat.MPI_ERROR,JNI_TRUE);
}
