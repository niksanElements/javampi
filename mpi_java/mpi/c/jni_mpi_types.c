#include "jni_mpi_types.h"
#include "jni_mpi_throw.h"
#include "jni_mpi_op.h"

// jni mpi types
tJniType gJniTypeTable[JNI_MAX_DATATYPES] = 
{
    // byte
    {
        JNI_FALSE,          // it's not a DirectBuffer
        MPI_INT8_T, // datatype
#ifdef JNI_REGION_COPY
        getByteRegion,        // callback address pointer
        setByteRegion        // callback release address
#elif defined JNI_CRITICAL_SECTION
        getCriticalSection, // callback address pointer
        relCriticalSection // callback release address
#endif
        ,sizeof(jbyte),
        getByteRegion,        // copy buffer
        setByteRegion,        // set buffer
        JNI_FALSE
    },  
    // short
    {
        JNI_FALSE,          // it's not a DirectBuffer
        MPI_INT16_T, // datatype
#ifdef JNI_REGION_COPY
        getShortRegion,        // callback address pointer
        setShortRegion        // callback release address
#elif defined JNI_CRITICAL_SECTION
        getCriticalSection,
        relCriticalSection
#endif
        ,sizeof(jshort),
        getShortRegion,        // copy buffer
        setShortRegion,        // set buffer
        JNI_FALSE
    },
    // int
    {
        JNI_FALSE,          // it's not a DirectBuffer
        MPI_INT32_T, // datatype
#ifdef JNI_REGION_COPY        
        getIntRegion,        // callback address pointer
        setIntRegion        // callback release address
#elif defined JNI_CRITICAL_SECTION
        getCriticalSection,
        relCriticalSection
#endif
        ,sizeof(jint),
        getIntRegion,        // copy buffer
        setIntRegion,        // set buffer
        JNI_FALSE
    },
    // long
    {
        JNI_FALSE,          // it's not a DirectBuffer
        MPI_INT64_T, // datatype
#ifdef JNI_REGION_COPY        
        getLongRegion,        // callback address pointer
        setLongRegion        // callback release address
#elif defined JNI_CRITICAL_SECTION
        getCriticalSection,
        relCriticalSection
#endif
        ,sizeof(jlong),
        getLongRegion,        // copy buffer
        setLongRegion,        // set buffer
        JNI_FALSE
    },
    // float
    {
        JNI_FALSE,          // it's not a DirectBuffer
        MPI_FLOAT, // datatype
#ifdef JNI_REGION_COPY        
        getFloatRegion,        // callback address pointer
        setFloatRegion        // callback release address
#elif defined JNI_CRITICAL_SECTION
        getCriticalSection,
        relCriticalSection
#endif
        ,sizeof(jfloat),
        getFloatRegion,        // copy buffer
        setFloatRegion,        // set buffer
        JNI_FALSE
    },
    // double
    {
        JNI_FALSE,          // it's not a DirectBuffer
        MPI_DOUBLE, // datatype
#ifdef JNI_REGION_COPY        
        getDoubleRegion,        // callback address pointer
        setDoubleRegion        // callback release address
#elif defined JNI_CRITICAL_SECTION
        getCriticalSection,
        relCriticalSection
#endif
        ,sizeof(jdouble),
        getDoubleRegion,        // copy buffer
        setDoubleRegion,        // set buffer
        JNI_FALSE
    },
    // char
    {
        JNI_FALSE,          // it's not a DirectBuffer
        MPI_UINT16_T, // datatype
#ifdef JNI_REGION_COPY        
        getCharRegion,        // callback address pointer
        setCharRegion        // callback release address
#elif defined JNI_CRITICAL_SECTION
        getCriticalSection,
        relCriticalSection
#endif
        ,sizeof(jchar),
        getCharRegion,        // copy buffer
        setCharRegion,        // set buffer
        JNI_FALSE
    },
     // boolean
    {
        JNI_FALSE,          // it's not a DirectBuffer
        MPI_UINT8_T, // datatype
#ifdef JNI_REGION_COPY        
        getBooleanRegion,        // callback address pointer
        setBooleanRegion        // callback release address
#elif defined JNI_CRITICAL_SECTION
        getCriticalSection,
        relCriticalSection
#endif
        ,sizeof(jboolean),
        getBooleanRegion,        // copy buffer
        setBooleanRegion,        // set buffer
        JNI_FALSE
    }, 
    // ByteBuffer
    {
        JNI_TRUE,
        MPI_INT8_T, // datatype
        getAddrDirectBuffer,        // callback address pointer
        NULL,       // callback release address
        sizeof(jbyte),
        NULL,
        NULL,
        JNI_FALSE
    },
    // ShortBuffer
    {
        JNI_TRUE,   // is DirectBuffer
        MPI_INT16_T, // datatype
        getAddrDirectBuffer,        // callback address pointer
        NULL,        // callback release address
        sizeof(jshort),
        NULL,
        NULL,
        JNI_FALSE
    },
    // IntBuffer
    {
        JNI_TRUE,   // is DirectBuffer
        MPI_INT32_T, // datatype
        getAddrDirectBuffer,        // callback address pointer
        NULL,        // callback release address
        sizeof(jint),
        NULL,
        NULL,
        JNI_FALSE
    },
    // LongByte
    {
        JNI_TRUE,   // is DirectBuffer
        MPI_INT64_T, // datatype
        getAddrDirectBuffer,        // callback address pointer
        NULL,        // callback release address
        sizeof(jlong),
        NULL,
        NULL,
        JNI_FALSE
    },
    // FloatBuffer
    {
        JNI_TRUE,   // is DirectBuffer
        MPI_FLOAT, // datatype
        getAddrDirectBuffer,        // callback address pointer
        NULL,        // callback release address
        sizeof(jfloat),
        NULL,
        NULL,
        JNI_FALSE
    },
    // DoubleBuffer
    {
        JNI_TRUE,   // is DirectBuffer
        MPI_DOUBLE, // datatype
        getAddrDirectBuffer,        // callback address pointer
        NULL,        // callback release address
        sizeof(jdouble),
        NULL,
        NULL,
        JNI_FALSE
    },
    // CharBuffer
    {
        JNI_TRUE,   // is DirectBuffer
        MPI_UINT16_T, // datatype
        getAddrDirectBuffer,        // callback address pointer
        NULL,        // callback release address
        sizeof(jchar),
        NULL,
        NULL,
        JNI_FALSE
    },
    // BooleanBuffer
    {
        JNI_TRUE,   // is DirectBuffer
        MPI_UINT8_T, // datatype
        getAddrDirectBuffer,        // callback address pointer
        NULL,        // callback release address
        sizeof(jboolean),
        NULL,
        NULL
    },
    // TODO: String object
    {
        JNI_FALSE, // is it DirectBuffer
        MPI_UINT16_T, // datatype
        // get/release functions
        NULL,
        NULL,
        sizeof(jchar),
        // copy/set functions
        NULL,
        NULL
    }
};

