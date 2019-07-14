#include "jni_mpi_exception.h"

void 
jni_mpi_throw_new(
    JNIEnv *env,
    const char* class)
{
    jclass cls;

    cls = (*env)->FindClass(env,class);
    (*env)->ThrowNew(env,cls,"MPI EXCEPTION");
}