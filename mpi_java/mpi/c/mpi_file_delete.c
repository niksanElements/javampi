#include "mpi_MPI.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_MPI
 * Method:    _file_delete
 * Signature: (Ljava/lang/String;J)V
 */
JNIEXPORT void JNICALL 
Java_mpi_MPI__1file_1delete(
    JNIEnv *env, jclass class, jstring name, jlong info)
{
    int result;
    const char *_name;

    _name = (*env)->GetStringUTFChars(env,name,NULL);
    if(name != NULL){
        result = MPI_File_delete(_name,(MPI_Info)info);
        if(result != MPI_SUCCESS){
            mpiErr(env,result,"MPI_File_delete");
        }
    }

    (*env)->ReleaseStringUTFChars(env,name,_name);
}