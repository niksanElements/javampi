#include "mpi_Cart.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Cart
 * Method:    _shift
 * Signature: (JIIZ)I
 */
JNIEXPORT jint 
JNICALL Java_mpi_Cart__1shift(
    JNIEnv *env, jclass class, jlong comm, jint direction, jint disp, jboolean isSource)
{
    int result;
    int source,dest;

    result = MPI_Cart_shift((MPI_Comm)comm,direction,disp,&source,&dest);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Cart_shift");
        return -1;
    }

    if(isSource){
        return source;
    }

    return dest;
}