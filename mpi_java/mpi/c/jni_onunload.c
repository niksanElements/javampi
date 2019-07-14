#include "jni_mpi.h"
#include "jni_mpi_types.h"
#include "jni_mpi_comm.h"
#include "jni_mpi_status.h"
#include "jni_mpi_op.h"

JNIEXPORT void JNICALL
JNI_OnUnload(JavaVM *vm, void *reserved)
{
    JNIEnv *env;

    if ((*vm)->GetEnv(vm, (void **)&env, JNI_VERSION)) 
    {
        return; 
    }

    // make sure that all cached global variables are deleted
    (*env)->DeleteGlobalRef(env,gJniCommClass);
    (*env)->DeleteGlobalRef(env,gJniDatatypeClass);
    (*env)->DeleteGlobalRef(env,gJniStatusClass);
    (*env)->DeleteGlobalRef(env,gJniOpClass);
}