void 
init_jni_datatype(
    JNIEnv *env,jclass cls,const char* name,enum jniTypes type)
{
    jobject obj;
    jlong address = 0;
    
    jfieldID fid = (*env)->GetStaticFieldID(env,cls,name,
        "Lmpi/datatype/Datatype;");
    if(fid == NULL){
        return;
    }
    obj = (*env)->GetStaticObjectField(env,cls,fid);
    if(obj == NULL){
        return;
    }
    address = (long)(&gJniTypeTable[type]);
    (*env)->SetLongField(env,obj,gJniDatatypeHandler,address);
    (*env)->SetIntField(env,obj,
        gJniDatatypeSize,gJniTypeTable[type].size);

    (*env)->DeleteLocalRef(env,obj);
}

int mpi_sizeof(MPI_Datatype type,JNIEnv* env)
{
    int result;
    int size;

    result = MPI_Type_size(type,&size);
    if(result == MPI_ERR_ARG){
        if(env != NULL){
            mpiErrArg(env,"MPI_Type_size");
        }
        return -1;
    }
    else if(result == MPI_ERR_TYPE){
        if(env != NULL){
            mpiErrType(env,"MPI_Type_size");
        }
        return -1;
    }

    return size;
}
/**
 * Getters/Setters
 */
// bytes
void getByteRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode)
{
    (*env)->GetByteArrayRegion(env,obj,start,len,*buff);
}
void setByteRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode)
{
    (*env)->SetByteArrayRegion(env,obj,start,len,*buff);
}
// short
void getShortRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode)
{
    (*env)->GetShortArrayRegion(env,obj,start,len,*buff);
}
void setShortRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode)
{
    (*env)->SetShortArrayRegion(env,obj,start,len,*buff);
}
// Int
void getIntRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode)
{
    (*env)->GetIntArrayRegion(env,obj,start,len,*buff);
}
void setIntRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode)
{
    (*env)->SetIntArrayRegion(env,obj,start,len,*buff);
}
// Long
void getLongRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode)
{
    (*env)->GetLongArrayRegion(env,obj,start,len,*buff);
}
void setLongRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode)
{
    (*env)->SetLongArrayRegion(env,obj,start,len,*buff);
}
// Float
void getFloatRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode)
{
    (*env)->GetFloatArrayRegion(env,obj,start,len,*buff);
}
void setFloatRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode)
{
    (*env)->SetFloatArrayRegion(env,obj,start,len,*buff);
}
// Double
void getDoubleRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode)
{
    (*env)->GetDoubleArrayRegion(env,obj,start,len,*buff);
}
void setDoubleRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode)
{
    (*env)->SetDoubleArrayRegion(env,obj,start,len,*buff);
}
// Char
void getCharRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode)
{
    (*env)->GetCharArrayRegion(env,obj,start,len,*buff);
}
void setCharRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode)
{
    (*env)->SetCharArrayRegion(env,obj,start,len,*buff);
}
// Boolean
void getBooleanRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode)
{
    (*env)->GetBooleanArrayRegion(env,obj,start,len,*buff);
}
void setBooleanRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode)
{
    (*env)->SetBooleanArrayRegion(env,obj,start,len,*buff);
}

