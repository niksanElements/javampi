#ifndef JAVA_MPIA_C_UTILS_H
#define JAVA_MPIA_C_UTILS_H

#include <jni.h>
#include "mpi.h"
#include "opa_queue.h"
// java virtual machine
JavaVM *JAVA_VM;
// MPI_Status
jclass JNI_MPI_STATUS_CLASS;
jfieldID JNI_MPI_STATUS_COUNT_LO;
jfieldID JNI_MPI_STATUS_COUNT_HI;
jfieldID JNI_MPI_STATUS_MPI_ERROR;
jfieldID JNI_MPI_STATUS_MPI_SOURCE;
jfieldID JNI_MPI_STATUS_MPI_TAG;
// MPI_Request
jclass JNI_MPI_REQUEST_CLASS;
jfieldID JNI_MPI_REQUEST_HANDLER;
jfieldID JNI_MPI_REQUEST_TYPE;
// MPI_Message
jclass JNI_MPI_MESSAGE_CLASS;
jfieldID JNI_MPI_MESSAGE_HANDLER;
// mpi object serialization
jclass JNI_MPI_SERIALIZABLE_CLASS;
jmethodID JNI_MPI_SERIALIZABLE_SET;
jmethodID JNI_MPI_SERIALIZABLE_GET;
// Integer
jclass JNI_MPI_INTEGER_CLASS;
jfieldID JNI_MPI_INTEGER_VALUE;
// JNI MPI Window Buffer
jclass JNI_MPI_WIN_BUFFER_CLASS;
jmethodID JNI_MPI_WIN_BUFFER_GET;
jfieldID JNI_MPI_WIN_BUFFER_BASE_ADDRESS;
jfieldID JNI_MPI_WIN_BUFFER_IS_ALLOC;
jfieldID JNI_MPI_WIN_BUFFER_SIZE;
// buffer isend queue
typedef struct {
    OPA_Queue_element_hdr_t hdr;
    jobject glob_array_ref;
    void* buff;
    int datatype;
    MPI_Request req;
    // Those fields are needed for
    // collective comminication 
    jobject sendbuff;
    void* c_sendbuff;
    int sendtype;
    jobject counts_object;
    jint *counts_buff;
    jobject disp_object;
    jint* disp_buff;
    jobject counts2_object;
    jint* counts2_buff;
    jobject disp2_object;
    jint* disp2_buff;
} icom_element_t;
// icom_element_t JNI_MPI_ISEND_BUFFER;
// icom_element_t JNI_MPI_IRECV_BUFFER;
// TODO: multithread tests
OPA_Queue_info_t JNI_MPI_QHEAD_ISEND;
OPA_Queue_info_t JNI_MPI_QHEAD_IRECV;

// TODO: support for multiple threads
// OPA_Queue_info_t JNI_MPI_ISEND_QHEAD;

typedef enum {
    FROM_MPI_STATUS_TO_JAVA_MPI_STATUS,
    FROM_JAVA_MPI_STATUS_TO_MPI_STATUS
}jni_mpi_convert_MPI_Status_flag;

extern void jni_mpi_convert_MPI_Status
    (JNIEnv *env,jobject obj,MPI_Status* status,jni_mpi_convert_MPI_Status_flag flag);

extern void release_icom_element(
    JNIEnv* env,
    OPA_Queue_info_t* head,
    MPI_Request* req,
    int mode);

// return statement
#define JNI_MPI_RETURN(result)                                          \
    fn_exit:                                                            \
        if(result != MPI_SUCCESS){                                      \
            jni_mpi_throw_new(env,                                      \
                JNI_MPI_EXCEPTIONS[result]);                            \
        }                                                               \
        return result;                                                  \
    fn_fail:                                                            \
        return -1;                                                      \

