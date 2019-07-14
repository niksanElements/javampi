#ifndef JNI_MPI_STATUS_H
#define JNI_MPI_STATUS_H

#include "jni_mpi.h"

#define JNI_STATUS_count_lo 0   
#define JNI_STATUS_count_hi_and_cancelled 1 
#define JNI_STATUS_mpi_source 2
#define JNI_STATUS_mpi_tag 3
#define JNI_STATUS_mpi_error 4
#define JNI_STATUS_max_param 5


jclass gJniStatusClass;
jmethodID gJniStatusGetStatus;
jmethodID gJniStatusConstructor;
jmethodID gJniStatusConstructorReq;
jmethodID gJniStatusSetStatus;


extern void getStatus(JNIEnv *env,jobject obj,MPI_Status* stat);
extern void setStatus(JNIEnv *env,jobject obj,MPI_Status* stat,jboolean flag);


#endif // JNI_MPI_STATUS_H