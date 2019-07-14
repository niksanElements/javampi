#include "jni_mpi.h"
#include "jni_mpi_exception.h"

#include <malloc.h>

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_File_open
 * Signature: (ILjava/lang/String;II)J
 */
JNIEXPORT jlong JNICALL 
Java_org_mpich_MPI_MPI_1File_1open(
    JNIEnv *env, 
    jclass class, 
    jint comm, 
    jstring filename, 
    jint amode, 
    jint info)
{
    MPI_File *file = malloc(sizeof(MPI_File));
    const char *_filename;
    int result;
    int fh;

    _filename = (*env)->GetStringUTFChars(env,filename,NULL);

    result = MPI_File_open(comm,_filename,amode,info,file);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return (long)file; 
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_File_close
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1File_1close(
    JNIEnv *env, 
    jclass class, 
    jlong fh)
{
    MPI_File* file;
    int result;

    file = (MPI_File*)fh;

    result = MPI_File_close(file);
    if(result == MPI_SUCCESS){
        free(file);
    }

    JNI_MPI_RETURN(result);        
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_File_delete
 * Signature: (Ljava/lang/String;I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1File_1delete(
    JNIEnv *env, 
    jclass class, 
    jstring filename, 
    jint info)
{
    const char *_filename;
    int result;

    _filename = (*env)->GetStringUTFChars(env,filename,NULL);
    result = MPI_File_delete(_filename,info);
    (*env)->ReleaseStringUTFChars(env,filename,_filename);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_File_set_size
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1File_1set_1size(
    JNIEnv *env, 
    jclass class, 
    jlong fh, 
    jlong size)
{
    MPI_File *file = NULL;
    int result;

    file = (MPI_File*)fh;
    result = MPI_File_set_size(*file,size);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_File_preallocate
 * Signature: (IJ)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1File_1preallocate(
    JNIEnv *env, 
    jclass class, 
    jlong fh, 
    jlong size)
{
    MPI_File *file = NULL;
    int result;

    file = (MPI_File*)fh;
    result = MPI_File_preallocate(*file,size);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_File_get_group
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1File_1get_1group(
    JNIEnv *env, 
    jclass class, 
    jlong fh)
{
    int group;
    MPI_File *file = NULL;
    int result;

    file = (MPI_File*)fh;

    result = MPI_File_get_group(*file,&group);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
        goto fn_fail;
    }

    fn_exit:
        return group;
    fn_fail:
        return -1;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_File_get_amode
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1File_1get_1amode(
    JNIEnv *env, 
    jclass class, 
    jlong fh)
{
    int amode;
    MPI_File *file = NULL;
    int result;

    file = (MPI_File*)fh;

    result = MPI_File_get_amode(*file,&amode);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
        goto fn_fail;
    }

    fn_exit:
        return amode;
    fn_fail:
        return -1;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_File_set_info
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1File_1set_1info(
    JNIEnv *env, 
    jclass class, 
    jlong fh, 
    jint info)
{
    MPI_File *file = NULL;
    int result;

    file = (MPI_File*)fh;

    result = MPI_File_set_info(*file,info);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
        goto fn_fail;
    }

    fn_exit:
        return MPI_SUCCESS;
    fn_fail:
        return -1;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_File_get_info
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1File_1get_1info(
    JNIEnv *env, 
    jclass class, 
    jlong fh)
{
    int info;
    MPI_File *file = NULL;
    int result;

    file = (MPI_File*)fh;

    result = MPI_File_get_info(*file,&info);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
        goto fn_fail;
    }

    fn_exit:
        return info;
    fn_fail:
        return -1;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_File_set_view
 * Signature: (IJIILjava/lang/String;I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1File_1set_1view(
    JNIEnv *env, 
    jclass class, 
    jlong fh, 
    jlong disp, 
    jint etype, 
    jint filetype, 
    jstring datarep, 
    jint info)
{
    MPI_File *file = NULL;
    int result;
    const char *_datarep;

    file = (MPI_File*)fh;
    JNI_GET_STRING(env,_datarep,datarep,NULL);
    result = MPI_File_set_view(*file,disp,etype,
        filetype,_datarep,info);
    (*env)->ReleaseStringUTFChars(env,datarep,_datarep);
    
    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_File_get_view_disp
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL 
Java_org_mpich_MPI_MPI_1File_1get_1view_1disp(
    JNIEnv *env, 
    jclass class, 
    jlong fh)
{
    long long disp;
    MPI_File* file;
    int result;
    char datarep[MPI_MAX_DATAREP_STRING];
    int etype;
    int filetype;

    file = (MPI_File*)fh;
    result = MPI_File_get_view(*file,&disp,&etype,
        &filetype,datarep);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
        goto fn_fail;
    }

    fn_exit:
        return disp;
    fn_fail:
        return -1;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_File_get_view_etyp
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1File_1get_1view_1etyp(
    JNIEnv *env, 
    jclass class, 
    jlong fh)
{
    long long disp;
    MPI_File* file;
    int result;
    char datarep[MPI_MAX_DATAREP_STRING];
    int etype;
    int filetype;

    file = (MPI_File*)fh;
    result = MPI_File_get_view(*file,&disp,&etype,
        &filetype,datarep);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
        goto fn_fail;
    }

    fn_exit:
        return etype;
    fn_fail:
        return -1;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_File_get_view_filetype
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1File_1get_1view_1filetype(
    JNIEnv *env, 
    jclass class, 
    jlong fh)
{
    long long disp;
    MPI_File* file;
    int result;
    char datarep[MPI_MAX_DATAREP_STRING];
    int etype;
    int filetype;

    file = (MPI_File*)fh;
    result = MPI_File_get_view(*file,&disp,&etype,
        &filetype,datarep);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
        goto fn_fail;
    }

    fn_exit:
        return filetype;
    fn_fail:
        return -1;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_File_get_view_datarep
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL 
Java_org_mpich_MPI_MPI_1File_1get_1view_1datarep(
    JNIEnv *env, 
    jclass class, 
    jlong fh)
{
    long long disp;
    MPI_File* file;
    int result;
    char datarep[MPI_MAX_DATAREP_STRING];
    int etype;
    int filetype;

    file = (MPI_File*)fh;
    result = MPI_File_get_view(*file,&disp,&etype,
        &filetype,datarep);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
        goto fn_fail;
    }

    fn_exit:
        return (*env)->NewStringUTF(env,datarep);
    fn_fail:
        return NULL;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_File_set_atomicity
 * Signature: (IZ)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1File_1set_1atomicity(
    JNIEnv *env, 
    jclass class, 
    jlong fh, 
    jboolean flag)
{
    int result;
    MPI_File* file;

    file = (MPI_File*)fh;

    result = MPI_File_set_atomicity(*file,flag);

    JNI_MPI_RETURN(result);
}
