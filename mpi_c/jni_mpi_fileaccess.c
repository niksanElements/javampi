#include "jni_mpi.h"
#include "jni_mpi_exception.h"
#include "file.h"

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_File_read_at
 * Signature: (IJLjava/lang/Object;IILorg/mpich/MPI_Status;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1File_1read_1at(
    JNIEnv *env, 
    jclass class, 
    jlong fh, 
    jlong offset, 
    jobject buff, 
    jint count, 
    jint datatype, 
    jobject stat)
{
    int mpi_type;
    void *_buff;
    int result;
    MPI_File *file;

    file = (MPI_File*)fh;

    if(datatype != org_mpich_MPI_OBJECT){
        jni_mpi_get_buffer(env,buff,_buff,datatype,mpi_type);
    }

    if(stat == NULL){
        result = MPI_File_read_at(*file,offset,_buff,count,mpi_type,
            MPI_STATUS_IGNORE);
    }
    else{
        MPI_Status _stat;
        result = MPI_File_read_at(*file,offset,_buff,count,mpi_type,
            &_stat);
        jni_mpi_convert_MPI_Status(env,stat,&_stat,
            FROM_MPI_STATUS_TO_JAVA_MPI_STATUS);
    }

    if(datatype != org_mpich_MPI_OBJECT){
        jni_mpi_rel_buffer(env,buff,_buff,datatype,JNI_COMMIT);
    }

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_File_read_at_all
 * Signature: (IJLjava/lang/Object;IILorg/mpich/MPI_Status;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1File_1read_1at_1all(
    JNIEnv *env, 
    jclass class, 
    jlong fh, 
    jlong offset, 
    jobject buff, 
    jint count, 
    jint datatype, 
    jobject stat)
{

}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_File_write_at
 * Signature: (IJLjava/lang/Object;IILorg/mpich/MPI_Status;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1File_1write_1at(
    JNIEnv *env, 
    jclass class, 
    jlong fh, 
    jlong offset, 
    jobject buff, 
    jint count, 
    jint datatype, 
    jobject stat)
{
        int mpi_type;
    void *_buff;
    int result;
    MPI_File *file;

    file = (MPI_File*)fh;

    if(datatype != org_mpich_MPI_OBJECT){
        jni_mpi_get_buffer(env,buff,_buff,datatype,mpi_type);
    }

    if(stat == NULL){
        result = MPI_File_write_at(*file,offset,_buff,count,mpi_type,
            MPI_STATUS_IGNORE);
    }
    else{
        MPI_Status _stat;
        result = MPI_File_write_at(*file,offset,_buff,count,mpi_type,
            &_stat);
        jni_mpi_convert_MPI_Status(env,stat,&_stat,
            FROM_MPI_STATUS_TO_JAVA_MPI_STATUS);
    }

    if(datatype != org_mpich_MPI_OBJECT){
        jni_mpi_rel_buffer(env,buff,_buff,datatype,JNI_ABORT);
    }

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_File_write_at_all
 * Signature: (IJLjava/lang/Object;IILorg/mpich/MPI_Status;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1File_1write_1at_1all(
    JNIEnv *env, 
    jclass class, 
    jlong fh, 
    jlong offset, 
    jobject buff, 
    jint count, 
    jint datatype, 
    jobject stat)
{

}
