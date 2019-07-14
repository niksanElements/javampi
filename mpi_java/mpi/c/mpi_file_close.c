#include "mpi_File.h"
#include "jni_mpi.h"

#include "malloc.h"

/*
 * Class:     mpi_File
 * Method:    _close
 * Signature: (J)V
 */
JNIEXPORT void JNICALL 
Java_mpi_File__1close(
    JNIEnv *env, jclass class, jlong file)
{
    int result;
    MPI_File *_file = (MPI_File*)file;

    result = MPI_File_close(_file);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_File_close");
        return;
    }

    free(_file);
}