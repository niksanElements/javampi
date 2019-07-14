#include "jni_mpi.h"
#include "jni_mpi_exception.h"

#define FUNCTION_MPI_WIN_ALLOCATE(func)\
    void *address;\
    int win;\
    int result;\
    int size;\
    size = (*env)->GetIntField(env,base,JNI_MPI_WIN_BUFFER_SIZE);\
    result = func(size,disp_unit,info,comm,&address,&win);\
    if(result != MPI_SUCCESS){\
        return JNI_ERR;\
    }\
    (*env)->SetLongField(env,base,JNI_MPI_WIN_BUFFER_BASE_ADDRESS,\
        (long)address);\
    (*env)->SetBooleanField(env,base,JNI_MPI_WIN_BUFFER_IS_ALLOC,\
        JNI_TRUE);\
    return win

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_create
 * Signature: (Lorg/mpich/MPI_Win_buffer;III)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1create(
    JNIEnv *env, 
    jclass class, 
    jobject base, 
    jint disp_unit, 
    jint info, 
    jint comm)
{
    jobject buffer;
    void* base_address;
    int result;
    int win;
    int size;

    buffer = (*env)->CallObjectMethod(env,base,
        JNI_MPI_WIN_BUFFER_GET);
    base_address = (*env)->GetDirectBufferAddress(env,buffer);
    size = (*env)->GetDirectBufferCapacity(env,buffer);

    result = MPI_Win_create(base_address,size,disp_unit,info,comm,&win);
    // It is not necessary to delete the buffer
    (*env)->DeleteLocalRef(env,buffer);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return win;
}


