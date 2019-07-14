#include "jni_mpi.h"
#include "mpi.h"
#include "malloc.h"
#include "mpi_MPI.h"

#include "jni_mpi_throw.h"

JNIEXPORT void JNICALL
Java_mpi_MPI__1init(JNIEnv *env, jclass obj, jobjectArray argv)
{
    int c_argc = 0;
    jstring *temp;
    char** c_argv;
    int i;
    int result = 0;

    if(argv != NULL){
        c_argc = (*env)->GetArrayLength(env,argv);
        c_argv = (char**)malloc(sizeof(char*)*c_argc);
        if(c_argv == NULL){
              jniOutOfMemoryException(env,"malloc");
              return;
        }
        temp = malloc(sizeof(jstring)*c_argc);
        if(temp == NULL){
            jniOutOfMemoryException(env,"malloc");
            if(c_argv != NULL){
                free(c_argv);
            }
            return;
        }
        else{
            // Get all parameters and string from java!
            for(i = 0;i < c_argc;i++){
                temp[i] = (jstring) (*env)->GetObjectArrayElement(env,argv,i);
                // we are converting this to char* because of a wonring
                // in reality we don't make changes over c_argv
                c_argv[i] = (char*) (*env)->GetStringUTFChars(env,temp[i],NULL);
                if(c_argv == NULL){
                    return;
                }
            }
            #ifdef JNI_MPI_DEBUG
            for(int i = 0;i < c_argc;i++){
                printf("%s\n",c_argv[i]);
            }
            #endif
            result = MPI_Init(&c_argc,&c_argv);

            // release utf strings
            for(i = 0;i < c_argc;i++){
                (*env)->ReleaseStringUTFChars(env,temp[i],c_argv[i]);
            }
            
            free(temp);
            free(c_argv);
        }
    }
    else{
        result = MPI_Init(NULL,NULL);
    }

    if(result == MPI_ERR_OTHER){
        mpiErrOther(env,"MPI_Init");
    }
}

/*
 * Class:     mpi_MPI
 * Method:    _init_thread
 * Signature: ([Ljava/lang/String;I)I
 */
JNIEXPORT jint JNICALL 
Java_mpi_MPI__1init_1thread(
    JNIEnv *env, jclass class, jobjectArray args, jint required)
{
    int provided;

    int c_argc = 0;
    jstring *temp;
    char** c_argv;
    int i;
    int result = 0;

    if(args != NULL){
        c_argc = (*env)->GetArrayLength(env,args);
        c_argv = (char**)malloc(sizeof(char*)*c_argc);
        if(c_argv == NULL){
              jniOutOfMemoryException(env,"malloc");
              return -1;
        }
        temp = malloc(sizeof(jstring)*c_argc);
        if(temp == NULL){
            jniOutOfMemoryException(env,"malloc");
            if(c_argv != NULL){
                free(c_argv);
            }
            return -1;
        }
        else{
            // Get all parameters and string from java!
            for(i = 0;i < c_argc;i++){
                temp[i] = (jstring) (*env)->GetObjectArrayElement(env,args,i);
                // we are converting this to char* because of a wonring
                // in reality we don't make changes over c_argv
                c_argv[i] = (char*) (*env)->GetStringUTFChars(env,temp[i],NULL);
                if(c_argv == NULL){
                    return -1;
                }
            }
            #ifdef JNI_MPI_DEBUG
            for(int i = 0;i < c_argc;i++){
                printf("%s\n",c_argv[i]);
            }
            #endif
            result = MPI_Init_thread(&c_argc,&c_argv,required,&provided);

            // release utf strings
            for(i = 0;i < c_argc;i++){
                (*env)->ReleaseStringUTFChars(env,temp[i],c_argv[i]);
            }
            
            free(temp);
            free(c_argv);
        }
    }
    else{
        result = MPI_Init_thread(NULL,NULL,required,&provided);
    }

    if(result == MPI_ERR_OTHER){
        mpiErrOther(env,"MPI_Init_thread");
    }

    return provided;
}

JNIEXPORT void JNICALL
Java_mpi_MPI__1finalize(JNIEnv *env, jclass obj)
{
    MPI_Finalize();
}