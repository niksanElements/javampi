#ifndef JNI_COMM_H
#define JNI_COMM_H

#include "jni_mpi.h"
#include "mpi.h"

// global viarables for cashing the Comm handler
jclass gJniCommClass;
jfieldID gJniCommHandler;

extern void init_comm(
    JNIEnv* env,jclass cls,const char* name,MPI_Comm comm);

#endif // JNI_COMM_H