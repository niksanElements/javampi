#include "jni_mpi.h"
#include "jni_mpi_exception.h"

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Open_port
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL 
Java_org_mpich_MPI_MPI_1Open_1port(
    JNIEnv *env, 
    jclass class, 
    jint info)
{
    char port_name[MPI_MAX_PORT_NAME];
    int result;

    result = MPI_Open_port(info,port_name);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return (*env)->NewStringUTF(env,port_name);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Close_port
 * Signature: (Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Close_1port(
    JNIEnv *env, 
    jclass class, 
    jstring port_name)
{
    int result;
    const char *_port_name;

    _port_name = (*env)->GetStringUTFChars(env,port_name,NULL);
    result = MPI_Close_port(_port_name);
    (*env)->ReleaseStringUTFChars(env,port_name,_port_name);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_accept
 * Signature: (Ljava/lang/String;III)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Comm_1accept(
    JNIEnv *env, 
    jclass class, 
    jstring port_name, 
    jint info, 
    jint root, 
    jint comm)
{
    int result;
    const char *_port_name;
    int newcomm;

    _port_name = (*env)->GetStringUTFChars(env,port_name,NULL);
    result = MPI_Comm_accept(_port_name,info,root,comm,&newcomm);
    (*env)->ReleaseStringUTFChars(env,port_name,_port_name);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return newcomm;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_connect
 * Signature: (Ljava/lang/String;III)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Comm_1connect(
    JNIEnv *env, 
    jclass class, 
    jstring port_name, 
    jint info, 
    jint root, 
    jint comm)
{
    int result;
    const char *_port_name;
    int newcomm;

    _port_name = (*env)->GetStringUTFChars(env,port_name,NULL);
    result = MPI_Comm_connect(_port_name,info,root,comm,&newcomm);
    (*env)->ReleaseStringUTFChars(env,port_name,_port_name);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return newcomm;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Publish_name
 * Signature: (Ljava/lang/String;ILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Publish_1name(
    JNIEnv *env, 
    jclass class, 
    jstring service_name, 
    jint info, 
    jstring port_name)
{
    int result;
    const char *_service_name;
    const char *_port_name;

    _service_name = (*env)->GetStringUTFChars(env,service_name,NULL);
    _port_name = (*env)->GetStringUTFChars(env,port_name,NULL);

    result = MPI_Publish_name(_service_name,info,_port_name);

    (*env)->ReleaseStringUTFChars(env,port_name,_port_name);
    (*env)->ReleaseStringUTFChars(env,service_name,_service_name);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Unpublich_name
 * Signature: (Ljava/lang/String;ILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL
Java_org_mpich_MPI_MPI_1Unpublich_1name(
    JNIEnv *env, 
    jclass class, 
    jstring service_name, 
    jint info, 
    jstring port_name)
{
    int result;
    const char *_service_name;
    const char *_port_name;

    _service_name = (*env)->GetStringUTFChars(env,service_name,NULL);
    _port_name = (*env)->GetStringUTFChars(env,port_name,NULL);

    result = MPI_Unpublish_name(_service_name,info,_port_name);

    (*env)->ReleaseStringUTFChars(env,port_name,_port_name);
    (*env)->ReleaseStringUTFChars(env,service_name,_service_name);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Lookup_name
 * Signature: (Ljava/lang/String;I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL 
Java_org_mpich_MPI_MPI_1Lookup_1name(
    JNIEnv *env, 
    jclass class, 
    jstring service_name, 
    jint info)
{
    char port_name[MPI_MAX_PORT_NAME];
    int result;
    const char *_service_name;

    _service_name = (*env)->GetStringUTFChars(env,service_name,NULL);

    result = MPI_Lookup_name(_service_name,info,port_name);
    (*env)->ReleaseStringUTFChars(env,service_name,_service_name);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return (*env)->NewStringUTF(env,port_name);
}