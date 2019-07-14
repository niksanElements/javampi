#ifndef JNI_MPI_OP_H
#define JNI_MPI_OP_H

#include "jni_mpi.h"

jclass gJniOpClass;
jfieldID gJniOpHander;
jmethodID gJniByteIopCallback;
jmethodID gJniShortIopCallback;
jmethodID gJniIntIopCallback;
jmethodID gJniLongIopCallback;
jmethodID gJniFloatIopCallback;
jmethodID gJniDoubleIopCallback;
jmethodID gJniCharIopCallback;
jmethodID gJniBooleanIopCallback;
jmethodID gJniObjectOpCallback;

enum JNI_OP_ENUM {
    JNI_OP_MAX,
    JNI_OP_MIN,
    JNI_OP_SUM,
    JNI_OP_PROD,
    JNI_OP_LAND,
    JNI_OP_BAND,
    JNI_OP_LOR,
    JNI_OP_BOR,
    JNI_OP_LXOR,
    JNI_OP_BXOR,
    JNI_OP_MINLOC,
    JNI_OP_MAXLOC,
    JNI_OP_REPLACE,
    JNI_OPERATION_MAX
};

typedef struct {
    MPI_Op mpi_op; // mpi operation
    jobject obj;
}tJniOp;

// base MPI operations
extern tJniOp gJniOpTable[JNI_OPERATION_MAX];

// init mpi operation
extern void 
init_jni_operation(
    JNIEnv *env,jclass cls,const char* name,enum JNI_OP_ENUM type);

void jniOpFunc (const void*, void *,const int*, const MPI_Datatype*,long long unsigned int);

#endif // JNI_MPI_OP_H