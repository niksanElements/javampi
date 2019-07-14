#ifndef JNI_JNI_MPI_EXCEPTION_H
#define JNI_JNI_MPI_EXCEPTION_H

#include "jni_mpi.h"
#include "jni_mpi_exception_classes.h"

extern void 
jni_mpi_throw_new(
    JNIEnv *env,
    const char* class);

#endif