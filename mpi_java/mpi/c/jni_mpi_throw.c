#include "jni_mpi_throw.h"

void mpiErr(JNIEnv *env,int err_code,const char* func)
{
    const char* class_name = gMpiExceptionTable[err_code];
    if(class_name != NULL)
        jni_throw(env,class_name,func);
}

void 
jni_throw(
    JNIEnv *env,const char* cls_name,const char* msg)
{
    jclass cls = (*env)->FindClass(env,cls_name);
    if(cls == NULL){
        return;
    }

    (*env)->ThrowNew(env,cls,msg);
}

void jniOutOfMemoryException(JNIEnv *env,const char* msg)
{
    jni_throw(env,"java/lang/OutOfMemoryError",msg);
}

void mpiErrOther(JNIEnv *env,const char* func)
{
    jni_throw(env,"mpi/exception/OtherException",func);
}

void mpiErrComm(JNIEnv *env,const char* func)
{
    jni_throw(env,"mpi/exception/CommException",func);
}

void mpiErrArg(JNIEnv *env,const char* func)
{
    jni_throw(env,"mpi/exception/ArgException",func);
}

void mpiErrType(JNIEnv *env,const char* func)
{
    jni_throw(env,"mpi/exception/TypeException",func);
}

void jniUndefinedMemException(JNIEnv *env,const char* func)
{
    jni_throw(env,"mpi/exception/UndefinedMemException",func);
}

void jniIndexOutOfBoundsException(JNIEnv *env,const char* msg)
{
    jni_throw(env,"java/lang/IndexOutOfBoundsException",msg);
}

void mpiPermissionsException(JNIEnv *env,const char* msg)
{
    jni_throw(env,"mpi/exception/PermissionsException",msg);
}

void mpiFileException(JNIEnv *env,const char* msg)
{
    jni_throw(env,"mpi/exception/FileException",msg);
}