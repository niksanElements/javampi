#include "jni_mpi.h"
#include "jni_mpi_exception.h"

#include <string.h>
#include <malloc.h>

// TODO: set malloc from mpi if possible 
// TODO: optimize function Java_org_mpich_MPI_MPI_1Init
JNIEXPORT jint JNICALL
Java_org_mpich_MPI_MPI_1Init(JNIEnv *env, jclass obj, jobjectArray argv)
{
    int c_argc = (*env)->GetArrayLength(env,argv);
    const int size = c_argc;
    jstring temp[size];
    char** c_argv;
    int i;
    int result = 0;

    c_argv = (char**)malloc(sizeof((char*)*c_argv));
    if(c_argv == NULL){
        goto fn_fail;
    }
    
    // Get all parameters and string from java!
    for(i = 0;i < c_argc;i++){
        temp[i] = (jstring) (*env)->GetObjectArrayElement(env,argv,i);
        // we are converting this to char* because of a wonring
        // in reality we don't make changes over c_argv
        c_argv[i] = (char*) (*env)->GetStringUTFChars(env,temp[i],NULL);
    }

    result = MPI_Init(&c_argc,&c_argv);


    // release utf strings
    for(i = 0;i < c_argc;i++){
        (*env)->ReleaseStringUTFChars(env,temp[i],c_argv[i]);
    }

    fn_exit:
        free(c_argv);
        if(result != MPI_SUCCESS){
            jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
        }
        return result;
    fn_fail:
        return -1;
}