#define jni_mpi_get_buffer(env,arr,buffer,jni_mpi_type,ret_type)\
{\
    switch (jni_mpi_type)\
    {\
        case org_mpich_MPI_BYTE:\
            if(arr != NULL){\
                buffer = (*env)->GetByteArrayElements(env,arr,NULL);\
                if(buffer == NULL){\
                    jni_mpi_throw_new(env,\
                        "org/mpich/exceptions/JNI_Null_exception");\
                }\
            }\
            ret_type = MPI_INT8_T;\
            break;\
        case org_mpich_MPI_SHORT:\
            if(arr != NULL){\
                buffer = (*env)->GetShortArrayElements(env,arr,NULL);\
                if(buffer == NULL){\
                    jni_mpi_throw_new(env,\
                        "org/mpich/exceptions/JNI_Null_exception");\
                }\
            }\
            ret_type = MPI_INT16_T;\
            break;\
        case org_mpich_MPI_INT:\
            if(arr != NULL){\
                buffer = (*env)->GetIntArrayElements(env,arr,NULL);\
                if(buffer == NULL){\
                    jni_mpi_throw_new(env,\
                        "org/mpich/exceptions/JNI_Null_exception");\
                }\
            }\
            ret_type = MPI_INT32_T;\
            break;\
        case org_mpich_MPI_LONG:\
            if(arr != NULL){\
                buffer = (*env)->GetLongArrayElements(env,arr,NULL);\
                if(buffer == NULL){\
                    jni_mpi_throw_new(env,\
                        "org/mpich/exceptions/JNI_Null_exception");\
                }\
            }\
            ret_type = MPI_INT64_T;\
            break;\
        case org_mpich_MPI_FLOAT:\
            if(arr != NULL){\
                buffer = (*env)->GetFloatArrayElements(env,arr,NULL);\
                if(buffer == NULL){\
                    jni_mpi_throw_new(env,\
                        "org/mpich/exceptions/JNI_Null_exception");\
                }\
            }\
            ret_type = MPI_FLOAT;\
            break;\
        case org_mpich_MPI_DOUBLE:\
            if(arr != NULL){\
                buffer = (*env)->GetDoubleArrayElements(env,arr,NULL);\
                if(buffer == NULL){\
                    jni_mpi_throw_new(env,\
                        "org/mpich/exceptions/JNI_Null_exception");\
                }\
            }\
            ret_type = MPI_DOUBLE;\
            break;\
        case org_mpich_MPI_BOOL_00415_00410N:\
            if(arr != NULL){\
                buffer = (*env)->GetBooleanArrayElements(env,arr,NULL);\
                if(buffer == NULL){\
                    jni_mpi_throw_new(env,\
                        "org/mpich/exceptions/JNI_Null_exception");\
                }\
            }\
            ret_type = MPI_UINT8_T;\
            break;\
        case org_mpich_MPI_CHAR:\
            if(arr != NULL){\
                buffer = (*env)->GetCharArrayElements(env,arr,NULL);\
                if(buffer == NULL){\
                    jni_mpi_throw_new(env,\
                        "org/mpich/exceptions/JNI_Null_exception");\
                }\
            }\
            ret_type = MPI_UINT16_T;\
            break;\
        case org_mpich_MPI_OBJECT:\
            ret_type = MPI_BYTE;\
            break;\
        default:\
            break;\
    }\
}

#define jni_mpi_rel_buffer(env,arr,buffer,jni_mpi_type,mode)\
{\
    switch (jni_mpi_type)\
    {\
        case org_mpich_MPI_BYTE:\
            (*env)->ReleaseByteArrayElements(env,arr,buffer,mode);\
            break;\
        case org_mpich_MPI_SHORT:\
            (*env)->ReleaseShortArrayElements(env,arr,buffer,mode);\
            break;\
        case org_mpich_MPI_INT:\
            (*env)->ReleaseIntArrayElements(env,arr,buffer,mode);\
            break;\
        case org_mpich_MPI_LONG:\
            (*env)->ReleaseLongArrayElements(env,arr,buffer,mode);\
            break;\
        case org_mpich_MPI_FLOAT:\
            (*env)->ReleaseFloatArrayElements(env,arr,buffer,mode);\
            break;\
        case org_mpich_MPI_DOUBLE:\
            (*env)->ReleaseDoubleArrayElements(env,arr,buffer,mode);\
            break;\
        case org_mpich_MPI_BOOL_00415_00410N:\
            (*env)->ReleaseBooleanArrayElements(env,arr,buffer,mode);\
            break;\
        case org_mpich_MPI_CHAR:\
            (*env)->ReleaseCharArrayElements(env,arr,buffer,mode);\
            break;\
        case org_mpich_MPI_OBJECT:\
            (*env)->ReleaseByteArrayElements(env,arr,buffer,mode);\
            break;\
        default:\
            break;\
    }\
}

#define jni_mpi_get_obj_addr(env,obj,buff,count,type,mpi_type,isset)\
{\
    jobject b = \
        (*env)->CallObjectMethod(env,obj,JNI_MPI_SERIALIZABLE_GET,isset);\
    if(b == NULL){\
        printf("MPI Serialization Errorr!\n");\
        goto fn_fail;\
    }\
    count = (*env)->GetDirectBufferCapacity(env,b);\
    jni_mpi_get_buffer(env,NULL,buff,type,mpi_type);\
    buff = (*env)->GetDirectBufferAddress(env,b);\
    (*env)->DeleteLocalRef(env,b);\
}

#define jni_mpi_gobj_addr(env,obj,gobj,buff,count,type,mpi_type,isset)\
{\
    jobject b = \
        (*env)->CallObjectMethod(env,obj,JNI_MPI_SERIALIZABLE_GET,isset);\
    gobj = (*env)->NewGlobalRef(env,obj);\
    if(b == NULL){\
        printf("MPI Serialization Errorr!\n");\
        goto fn_fail;\
    }\
    count = (*env)->GetDirectBufferCapacity(env,b);\
    jni_mpi_get_buffer(env,NULL,buff,type,mpi_type);\
    buff = (*env)->GetDirectBufferAddress(env,b);\
    (*env)->DeleteLocalRef(env,b);\
}

extern int jni_mpi_sizeof(int type);
extern void init_icom_element(icom_element_t*ele);

// jni help macros
#define JNI_GET_STRING(env,c_char,str_obj,isCopy)\
c_char = (*env)->GetStringUTFChars(env,str_obj,isCopy);\
if(c_char == NULL){\
    jni_mpi_throw_new(env,\
        "org/mpich/exceptions/JNI_Null_exception");\
    goto fn_fail;\
}
#define JNI_NEW_GLOBAL_REF(env,obj,result_object)\
    result_object = (*env)->NewGlobalRef(env,obj);\
    if(result_object ==  NULL){\
        jni_mpi_throw_new(env,\
            "org/mpich/exceptions/JNI_Null_exception");\
        goto fn_fail;\
    }

#endif // JAVA_MPIA_C_UTILS_H