#include "jni_mpi_op.h"

tJniOp gJniOpTable[JNI_OPERATION_MAX] = 
{
    { 
        MPI_MAX
    },
    {
        MPI_MIN
    },
    {
        MPI_SUM
    },
    {
        MPI_PROD
    },
    {
        MPI_LAND
    },
    {
        MPI_BAND
    },
    {
        MPI_LOR
    },
    {
        MPI_BOR
    },
    {
        MPI_LXOR
    },
    {
        MPI_BXOR
    },
    {
        MPI_MINLOC
    },
    {
        MPI_MAXLOC
    },
    {
        MPI_REPLACE
    }
};

void 
init_jni_operation(JNIEnv *env,jclass cls,const char* name,enum JNI_OP_ENUM type)
{
    jobject obj;
    jlong address = 0;
    
    jfieldID fid = (*env)->GetStaticFieldID(env,cls,name,
        "Lmpi/op/Op;");
    if(fid == NULL){
        return;
    }
    obj = (*env)->GetStaticObjectField(env,cls,fid);
    if(obj == NULL){
        return;
    }
    address = (long)(&gJniOpTable[type]);
    (*env)->SetLongField(env,obj,gJniOpHander,address);

    (*env)->DeleteLocalRef(env,obj);
}

void jniOpFunc (const void* inbuff, void * inoutbuff,const int* len, 
    const MPI_Datatype* datatype, long long unsigned int op)
{
    tJniOp* _op = (tJniOp*)op;
    JNIEnv *env;

    // TODO: implementation for custom types

    // get java environment
    if ((*gJava)->GetEnv(gJava, (void **)&env, JNI_VERSION)) {
        return;
    }

    switch (*datatype)
    {
    case MPI_INT8_T:
    {
        jbyte *_in = (jbyte*)inbuff;
        jbyte *_inout = (jbyte*)inoutbuff;

        for(int i = 0;i < *len;i++){
            byte_op_call(env,_op->obj,&_in[i],&_inout[i]);
        }
        break;
    }
    case MPI_INT16_T:
    {
        jshort *_in = (jshort*)inbuff;
        jshort *_inout = (jshort*)inoutbuff;

        for(int i = 0;i < *len;i++){
            short_op_call(env,_op->obj,&_in[i],&_inout[i]);
        }
        break;
    }
    case MPI_INT32_T:
    {
        jint *_in = (jint*)inbuff;
        jint *_inout = (jint*)inoutbuff;

        for(int i = 0;i < *len;i++){
            int_op_call(env,_op->obj,&_in[i],&_inout[i]);
        }
        break;
    }
    case MPI_INT64_T:
    {
        jlong *_in = (jlong*)inbuff;
        jlong *_inout = (jlong*)inoutbuff;

        for(int i = 0;i < *len;i++){
            long_op_call(env,_op->obj,&_in[i],&_inout[i]);
        }
        break;
    }
    case MPI_FLOAT:
    {
        jfloat *_in = (jfloat*)inbuff;
        jfloat *_inout = (jfloat*)inoutbuff;

        for(int i = 0;i < *len;i++){
            float_op_call(env,_op->obj,&_in[i],&_inout[i]);
        }
        break;
    }
    case MPI_DOUBLE:
    {
        jdouble *_in = (jdouble*)inbuff;
        jdouble *_inout = (jdouble*)inoutbuff;

        for(int i = 0;i < *len;i++){
            double_op_call(env,_op->obj,&_in[i],&_inout[i]);
        }
        break;
    }
    case MPI_UINT16_T:
    {
        jchar *_in = (jchar*)inbuff;
        jchar *_inout = (jchar*)inoutbuff;

        for(int i = 0;i < *len;i++){
            char_op_call(env,_op->obj,&_in[i],&_inout[i]);
        }
        break;
    }
    case MPI_UINT8_T:
    {
        jboolean *_in = (jboolean*)inbuff;
        jboolean *_inout = (jboolean*)inoutbuff;

        for(int i = 0;i < *len;i++){
            boolean_op_call(env,_op->obj,&_in[i],&_inout[i]);
        }
        break;
    }
    
    default:
    {
        // object handler
        jboolean *_in = (jboolean*)inbuff;
        jboolean *_inout = (jboolean*)inoutbuff;
        int size = mpi_sizeof(*datatype,env);
        int index = 0;

        for(int i = 0;i < *len;i++){
            index = index+(i*size);
            object_op_call(env,_op->obj,&_in[i],&_inout[i],size);
        }
        break;
    }
    }
}