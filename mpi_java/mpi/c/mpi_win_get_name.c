#include "mpi_Win.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Win
 * Method:    _get_name
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL 
Java_mpi_Win__1get_1name(
    JNIEnv *env, jclass class, jlong win)
{
    char name[MPI_MAX_OBJECT_NAME];
    int result;
    int resultlen;

    result = MPI_Win_get_name((MPI_Win)win,name,&resultlen);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Win_get_name");
        return NULL;
    }


    return (*env)->NewStringUTF(env,name);
}