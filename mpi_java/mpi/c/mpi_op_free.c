#include "mpi_op_Op.h"
#include "jni_mpi_op.h"

#include "malloc.h"

/*
 * Class:     mpi_op_Op
 * Method:    _free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL 
Java_mpi_op_Op__1free(
    JNIEnv *env, jclass clss, jlong op)
{
    tJniOp* _op = (tJniOp*)op;
    int result;

    result = MPI_Op_free(&_op->mpi_op);

    free(_op);

    // rase exception if there is one
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Sendrecv");
    }
}