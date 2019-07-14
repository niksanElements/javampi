#include "jni_mpi.h"
#include "jni_mpi_exception.h"

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Info_create
 * Signature: ()I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Info_1create(
    JNIEnv *env, jclass class)
{
    int result;
    int info;

    result = MPI_Info_create(&info);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return info;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Info_set
 * Signature: (ILjava/lang/String;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Info_1set(
    JNIEnv *env, 
    jclass class, 
    jint info, 
    jstring key, 
    jstring value)
{
    const char *_key;
    const char *_value;
    int result;

    _key = (*env)->GetStringUTFChars(env,key,NULL);
    _value =(*env)->GetStringUTFChars(env,value,NULL);

    result = MPI_Info_set(info,_key,_value);

    (*env)->ReleaseStringUTFChars(env,key,_key);
    (*env)->ReleaseStringUTFChars(env,value,_value);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Info_delete
 * Signature: (ILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Info_1delete(
    JNIEnv *env, 
    jclass class, 
    jint info, 
    jstring key)
{
    int result;
    const char *_key;
    _key = (*env)->GetStringUTFChars(env,key,NULL);

    result  = MPI_Info_delete(info,_key);

    (*env)->ReleaseStringUTFChars(env,key,_key);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Info_get
 * Signature: (ILjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL 
Java_org_mpich_MPI_MPI_1Info_1get(
    JNIEnv *env, 
    jclass class, 
    jint info, 
    jstring key)
{
    int result;
    const char *_key;
    char value[MPI_MAX_INFO_VAL];
    int flag;
    _key = (*env)->GetStringUTFChars(env,key,NULL);

    result = MPI_Info_get(info,_key,MPI_MAX_INFO_VAL,value,&flag);
    (*env)->ReleaseStringUTFChars(env,key,_key);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    if(flag == 1){
        return (*env)->NewStringUTF(env,value);
    }
    return NULL;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Info_get_valuelen
 * Signature: (ILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Info_1get_1valuelen(
    JNIEnv *env, 
    jclass class, 
    jint info, 
    jstring key)
{
    int result;
    const char *_key;
    int len;
    int flag;

    _key = (*env)->GetStringUTFChars(env,key,NULL);

    result = MPI_Info_get_valuelen(info,_key,&len,&flag);
    (*env)->ReleaseStringUTFChars(env,key,_key);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    if(flag == 1){
        return len;
    }
    return -1;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Info_get_nthkey
 * Signature: (II)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL 
Java_org_mpich_MPI_MPI_1Info_1get_1nthkey(
    JNIEnv *env, 
    jclass class,
    jint info, 
    jint n)
{
    int result;
    char key[MPI_MAX_INFO_KEY];

    result = MPI_Info_get_nthkey(info,n,key);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return (*env)->NewStringUTF(env,key);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Info_dup
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Info_1dup(
    JNIEnv *env, 
    jclass class, 
    jint info)
{
    int newinfo;
    int result;

    result = MPI_Info_dup(info,&newinfo);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return newinfo;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Info_free
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Info_1free(
    JNIEnv *env, 
    jclass class, 
    jint info)
{
    int result;
    result = MPI_Info_free(&info);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }
    return info;
}
