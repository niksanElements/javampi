#include "jni_mpi.h"
#include "jni_mpi_exception.h"


/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_compare
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Comm_1compare(
    JNIEnv *env, 
    jclass class, 
    jint comm1, 
    jint comm2)
{
    int result;
    int flag;

    result = MPI_Comm_compare(comm1,comm2,&flag);
    if(MPI_SUCCESS != result){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return flag;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_dup
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Comm_1dup(
    JNIEnv *env, 
    jclass class, 
    jint comm)
{
    int result;
    int newcomm;

    result = MPI_Comm_dup(comm,&newcomm);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return newcomm;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_dup_with_info
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Comm_1dup_1with_1info(
    JNIEnv *env, 
    jclass class, 
    jint comm, 
    jint info)
{
    int result;
    int newcomm;

    result = MPI_Comm_dup_with_info(comm,info,&newcomm);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return newcomm;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_idup
 * Signature: (ILorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Comm_1idup(
    JNIEnv *env, 
    jclass class, 
    jint comm, 
    jobject req)
{
    // TODO: Java_org_mpich_MPI_MPI_1Comm_1idup
    return -1;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_create
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Comm_1create(
    JNIEnv *env, 
    jclass class, 
    jint comm, 
    jint group)
{
    int result;
    int newcomm;

    result = MPI_Comm_create(comm,group,&newcomm);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return newcomm;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_create_group
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Comm_1create_1group(
    JNIEnv *env, 
    jclass class, 
    jint comm, 
    jint group, 
    jint tag)
{
    int result;
    int newcomm;

    result = MPI_Comm_create_group(comm,group,tag,&newcomm);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return newcomm;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_split
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Comm_1split(
    JNIEnv *env, 
    jclass class, 
    jint comm, 
    jint color, 
    jint key)
{
    int result;
    int newcomm;

    result = MPI_Comm_split(comm,color,key,&newcomm);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return newcomm;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_split_type
 * Signature: (IIII)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Comm_1split_1type(
    JNIEnv *env, 
    jclass class, 
    jint comm, 
    jint split_type, 
    jint key, 
    jint info)
{
    int result;
    int newcomm;

    result = MPI_Comm_split_type(comm,split_type,key,info,&newcomm);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return newcomm;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_free
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Comm_1free(
    JNIEnv *env, 
    jclass class, 
    jint comm)
{
    int result;

    result = MPI_Comm_free(&comm);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return comm;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_set_info
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Comm_1set_1info(
    JNIEnv *env, 
    jclass class, 
    jint comm, 
    jint info)
{
    int result;

    result = MPI_Comm_set_info(comm,info);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_get_info
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Comm_1get_1info(
    JNIEnv *env, 
    jclass class, 
    jint comm)
{
    int info;
    int result;

    result = MPI_Comm_get_info(comm,&info);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return info;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_group
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Comm_1group(
    JNIEnv *env, 
    jclass class, 
    jint comm)
{
    int group;
    int result;

    result = MPI_Comm_group(comm,&group);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return group;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_test_inter
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Comm_1test_1inter(
    JNIEnv * env, 
    jclass class, 
    jint comm)
{
    int result;
    int flag;

    result = MPI_Comm_test_inter(comm,&flag);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return flag;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_remote_size
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Comm_1remote_1size(
    JNIEnv *env, 
    jclass class, 
    jint comm)
{
    int result;
    int size;

    result = MPI_Comm_remote_size(comm,&size);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return size;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_remote_group
 * Signature: (I)I
 */
JNIEXPORT jint 
JNICALL Java_org_mpich_MPI_MPI_1Comm_1remote_1group(
    JNIEnv *env, 
    jclass class, 
    jint comm)
{
    int result;
    int group;

    result = MPI_Comm_remote_group(comm,&group);

    return group;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Comm_set_name
 * Signature: (ILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Comm_1set_1name(
    JNIEnv *env, 
    jclass class, 
    jint comm, 
    jstring name)
{
    int result;
    const char* _name = (*env)->GetStringUTFChars(env,name,NULL);

    result = MPI_Comm_set_name(comm,_name);
    
    (*env)->ReleaseStringUTFChars(env,name,_name);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Com_get_name
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL 
Java_org_mpich_MPI_MPI_1Com_1get_1name(
    JNIEnv *env, 
    jclass class, 
    jint comm)
{
    char name[MPI_MAX_OBJECT_NAME];
    int result;
    int len;

    result = MPI_Comm_get_name(comm,name,&len);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return (*env)->NewStringUTF(env,name);
}