// direct address buffer region
void getAddrDirectBuffer(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode)
{
    int capacity;

    capacity = (*env)->GetDirectBufferCapacity(env,obj);
    *buff = (*env)->GetDirectBufferAddress(env,obj);
    if(*buff == NULL){
        jniUndefinedMemException(env,"JNI GetDirectBufferAddress");
        return;
    }

    if(((len+start)*type_size) > capacity){
        jniIndexOutOfBoundsException(env,"Error Offset/Capacity!");
        buff = NULL;
        return;
    }
    *buff = ((jbyte*)*buff)+(type_size*start);
}

// critical sections
// bytes
void getCriticalSection(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode)
{
    int capacity;

    capacity = (*env)->GetArrayLength(env,obj);
    *buff = (*env)->GetPrimitiveArrayCritical(env,obj,NULL);
    if(*buff == NULL){
        jniOutOfMemoryException(env,"JNI Exception");
    }

    if((len+start) > capacity){
        (*env)->ReleasePrimitiveArrayCritical(env,obj,*buff,JNI_ABORT);
        jniIndexOutOfBoundsException(env,"Error Offset/Capacity!");
        buff = NULL;
        return;
    }
    *buff = ((jbyte*)*buff)+(type_size*start);

}
void relCriticalSection(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode)
{
    *buff = ((jbyte*)*buff)-(type_size*start);
    (*env)->ReleasePrimitiveArrayCritical(env,obj,*buff,mode);
}

// operation callers
void byte_op_call(JNIEnv*env,jobject obj,const jbyte* in,jbyte* inout)
{
    *inout = (*env)->CallByteMethod(env,obj,gJniByteIopCallback,*in,*inout);
}
void short_op_call(JNIEnv*env,jobject obj,const jshort* in,jshort* inout)
{
    *inout = (*env)->CallShortMethod(env,obj,gJniShortIopCallback,*in,*inout);
}
void int_op_call(JNIEnv* env,jobject obj,const jint* in,jint* inout)
{
    *inout = (*env)->CallIntMethod(env,obj,gJniIntIopCallback,*in,*inout);
}
void long_op_call(JNIEnv*env,jobject obj,const jlong* in,jlong* inout)
{
    *inout = (*env)->CallLongMethod(env,obj,gJniLongIopCallback,*in,*inout);
}
void float_op_call(JNIEnv*env,jobject obj,const jfloat* in,jfloat* inout)
{
    *inout = (*env)->CallFloatMethod(env,obj,gJniFloatIopCallback,*in,*inout);
}
void double_op_call(JNIEnv*env,jobject obj,const jdouble* in,jdouble* inout)
{
    *inout = (*env)->CallDoubleMethod(env,obj,gJniDoubleIopCallback,*in,*inout);
}
void char_op_call(JNIEnv*env,jobject obj,const jchar* in,jchar* inout)
{
    *inout = (*env)->CallCharMethod(env,obj,gJniCharIopCallback,*in,*inout);
}
void boolean_op_call(JNIEnv*env,jobject obj,const jboolean* in,jboolean* inout)
{
    *inout = (*env)->CallBooleanMethod(env,obj,gJniBooleanIopCallback,*in,*inout);
}
void object_op_call(JNIEnv*env,jobject obj,const jbyte* in,jbyte* inout,int size)
{
    jobject in_buff = (*env)->NewDirectByteBuffer(env,(void*)in,size);
    jobject inout_buff = (*env)->NewDirectByteBuffer(env,inout,size);
    // call the method
    (*env)->CallObjectMethod(env,obj,gJniObjectOpCallback,
        in_buff,inout_buff);

    (*env)->DeleteLocalRef(env,in_buff);
    (*env)->DeleteLocalRef(env,inout_buff);
}