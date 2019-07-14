#include "jni_mpi.h"
#include "mpi_MPI.h"
#include "jni_mpi_types.h"
#include "jni_mpi_comm.h"
#include "jni_mpi_op.h"


JNIEXPORT void JNICALL
Java_mpi_MPI_initNative(JNIEnv *env,jclass cls)
{
    // init all primitive datatype handlers
    init_jni_datatype(env,cls,"BYTE",JNI_BYTE);
    init_jni_datatype(env,cls,"SHORT",JNI_SHORT);
    init_jni_datatype(env,cls,"INT",JNI_INT);
    init_jni_datatype(env,cls,"LONG",JNI_LONG);
    init_jni_datatype(env,cls,"FLOAT",JNI_FLOAT);
    init_jni_datatype(env,cls,"DOUBLE",JNI_DOUBLE);
    init_jni_datatype(env,cls,"CHAR",JNI_CHAR);
    init_jni_datatype(env,cls,"BOOLEAN",JNI_BOOLEAN);
    init_jni_datatype(env,cls,"SHORT",JNI_SHORT);
    init_jni_datatype(env,cls,"BYTE_BUFFER",JNI_BYTE_BUFFER);
    init_jni_datatype(env,cls,"SHORT_BUFFER",JNI_SHORT_BUFFER);
    init_jni_datatype(env,cls,"INT_BUFFER",JNI_INT_BUFFER);
    init_jni_datatype(env,cls,"LONG_BUFFER",JNI_LONG_BUFFER);
    init_jni_datatype(env,cls,"FLOAT_BUFFER",JNI_FLOAT_BUFFER);
    init_jni_datatype(env,cls,"DOUBLE_BUFFER",JNI_DOUBLE_BUFFER);
    init_jni_datatype(env,cls,"CHAR_BUFFER",JNI_CHAR_BUFFER);
    init_jni_datatype(env,cls,"BOOLEAN_BUFFER",JNI_BOOLEAN_BUFFER);
    // initialize MPI_COMM_WORLD
    init_comm(env,cls,"COMM_WORLD",MPI_COMM_WORLD);
    // initialize MPI_OP
    init_jni_operation(env,cls,"MAX",JNI_OP_MAX);
    init_jni_operation(env,cls,"MIN",JNI_OP_MIN);
    init_jni_operation(env,cls,"SUM",JNI_OP_SUM);
    init_jni_operation(env,cls,"PROD",JNI_OP_PROD);
    init_jni_operation(env,cls,"LAND",JNI_OP_LAND);
    init_jni_operation(env,cls,"BAND",JNI_OP_BAND);
    init_jni_operation(env,cls,"LOR",JNI_OP_LOR);
    init_jni_operation(env,cls,"BOR",JNI_OP_BOR);
    init_jni_operation(env,cls,"LXOR",JNI_OP_LXOR);
    init_jni_operation(env,cls,"BXOR",JNI_OP_BXOR);
    init_jni_operation(env,cls,"MINLOC",JNI_OP_MINLOC);
    init_jni_operation(env,cls,"MAXLOC",JNI_OP_MAXLOC);
    init_jni_operation(env,cls,"REPLACE",JNI_OP_REPLACE); 
}