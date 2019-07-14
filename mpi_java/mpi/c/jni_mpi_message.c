#include "jni_mpi_message.h"

jobject 
newJniMpiMessage(JNIEnv *env,MPI_Message* msg,MPI_Status* stat,jboolean flag)
{
    jobject status = (*env)->NewObject(env,gJniStatusClass,
        gJniStatusConstructorReq,stat->count_lo,
        stat->count_hi_and_cancelled,stat->MPI_SOURCE,
        stat->MPI_TAG,stat->MPI_ERROR,flag);
    
    return (*env)->NewObject(env,gJniMessageClass,gJniMessageConstructor,
        (jlong)*msg,status);
}