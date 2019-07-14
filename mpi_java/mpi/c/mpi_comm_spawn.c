#include "mpi_Intracomm.h"
#include "jni_mpi.h"

#include "malloc.h"

/*
 * Class:     mpi_Intracomm
 * Method:    _spawn
 * Signature: (Ljava/lang/String;[Ljava/lang/String;IJIJII[I)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Intracomm__1spawn(
    JNIEnv *env, jclass class, jstring command, jobjectArray args, jint maxproc, 
    jlong info, jint root, jlong comm, jint offset, jint len, jintArray error_codes)
{
    const char *_command;
    char **_args;
    jobject *args_temp;
    jint* _error_codes;
    int result;
    int count;
    long new_comm = 0;

    // extract the command
    _command = (*env)->GetStringUTFChars(env,command,NULL);
    if(args != NULL){
        // extract all arguments
        count = (*env)->GetArrayLength(env,args);
        _args = malloc(sizeof(char*)*count);
        if(_args == NULL){
            jniOutOfMemoryException(env,"malloc");
            return -1;
        }
        args_temp = malloc(sizeof(jobject*)*count);
        if(args == NULL){
            jniOutOfMemoryException(env,"malloc");
            return -1;
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
    }
    // get array of errcodes
#ifdef JNI_REGION_COPY
    // if the buffer is DirectBuffer
    // allocate _buff
    _error_codes = malloc(len*sizeof(jint));
    
    if(_error_codes == NULL){
        jniOutOfMemoryException(env,"malloc");
        return -1;;
    }
    // getIntRegion(env,remain,offset,size,(void**)&_remain,0);
#elif defined JNI_CRITICAL_SECTION
    getCriticalSection(env,error_codes,offset,len,(void**)&_error_codes,sizeof(jint),0);
#endif

    // the main part
    if(args == NULL){
        result = MPI_Comm_spawn(_command,MPI_ARGV_NULL,maxproc,(MPI_Info)info,root,(MPI_Comm)comm,
            (MPI_Comm*)&new_comm,_error_codes);
    }
    else{
        result = MPI_Comm_spawn(_command,_args,maxproc,(MPI_Info)info,root,(MPI_Comm)comm,
            (MPI_Comm*)&new_comm,_error_codes);
    }
    
    
    // release the commad string
    (*env)->ReleaseStringUTFChars(env,command,_command);
    // release the args
    for(int i = 0;i < count;i++){
        if(args_temp[i] != NULL){
            (*env)->ReleaseStringUTFChars(env,args_temp[i],_args[i]);
            (*env)->DeleteLocalRef(env,args_temp[i]);
        }
    }
#ifdef JNI_REGION_COPY
    setIntRegion(env,error_codes,offset,len,(void**)&_error_codes,JNI_COMMIT);
    free(_error_codes);
#elif defined JNI_CRITICAL_SECTION
    relCriticalSection(env,error_codes,offset,len,
        (void**)&_error_codes,sizeof(jint),JNI_COMMIT);
#endif
    return new_comm;
}