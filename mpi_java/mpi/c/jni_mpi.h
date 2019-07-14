#ifndef JNI_MPI_H
#define JNI_MPI_H
// temporary configurations
#define HAVE_JNI_H 1
// #define JNI_REGION_COPY
#define JNI_CRITICAL_SECTION

#ifdef HAVE_JNI_H
#include "jni.h"
#else
    #error "There is no jni header file!"
#endif

#include "mpi.h"
#include "jni_mpi_throw.h"
#include "jni_mpi_types.h"
#include "jni_mpi_status.h"

// global handler for java virtual machine
JavaVM* gJava;

#define JNI_VERSION JNI_VERSION_1_8

#endif // JNI_MPI_H