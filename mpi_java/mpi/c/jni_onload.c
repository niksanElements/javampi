#include "jni_mpi.h"
#include "jni_mpi_types.h"
#include "jni_mpi_comm.h"
#include "jni_mpi_status.h"
#include "jni_mpi_request.h"
#include "jni_mpi_message.h"
#include "jni_mpi_win.h"
#include "jni_mpi_op.h"

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JNIEnv *env;
    jclass cls;

    gJava = vm;

    if ((*vm)->GetEnv(vm, (void **)&env, JNI_VERSION)) 
    {
        return JNI_ERR; /* JNI version not supported */
    }

    // cache Datatype class
    cls = (*env)->FindClass(env,"mpi/datatype/Datatype");
    if(cls == NULL){
        return JNI_ERR;
    }
    gJniDatatypeClass = (*env)->NewGlobalRef(env,cls);
    (*env)->DeleteLocalRef(env,cls);
    gJniDatatypeHandler = (*env)->GetFieldID(env,
        gJniDatatypeClass,"handler","J");
    if(gJniDatatypeHandler == NULL){
        return JNI_ERR;
    }
    gJniDatatypeSize = (*env)->GetFieldID(env,
        gJniDatatypeClass,"size","I");
    if(gJniDatatypeSize == NULL){
        return JNI_ERR;
    }

    // cache Comm class
    cls = (*env)->FindClass(env,"mpi/Comm");
    gJniCommClass = (*env)->NewGlobalRef(env,cls);
    (*env)->DeleteLocalRef(env,cls);
    if(gJniCommClass == NULL){
        return JNI_ERR;
    }
    gJniCommHandler = (*env)->GetFieldID(env,gJniCommClass,
        "handler","J");
    if(gJniCommHandler == NULL){
        return JNI_ERR;
    }

    // cache Status class
    cls = (*env)->FindClass(env,"mpi/Status");
    gJniStatusClass = (*env)->NewGlobalRef(env,cls);
    (*env)->DeleteLocalRef(env,cls);
    if(gJniStatusClass == NULL){
        return JNI_ERR;
    }
    gJniStatusGetStatus = (*env)->GetMethodID(env,gJniStatusClass,
        "getStatus","()[I");
    if(gJniStatusGetStatus == NULL){
        return JNI_ERR;
    }
    gJniStatusConstructor = (*env)->GetMethodID(env,gJniStatusClass,
        "<init>","(IIIII)V");
    if(gJniStatusConstructor == NULL){
        return JNI_ERR;
    }
    gJniStatusConstructorReq = (*env)->GetMethodID(env,gJniStatusClass,
        "<init>","(IIIIIZ)V");
    if(gJniStatusConstructorReq == NULL){
        return JNI_ERR;
    }
    gJniStatusSetStatus = (*env)->GetMethodID(env,gJniStatusClass,
        "setStatus","(IIIIIZ)V");
    if(gJniStatusSetStatus == NULL){
        return JNI_ERR;
    }

    // cache Request class
    cls = (*env)->FindClass(env,"mpi/Request");
    gJniRequestClass = (*env)->NewGlobalRef(env,cls);
    (*env)->DeleteLocalRef(env,cls);
    if(gJniRequestClass == NULL){
        return JNI_ERR;
    }
    gJniRequestConstructor = (*env)->GetMethodID(env,gJniRequestClass,
        "<init>","(J)V");
    if(gJniRequestConstructor == NULL){
        return JNI_ERR;
    }
    gJniRequestHandler = (*env)->GetFieldID(env,gJniRequestClass,
        "handler","J");
    if(gJniRequestHandler == NULL){
        return JNI_ERR;
    }

    // cache Message class
    cls = (*env)->FindClass(env,"mpi/Message");
    gJniMessageClass = (*env)->NewGlobalRef(env,cls);
    (*env)->DeleteLocalRef(env,cls);
    if(gJniMessageClass == NULL){
        return JNI_ERR;
    }
    gJniMessageConstructor = (*env)->GetMethodID(env,gJniMessageClass,
        "<init>","(JLmpi/Status;)V");
    if(gJniMessageConstructor == NULL){
        return JNI_ERR;
    }

    // cash Op class
    cls = (*env)->FindClass(env,"mpi/op/Op");
    gJniOpClass = (*env)->NewGlobalRef(env,cls);
    (*env)->DeleteLocalRef(env,cls);
    if(gJniOpClass == NULL){
        return JNI_ERR;
    }
    gJniOpHander = (*env)->GetFieldID(env,gJniOpClass,"handler","J");
    if(gJniOpHander == NULL){
        return JNI_ERR;
    }

    // operation handlers
    // Byte
    cls = (*env)->FindClass(env,"mpi/op/IByteOp");
    gJniByteIopCallback = (*env)->GetMethodID(env,cls,"operation","(BB)B");
    if(gJniByteIopCallback == NULL){
        return JNI_ERR;
    }
    // short
    cls = (*env)->FindClass(env,"mpi/op/IShortOp");
    gJniShortIopCallback = (*env)->GetMethodID(env,cls,"operation","(SS)S");
    if(gJniShortIopCallback == NULL){
        return JNI_ERR;
    }
    // int
    cls = (*env)->FindClass(env,"mpi/op/IIntOp");
    gJniIntIopCallback = (*env)->GetMethodID(env,cls,"operation","(II)I");
    if(gJniIntIopCallback == NULL){
        return JNI_ERR;
    }
    // long
    cls = (*env)->FindClass(env,"mpi/op/ILongOp");
    gJniLongIopCallback = (*env)->GetMethodID(env,cls,"operation","(JJ)J");
    if(gJniLongIopCallback == NULL){
        return JNI_ERR;
    }
    // float
    cls = (*env)->FindClass(env,"mpi/op/IFloatOp");
    gJniFloatIopCallback = (*env)->GetMethodID(env,cls,"operation","(FF)F");
    if(gJniFloatIopCallback == NULL){
        return JNI_ERR;
    }
    // double
    cls = (*env)->FindClass(env,"mpi/op/IDoubleOp");
    gJniDoubleIopCallback = (*env)->GetMethodID(env,cls,"operation","(DD)D");
    if(gJniDoubleIopCallback == NULL){
        return JNI_ERR;
    }
    // char
    cls = (*env)->FindClass(env,"mpi/op/ICharOp");
    gJniCharIopCallback = (*env)->GetMethodID(env,cls,"operation","(CC)C");
    if(gJniCharIopCallback == NULL){
        return JNI_ERR;
    }
    // boolean
    cls = (*env)->FindClass(env,"mpi/op/IBooleanOp");
    gJniBooleanIopCallback = (*env)->GetMethodID(env,cls,"operation","(ZZ)Z");
    if(gJniBooleanIopCallback == NULL){
        return JNI_ERR;
    }
    // object
    cls = (*env)->FindClass(env,"mpi/op/ObjectOp");
    gJniObjectOpCallback = (*env)->GetMethodID(env,cls,"_operation",
        "(Ljava/nio/ByteBuffer;Ljava/nio/ByteBuffer;)V");
    if(gJniObjectOpCallback == NULL){       
        return JNI_ERR;
    }
    // Win/Win_allocate_ret
    cls = (*env)->FindClass(env,"mpi/Win$Win_allocate_ret");
    gJniWinReturnClass = (*env)->NewGlobalRef(env,cls);
    if(gJniWinReturnClass == NULL){
        return JNI_ERR;
    }
    (*env)->DeleteLocalRef(env,cls);
    gJniWinReturnWin = (*env)->GetFieldID(env,gJniWinReturnClass,"win","J");
    if(gJniWinReturnWin == NULL){
        return JNI_ERR;
    }
    gJniWinReturnAddress = (*env)->GetFieldID(env,gJniWinReturnClass,"address","J");
    if(gJniWinReturnAddress == NULL){
        return JNI_ERR;
    }
    gJniWinReturnSize = (*env)->GetFieldID(env,gJniWinReturnClass,"size","I");
    if(gJniWinReturnSize == NULL){
        return JNI_ERR;
    }
    gJniWinReturnBuffer = (*env)->GetFieldID(env,gJniWinReturnClass,"buffer","Ljava/nio/ByteBuffer;");
    if(gJniWinReturnBuffer == NULL){
        return JNI_ERR;
    }

    return JNI_VERSION;
}