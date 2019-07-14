#include "jni_mpi_comm.h"
#include "mpi_Comm.h"
#include "mpi.h"
#include "jni_mpi_throw.h"
#include "jni_mpi_types.h"


void init_comm(
    JNIEnv* env,jclass cls,const char* name,MPI_Comm comm)
{   
    jobject obj;
    jfieldID fid = (*env)->GetStaticFieldID(env,cls,name,
        "Lmpi/Intracomm;");
    if(fid == NULL){
        return;
    }
    obj = (*env)->GetStaticObjectField(env,cls,fid);
    if(obj == NULL){
        return;
    }
    (*env)->SetLongField(env,obj,gJniCommHandler,comm);

    (*env)->DeleteLocalRef(env,obj);
}

JNIEXPORT int JNICALL
Java_mpi_Comm__1rank(
    JNIEnv *env,
    jclass cls,jlong comm)
{
    int result;
    int rank;
    
    result = MPI_Comm_rank((MPI_Comm)comm,&rank);

    if(result == MPI_ERR_COMM){
        mpiErrComm(env,"MPI_Comm_rank");
    }

    return rank;
}

JNIEXPORT int JNICALL
Java_mpi_Comm__1size(
    JNIEnv* env,
    jclass cls,
    jlong comm)
{
    int size;
    int result;

    result = MPI_Comm_size((MPI_Comm)comm,&size);

    if(result == MPI_ERR_COMM){
        mpiErrComm(env,"MPI_Comm_size");
    }
    else if(result == MPI_ERR_ARG){
        mpiErrArg(env,"MPI_Comm_size");
    }

    return size;
}
