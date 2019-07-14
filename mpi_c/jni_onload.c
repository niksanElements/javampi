#include "jni_mpi.h"
#include "file.h"

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JNIEnv *env;
    jclass cls;

    JAVA_VM = vm;

    if ((*vm)->GetEnv(vm, (void **)&env, JNI_VERSION_1_8)) 
    {
        return JNI_ERR; /* JNI version not supported */
    }
    // MPI_Status
    cls = (*env)->FindClass(env, "org/mpich/MPI_Status");
    if (cls == NULL) {
        return JNI_ERR;
    }
    /* Use weak global ref to allow C class to be unloaded */
    JNI_MPI_STATUS_CLASS = (*env)->NewGlobalRef(env, cls);
    if (JNI_MPI_STATUS_CLASS == NULL) {
        return JNI_ERR;
    }  
    (*env)->DeleteLocalRef(env,cls);
    JNI_MPI_STATUS_COUNT_LO = (*env)->
        GetFieldID(env,JNI_MPI_STATUS_CLASS,"count_lo","I");
    if(JNI_MPI_STATUS_COUNT_LO == NULL){
        return JNI_ERR;
    }

    JNI_MPI_STATUS_COUNT_HI = (*env)->
        GetFieldID(env,JNI_MPI_STATUS_CLASS,"count_hi_and_cancelled","I");
    if(JNI_MPI_STATUS_COUNT_HI == NULL){
        return JNI_ERR;
    }

    JNI_MPI_STATUS_MPI_ERROR = (*env)->
        GetFieldID(env,JNI_MPI_STATUS_CLASS,"MPI_ERROR","I");
    if(JNI_MPI_STATUS_MPI_ERROR == NULL){
        return JNI_ERR;
    }

    JNI_MPI_STATUS_MPI_SOURCE = (*env)->
        GetFieldID(env,JNI_MPI_STATUS_CLASS,"MPI_SOURCE","I");
    if(JNI_MPI_STATUS_MPI_SOURCE == NULL){
        return JNI_ERR;
    }

    JNI_MPI_STATUS_MPI_TAG = (*env)->
        GetFieldID(env,JNI_MPI_STATUS_CLASS,"MPI_TAG","I");
    if(JNI_MPI_STATUS_MPI_TAG == NULL){
        return JNI_ERR;
    }
    // MPI_Request
    cls = (*env)->FindClass(env,"org/mpich/MPI_Request");
    if(cls == NULL){
        return JNI_ERR;
    }
    JNI_MPI_REQUEST_CLASS = (*env)->NewGlobalRef(env,cls);
    if(JNI_MPI_REQUEST_CLASS == NULL){
        return JNI_ERR;
    }
    (*env)->DeleteLocalRef(env,cls);
    JNI_MPI_REQUEST_HANDLER = (*env)->
        GetFieldID(env,JNI_MPI_REQUEST_CLASS,"handler","I");
    if(JNI_MPI_REQUEST_HANDLER == NULL){
        return JNI_ERR;
    }
    JNI_MPI_REQUEST_TYPE = (*env)->
        GetFieldID(env,JNI_MPI_REQUEST_CLASS,"type","I");
    if(JNI_MPI_REQUEST_TYPE == NULL){
        return JNI_ERR;
    }

    cls =(*env)->FindClass(env,"org/mpich/MPI_Message");
    if(cls == NULL){
        return JNI_ERR;
    }
    JNI_MPI_MESSAGE_CLASS = (*env)->NewGlobalRef(env,cls);
    if(JNI_MPI_MESSAGE_CLASS == NULL){
        return JNI_ERR;
    }
    (*env)->DeleteLocalRef(env,cls);
    JNI_MPI_MESSAGE_HANDLER = (*env)->
        GetFieldID(env,JNI_MPI_MESSAGE_CLASS,"handler","I");
    if(JNI_MPI_MESSAGE_HANDLER == NULL){
        return JNI_ERR;
    }

    cls = (*env)->FindClass(env,"org/mpich/MPI_Serializable");
    if(cls == NULL){
        return JNI_ERR;
    }
    JNI_MPI_SERIALIZABLE_CLASS = (*env)->NewGlobalRef(env,cls);
    if(JNI_MPI_SERIALIZABLE_CLASS == NULL){
        return JNI_ERR;
    }
    (*env)->DeleteLocalRef(env,cls);
    JNI_MPI_SERIALIZABLE_GET = (*env)->GetMethodID(env,
        JNI_MPI_SERIALIZABLE_CLASS,"mpi_get_buff","(Z)Ljava/nio/ByteBuffer;");
    if(JNI_MPI_SERIALIZABLE_GET == NULL){
        return JNI_ERR;
    }
    JNI_MPI_SERIALIZABLE_SET = (*env)->GetMethodID(env,
        JNI_MPI_SERIALIZABLE_CLASS,"mpi_create","()V");
    if(JNI_MPI_SERIALIZABLE_SET == NULL){
        return JNI_ERR;
    }
    cls = (*env)->FindClass(env,"org/mpich/MPI_Integer_ref");
    if(cls == NULL){
        return JNI_ERR;
    }
    JNI_MPI_INTEGER_CLASS = (*env)->NewGlobalRef(env,cls);
    if(JNI_MPI_INTEGER_CLASS == NULL){
        return JNI_ERR;
    }
    (*env)->DeleteLocalRef(env,cls);
    JNI_MPI_INTEGER_VALUE = (*env)->GetFieldID(env,JNI_MPI_INTEGER_CLASS,
        "value","I");
    if(JNI_MPI_INTEGER_VALUE == NULL){
        return JNI_ERR;
    }

    cls = (*env)->FindClass(env,"org/mpich/MPI_Win_buffer");
    if(cls == NULL){
        return JNI_ERR;
    }
    JNI_MPI_WIN_BUFFER_CLASS = (*env)->NewGlobalRef(env,cls);
    if(JNI_MPI_WIN_BUFFER_CLASS == NULL){
        return JNI_ERR;
    }
    (*env)->DeleteGlobalRef(env,cls);
    JNI_MPI_WIN_BUFFER_GET = (*env)->GetMethodID(
        env,JNI_MPI_WIN_BUFFER_CLASS,
        "getByteBuffer","()Ljava/nio/ByteBuffer;");
    if(JNI_MPI_WIN_BUFFER_GET == NULL){
        return JNI_ERR;
    }
    JNI_MPI_WIN_BUFFER_BASE_ADDRESS = (*env)->GetFieldID(
        env,JNI_MPI_WIN_BUFFER_CLASS,"base_address","J");
    if(JNI_MPI_WIN_BUFFER_BASE_ADDRESS == NULL){
        return JNI_ERR;
    }
    JNI_MPI_WIN_BUFFER_IS_ALLOC = (*env)->GetFieldID(
        env,JNI_MPI_WIN_BUFFER_CLASS,"MPI_Is_allocation","Z");
    if(JNI_MPI_WIN_BUFFER_IS_ALLOC == NULL){
        return JNI_ERR;
    }
    JNI_MPI_WIN_BUFFER_SIZE = (*env)->GetFieldID(
        env,JNI_MPI_WIN_BUFFER_CLASS,"size","I");
    if(JNI_MPI_WIN_BUFFER_SIZE == NULL){
        return JNI_ERR;
    }

    // isend linked queue
    OPA_Queue_init(&JNI_MPI_QHEAD_ISEND);
    // irecv linked queue
    OPA_Queue_init(&JNI_MPI_QHEAD_IRECV);
    
    return JNI_VERSION_1_8;
}