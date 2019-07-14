#ifndef JNI_MPI_REQUEST_H
#define JNI_MPI_REQUEST_H

#include "jni_mpi.h"

jclass gJniRequestClass;
jmethodID gJniRequestConstructor;
jfieldID gJniRequestHandler;

enum JNI_MPI_BUFFERS {
    JNI_ISEND_BUFFER,
    JNI_IRECV_BUFFER,

    JNI_IMAX_BUFFERS
};

// jni mpi request handler
typedef struct {
    MPI_Request request;
    tJniType* type[JNI_IMAX_BUFFERS];
    // region variables
    int offset[JNI_IMAX_BUFFERS];
    int count[JNI_IMAX_BUFFERS];
    // buffers
    jobject buffers[JNI_IMAX_BUFFERS];
    void* address[JNI_IMAX_BUFFERS];
    jboolean isPersistentRequest;
    jboolean isSendRequest;
} tJniRequest;

extern void jniMpiRequestFree(JNIEnv *env,tJniRequest* request);

#endif // JNI_MPI_REQUEST_H