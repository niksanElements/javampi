#include "mpi_Intracomm.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Intracomm
 * Method:    _win_create
 * Signature: (Ljava/nio/ByteBuffer;IJJ)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Intracomm__1win_1create(
    JNIEnv *env, jclass class, jobject base, jint disp_unit, jlong info, jlong comm)
{
    long win = 0;
    void *_base = (*env)->GetDirectBufferAddress(env,base);
    int size = (*env)->GetDirectBufferCapacity(env,base);
    int result;

    result = MPI_Win_create(_base,size,disp_unit,(MPI_Info)info,(MPI_Comm)comm,(MPI_Win*)&win);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Win_create");
    }

    return win;
}