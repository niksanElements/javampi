#include "mpi_op_Op.h"
#include "jni_mpi.h"
#include "jni_mpi_op.h"
#include "mpii_javainterface.h"

#include "malloc.h"

/*
 * Class:     mpi_op_Op
 * Method:    _create
 * Signature: (Ljava/lang/Object;ZJ)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_op_Op__1create(
    JNIEnv *env, jclass class, jobject obj, jboolean isCommute,jlong type)
{
    tJniOp* op;
    long long unsigned int op_addres = 0;

    // allocate a operation handler
    op = malloc(sizeof(tJniOp));
    if(op == NULL){
        jniOutOfMemoryException(env,"malloc");
        return -1;
    }
    // crete object callback
    op->obj = (*env)->NewGlobalRef(env,obj);
    if(op->obj == NULL){
        return -1;
    }
    op_addres = (long long unsigned int)op;

    MPII_Op_create_java(jniOpFunc,isCommute,&op->mpi_op,op_addres);

    return (jlong)op;
}