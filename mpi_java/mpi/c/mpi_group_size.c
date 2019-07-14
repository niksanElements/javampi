#include "mpi_Group.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Group
 * Method:    _size
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL 
Java_mpi_Group__1size(
    JNIEnv *env, jclass class, jlong group)
{
    int result;
    int size;

    result = MPI_Group_size((MPI_Group)group,&size);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Group_size");
        return -1;
    }

    return size;
}