/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_allocate
 * Signature: (IIILorg/mpich/MPI_Win_buffer;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1allocate(
    JNIEnv *env, 
    jclass class, 
    jint disp_unit, 
    jint info, 
    jint comm, 
    jobject base)
{
    FUNCTION_MPI_WIN_ALLOCATE(MPI_Win_allocate);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_allocate_shared
 * Signature: (IIILorg/mpich/MPI_Win_buffer;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1allocate_1shared(
    JNIEnv *env, 
    jclass class, 
    jint disp_unit, 
    jint info, 
    jint comm, 
    jobject base)
{
    FUNCTION_MPI_WIN_ALLOCATE(MPI_Win_allocate_shared);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_shared_query
 * Signature: (IILorg/mpich/MPI_Win_buffer;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1shared_1query(
    JNIEnv *env, 
    jclass class, 
    jint win, 
    jint rank, 
    jobject base)
{
    int result;
    void *baseptr;
    MPI_Aint size;
    int disp_unit;

    result = MPI_Win_shared_query(win,rank,&size,&disp_unit,&baseptr);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    (*env)->SetLongField(env,base,JNI_MPI_WIN_BUFFER_BASE_ADDRESS,
        (long)baseptr);
    (*env)->SetBooleanField(env,base,JNI_MPI_WIN_BUFFER_IS_ALLOC,
        JNI_TRUE);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_create_dynamic
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1create_1dynamic(
    JNIEnv *env, 
    jclass class, 
    jint info, 
    jint comm)
{
    int result;
    int win;

    result = MPI_Win_create_dynamic(info,comm,&win);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return win;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_attach
 * Signature: (ILorg/mpich/MPI_Win_buffer;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1attach(
    JNIEnv *env, 
    jclass class, 
    jint win, 
    jobject base)
{
    jobject buff;
    int size;
    void *baseptr;
    int result;

    buff = (*env)->CallObjectMethod(env,base,JNI_MPI_WIN_BUFFER_GET);
    baseptr = (*env)->GetDirectBufferAddress(env,buff);
    size = (*env)->GetDirectBufferCapacity(env,buff);

    result = MPI_Win_attach(win,baseptr,size);
    (*env)->DeleteLocalRef(env,buff);
    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_detach
 * Signature: (ILorg/mpich/MPI_Win_buffer;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1detach(
    JNIEnv *env, 
    jclass class, 
    jint win, 
    jobject base)
{
    jobject buff;
    int size;
    const void *baseptr;
    int result;

    buff = (*env)->CallObjectMethod(env,base,JNI_MPI_WIN_BUFFER_GET);
    baseptr = (*env)->GetDirectBufferAddress(env,buff);
    size = (*env)->GetDirectBufferCapacity(env,buff);

    result = MPI_Win_detach(win,base);
    (*env)->DeleteLocalRef(env,buff);
    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_free
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1free(
    JNIEnv *env, 
    jclass class, 
    jint win)
{
    int result;

    result = MPI_Win_free(&win);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return win;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_get_attr
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1get_1attr(
    JNIEnv *env, 
    jclass class, 
    jint win, 
    jint win_keyval)
{
    // TODO: MPI_Win_get_attr
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_get_group
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1get_1group(
    JNIEnv *env, 
    jclass class, 
    jint win)
{
    int result;
    int group;

    result = MPI_Win_get_group(win,&group);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return group;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_set_info
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1set_1info(
    JNIEnv *env, 
    jclass class, 
    jint win, 
    jint info)
{
    int result;

    result = MPI_Win_set_info(win,info);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_get_info
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1get_1info(
    JNIEnv *env, 
    jclass class, 
    jint win)
{
    int info;
    int result;

    result = MPI_Win_get_info(win,&info);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return info;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_fence
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1fence(
    JNIEnv *env, 
    jclass class, 
    jint assert, 
    jint win)
{
    int result;

    result = MPI_Win_fence(assert,win);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_start
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1start(
    JNIEnv *env, 
    jclass class, 
    jint group, 
    jint ass, 
    jint win)
{
    int result;

    result = MPI_Win_start(group,ass,win);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_complete
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1complete(
    JNIEnv *env, 
    jclass class, 
    jint win)
{
    int result;

    result = MPI_Win_complete(win);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_post
 * Signature: (III)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1post(
    JNIEnv *env, 
    jclass class, 
    jint group, 
    jint ass, 
    jint win)
{
    int result;

    result = MPI_Win_post(group,ass,win);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_wait
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1wait(
    JNIEnv *env, 
    jclass class, 
    jint win)
{
    int result;

    result = MPI_Win_wait(win);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_test
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL 
Java_org_mpich_MPI_MPI_1Win_1test(
    JNIEnv *env, 
    jclass class, 
    jint win)
{
    int flag;
    int result;

    result = MPI_Win_test(win,&flag);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    if(flag == 1){
        return JNI_TRUE;
    }

    return JNI_FALSE;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_lock
 * Signature: (IIII)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1lock(
    JNIEnv *env, 
    jclass class, 
    jint lock_type, 
    jint rank, 
    jint ass, 
    jint win)
{
    int result;

    result = MPI_Win_lock(lock_type,rank,ass,win);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_lock_all
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1lock_1all(
    JNIEnv *env, 
    jclass class, 
    jint ass, 
    jint win)
{
    int result;

    result = MPI_Win_lock_all(ass,win);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_unlock
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1unlock(
    JNIEnv *env, 
    jclass class, 
    jint rank, 
    jint win)
{
    int result;

    result = MPI_Win_unlock(rank,win);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_unlock_all
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1unlock_1all(
    JNIEnv *env, 
    jclass class, 
    jint win)
{
    int result;

    result = MPI_Win_unlock_all(win);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_flush
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1flush(
    JNIEnv *env, 
    jclass class, 
    jint rank, 
    jint win)
{
    int result;

    result = MPI_Win_flush(rank,win);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_flush_all
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1flush_1all(
    JNIEnv *env, 
    jclass class, 
    jint win)
{
    int result;

    result = MPI_Win_flush_all(win);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_flush_local
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1flush_1local(
    JNIEnv *env, 
    jclass class, 
    jint rank, 
    jint win)
{
    int result;

    result = MPI_Win_flush_local(rank,win);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_flush_local_all
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1flush_1local_1all(
    JNIEnv *env, 
    jclass class, 
    jint win)
{
    int result;

    result = MPI_Win_flush_local_all(win);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Win_sync
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Win_1sync(
    JNIEnv *env, 
    jclass class, 
    jint win)
{
    int result;

    result = MPI_Win_sync(win);

    JNI_MPI_RETURN(result);
}

