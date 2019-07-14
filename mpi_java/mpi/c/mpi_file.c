#include "mpi_File.h"
#include "jni_mpi.h"

/**
 * access mode
 */
/*
 * Class:     mpi_File
 * Method:    _amode
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL 
Java_mpi_File__1amode(
    JNIEnv *env, jclass class, jlong file)
{
    MPI_File *_file = (MPI_File*)file;
    int amode;

    if(MPI_File_get_amode(*_file,&amode) != MPI_SUCCESS){
        mpiFileException(env,"MPI_File_get_amode");
    }

    return amode;
}

/**
 * atomicity
 */
/*
 * Class:     mpi_File
 * Method:    _atomicity
 * Signature: (JZ)V
 */
JNIEXPORT void JNICALL 
Java_mpi_File__1atomicity__JZ(
    JNIEnv *env, jclass class, jlong file, jboolean flag)
{
    MPI_File *_file = (MPI_File*)file;
    if(MPI_File_set_atomicity(*_file,(int)flag) != MPI_SUCCESS){
        mpiFileException(env,"MPI_File_set_atomicity");
    }
}


/*
 * Class:     mpi_File
 * Method:    _atomicity
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL 
Java_mpi_File__1atomicity__J(
    JNIEnv *env, jclass class, jlong file)
{
    MPI_File *_file = (MPI_File*)file;
    int flag; 
    if(MPI_File_get_atomicity(*_file,&flag) != MPI_SUCCESS){
        mpiFileException(env,"MPI_File_get_atomicity");
    }

    return (jboolean)flag;
}

/*
 * Class:     mpi_File
 * Method:    _get_group
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_File__1get_1group(
    JNIEnv *env, jclass class, jlong file)
{
    MPI_File *_file = (MPI_File*)file;
    MPI_Group group;

    if(MPI_File_get_group(*_file,&group) != MPI_SUCCESS){
        mpiFileException(env,"MPI_File_get_group");
    }

    return (jlong)group;
}

/*
 * Class:     mpi_File
 * Method:    _info
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_File__1info(
    JNIEnv *env, jclass class, jlong file)
{
    MPI_Info info;
    MPI_File *_file = (MPI_File*)file;

    if(MPI_File_get_info(*_file,&info) != MPI_SUCCESS){
        mpiFileException(env,"MPI_File_get_info");
    }

    return (jlong)info;
}

/*
 * Class:     mpi_File
 * Method:    _get_position
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_File__1get_1position(
    JNIEnv *env, jclass class, jlong file)
{
    MPI_Offset offset;
    MPI_File *_file = (MPI_File*)file;

    if(MPI_File_get_position(*_file,&offset) != MPI_SUCCESS){
        mpiFileException(env,"MPI_File_get_position");
    }

    return (jlong)offset;
}

/*
 * Class:     mpi_File
 * Method:    _get_position_shared
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_File__1get_1position_1shared(
    JNIEnv *env, jclass class, jlong file)
{
    MPI_Offset offset;
    MPI_File *_file = (MPI_File*)file;

    if(MPI_File_get_position_shared(*_file,&offset) != MPI_SUCCESS){
        mpiFileException(env,"MPI_File_get_position");
    }

    return (jlong)offset;
}

/*
 * Class:     mpi_File
 * Method:    _set_size
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL 
Java_mpi_File__1set_1size(
    JNIEnv *env, jclass class, jlong file, jlong size)
{
    MPI_File *_file = (MPI_File*)file;

    if(MPI_File_set_size(*_file,(MPI_Offset)size) != MPI_SUCCESS){
        mpiFileException(env,"MPI_File_set_size");
    }
}

/*
 * Class:     mpi_File
 * Method:    _get_size
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_File__1get_1size(
    JNIEnv *env, jclass class, jlong file)
{
    MPI_File *_file = (MPI_File*)file;
    MPI_Offset size;

    if(MPI_File_get_size(*_file,&size) != MPI_SUCCESS){
        mpiFileException(env,"MPI_File_get_size");
    }

    return (jlong)size;
}

/*
 * Class:     mpi_File
 * Method:    _preallocate
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL 
Java_mpi_File__1preallocate(
    JNIEnv *env, jclass class, jlong file, jlong preallocate)
{
    MPI_File *_file = (MPI_File*)file;
    
    if(MPI_File_preallocate(*_file,preallocate) != MPI_SUCCESS){
        mpiFileException(env,"MPI_File_preallocate");
    }
}

/*
 * Class:     mpi_File
 * Method:    _seek
 * Signature: (JJI)V
 */
JNIEXPORT void JNICALL 
Java_mpi_File__1seek(
    JNIEnv *env, jclass class, 
    jlong file, jlong offset, jint whance)
{
    MPI_File *_file = (MPI_File*)file;
    
    if(MPI_File_seek(*_file,offset,whance) != MPI_SUCCESS){
        mpiFileException(env,"MPI_File_seek");
    }
}

/*
 * Class:     mpi_File
 * Method:    _seek_shared
 * Signature: (JJI)V
 */
JNIEXPORT void JNICALL 
Java_mpi_File__1seek_1shared(
    JNIEnv *env, jclass class, 
    jlong file, jlong offset, jint whance)
{
    MPI_File *_file = (MPI_File*)file;
    
    if(MPI_File_seek_shared(*_file,offset,whance) != MPI_SUCCESS){
        mpiFileException(env,"MPI_File_seek");
    }
       
}