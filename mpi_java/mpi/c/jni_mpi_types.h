#ifndef JNI_MPI_TYPES_H
#define JNI_MPI_TYPES_H

#include "jni_mpi.h"
#include "mpi.h"

enum jniTypes{ 
    JNI_BYTE =                      0,
    JNI_SHORT =                     1,
    JNI_INT =                       2,
    JNI_LONG =                      3,
    JNI_FLOAT =                     4,
    JNI_DOUBLE =                    5,
    JNI_CHAR =                      6,
    JNI_BOOLEAN =                   7,
    JNI_BYTE_BUFFER =               8,
    JNI_SHORT_BUFFER =              9,
    JNI_INT_BUFFER =                10,
    JNI_LONG_BUFFER =               11,
    JNI_FLOAT_BUFFER =              12,
    JNI_DOUBLE_BUFFER =             13,
    JNI_CHAR_BUFFER =               14,
    JNI_BOOLEAN_BUFFER =            15,
    JNI_STRING =                    16,
    JNI_MAX_DATATYPES
};

// Datatype cache variables
/**
 * Don't set this global variables to 
 * static. There is strage behavior from
 * JNI.
 */
jclass gJniDatatypeClass;
jfieldID gJniDatatypeHandler;
jfieldID gJniDatatypeSize;

// getter/setter for a buffer
typedef void (*fBufferControl)(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode);

typedef struct JNI_Datatype_struct {
    // true if the type is Buffer e.c ByteBuffer,IntBuffer..
    jboolean isBufferType;
    MPI_Datatype mpi_type;
    fBufferControl getBuffAddr;
    fBufferControl relBuffAddr;
    int size;
    // true blocking functions
    fBufferControl copyBuffer;
    fBufferControl setBuffer;
    jboolean isCustom;
    // operation call
    // TODO: remove op_call 
    void (*op_call)(JNIEnv*,jobject,const void*,void*);    
} tJniType;


// primary datatype handlers
extern tJniType gJniTypeTable[JNI_MAX_DATATYPES];
extern void 
init_jni_datatype(
    JNIEnv *env,jclass cls,const char* name,enum jniTypes type);

extern void getGenericRegion(
    JNIEnv *env,jobject obj,jint start,jint len,
    void** buff,int data,MPI_Datatype type);
extern void setGenericRegion(
    JNIEnv *env,jobject obj,jint start,jint len,
    void** buff,int data,MPI_Datatype type);
    

/**
 * @type
 * @env: It is allowed for this variable to be NULL, but then exception
 *  won't be raised.
 * 
 * @return: the size of the type in bytes.
 * 
 * @errors:
 *  mpiErrType
 *  mpiErrArg
 */
extern int mpi_sizeof(MPI_Datatype type,JNIEnv *env);
    /** region functions */
// datatypes getters
void getByteRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode);
void getShortRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode);
void getIntRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode);
void getLongRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode);
void getFloatRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode);
void getDoubleRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode);
void getCharRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode);
void getBooleanRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode);

// datatypes setters
void setByteRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode);
void setShortRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode);
void setIntRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode);
void setLongRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode);
void setFloatRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode);
void setDoubleRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode);
void setCharRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode);
void setBooleanRegion(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode);
    /** Direct Buffer function address function */
void getAddrDirectBuffer(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode);

// critical section functions
void getCriticalSection(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode);
void relCriticalSection(
    JNIEnv *env,jobject obj,jint start,jint len,void** buff,int type_size,int mode);

// operation callers
void byte_op_call(JNIEnv*,jobject,const jbyte*,jbyte*);
void short_op_call(JNIEnv*,jobject,const jshort*,jshort*);
void int_op_call(JNIEnv*,jobject,const jint*,jint*);
void long_op_call(JNIEnv*,jobject,const jlong*,jlong*);
void float_op_call(JNIEnv*,jobject,const jfloat*,jfloat*);
void double_op_call(JNIEnv*,jobject,const jdouble*,jdouble*);
void char_op_call(JNIEnv*,jobject,const jchar*,jchar*);
void boolean_op_call(JNIEnv*,jobject,const jboolean*,jboolean*);
void object_op_call(JNIEnv*,jobject,const jbyte*,jbyte*,int);
    
#endif // JNI_MPI_TYPES_H