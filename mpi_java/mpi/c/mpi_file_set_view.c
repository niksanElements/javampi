#include "mpi_File.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_File
 * Method:    _set_view
 * Signature: (JJJJLjava/lang/String;J)V
 */
JNIEXPORT void JNICALL 
Java_mpi_File__1set_1view(
    JNIEnv *env, jclass class, 
    jlong file, jlong disp, jlong etype, jlong filetype, jstring datarep, jlong info)
{
    tJniType *_filetype = (tJniType*)filetype;
    tJniType *_etype = (tJniType*)etype;
    MPI_File *_file = (MPI_File*)file;
    const char *_datarep;
    int result;

    _datarep = (*env)->GetStringUTFChars(env,datarep,NULL);
    if(_datarep == NULL){
        return;
    }

    result =  MPI_File_set_view(*_file,disp,_etype->mpi_type,_filetype->mpi_type,
        _datarep,(MPI_Info)info);
    if(result != MPI_SUCCESS){
        // printf("result: %d\n",result);
        mpiFileException(env,"MPI_File_set_view");
    }

    (*env)->ReleaseStringUTFChars(env,datarep,_datarep);
}