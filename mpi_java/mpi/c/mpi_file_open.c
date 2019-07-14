#include "mpi_Intracomm.h"
#include "jni_mpi.h"

#include "malloc.h"

/*
 * Class:     mpi_Intracomm
 * Method:    _file_open
 * Signature: (JLjava/lang/String;IJ)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Intracomm__1file_1open(
    JNIEnv *env, jclass class, jlong comm, jstring fname, jint amode, jlong  info)
{
    int result;
    const char *name;
    MPI_File *file = malloc(sizeof(MPI_File));

    if(file == NULL){
        jniOutOfMemoryException(env,"malloc");
        return -1;
    }

    name = (*env)->GetStringUTFChars(env,fname,NULL);

    if(name != NULL){
        result = MPI_File_open((MPI_Comm)comm,name,amode,(MPI_Info)info,file);
        if(result != MPI_SUCCESS){
            mpiFileException(env,"MPI_File_open");
        }
    }

    (*env)->ReleaseStringUTFChars(env,fname,name);

    return (jlong)file;
}