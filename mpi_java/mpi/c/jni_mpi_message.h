#ifndef JNI_MPI_MESSAGE_H
#define JNI_MPI_MESSAGE_H

#include "jni_mpi.h"
#include "jni_mpi_status.h"

jclass gJniMessageClass;
jmethodID gJniMessageConstructor;

extern jobject 
newJniMpiMessage(JNIEnv *env,MPI_Message* msg,MPI_Status* status,jboolean flag);


#endif // JNI_MPI_MESSAGE_H