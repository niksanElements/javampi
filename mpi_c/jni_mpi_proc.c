#include "jni_mpi.h"
#include "jni_mpi_exception.h"

#include <malloc.h>

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_spawn
 * Signature: (Ljava/lang/String;[Ljava/lang/String;IIII[I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Comm_1spawn(
    JNIEnv *env, 
    jclass class, 
    jstring command, 
    jobjectArray args, 
    jint maxprcs, 
    jint info, 
    jint root, 
    jint comm, 
    jintArray array_of_errocodes)
{
    const char *_command;
    char **_args;
    jobject *args_temp;
    jint* _array_of_errcodes;
    int result;
    int count;
    int intercomm;

    // extract the command
    _command = (*env)->GetStringUTFChars(env,command,NULL);
    // extract all arguments
    count = (*env)->GetArrayLength(env,args);
    _args = malloc(sizeof(char*)*count);
    if(_args == NULL){
        jni_mpi_throw_new(env,"org/mpich/exceptions/JNI_Exception");
    }
    args_temp = malloc(sizeof(jobject*)*count);
    if(args == NULL){
        jni_mpi_throw_new(env,"org/mpich/exceptions/JNI_Exception");
    }
    for(int i = 0;i < count;i++){
        args_temp[i] = (*env)->GetObjectArrayElement(env,args,i);
        if(args_temp[i] != NULL){
            _args[i] = (char*)(*env)->GetStringUTFChars(env,
                args_temp[i],NULL);
        }
        else{
            _args[i] = NULL;
        }
    }
    // get array of errcodes
    _array_of_errcodes = (*env)->GetIntArrayElements(env,
        array_of_errocodes,NULL);
    
    result = MPI_Comm_spawn(_command,_args,maxprcs,info,root,
        comm,&intercomm,_array_of_errcodes);
    
    // release the commad string
    (*env)->ReleaseStringUTFChars(env,command,_command);
    // release the args
    for(int i = 0;i < count;i++){
        if(args_temp[i] != NULL){
            (*env)->ReleaseStringUTFChars(env,args_temp[i],_args[i]);
            (*env)->DeleteLocalRef(env,args_temp[i]);
        }
    }
    (*env)->ReleaseIntArrayElements(env,array_of_errocodes,
        _array_of_errcodes,JNI_COMMIT);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    fn_exit:
        free(_args);
        free(args_temp);
        return intercomm;
    fn_fail:
        if(_args != NULL)
            free(_args);
        if(args_temp != NULL)
            free(args_temp);
        return -1;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_get_parent
 * Signature: ()I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Comm_1get_1parent(
    JNIEnv *env, 
    jclass class)
{
    int result;
    int perent;

    result = MPI_Comm_get_parent(&perent);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return perent;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_spawn_multiple
 * Signature: ([Ljava/lang/String;[[Ljava/lang/String;[I[III[I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Comm_1spawn_1multiple(
    JNIEnv *env, 
    jclass class, 
    jobjectArray commands, 
    jobjectArray args, 
    jintArray maxproces, 
    jintArray infos, 
    jint root, 
    jint comm, 
    jintArray array_of_errorcodes)
{
    // TODO: MPI_Comm_spawn_multiple
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_disconnect
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Comm_1disconnect(
    JNIEnv *env, 
    jclass class, 
    jint comm)
{
    int result;
    
    result = MPI_Comm_disconnect(&comm);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return comm;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_join
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Comm_1join(
    JNIEnv *env, 
    jclass class, 
    jint fd)
{
    int result;
    int intercomm;

    result = MPI_Comm_join(fd,&intercomm);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return intercomm;
}
