#include "jni_mpi.h"
#include "jni_mpi_exception.h"

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Probe
 * Signature: (IIILorg/mpich/MPI_Status;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Probe(
    JNIEnv *env, 
    jclass class, 
    jint source, 
    jint tag, 
    jint comm, 
    jobject status)
{
    int result;
    MPI_Status stat;

    result = MPI_Probe(source,tag,comm,&stat);
    jni_mpi_convert_MPI_Status(env,status,&stat,
        FROM_MPI_STATUS_TO_JAVA_MPI_STATUS);
    
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return result;
}


/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Iprobe
 * Signature: (IIILorg/mpich/MPI_Status;)Z
 */
JNIEXPORT jboolean JNICALL 
Java_org_mpich_MPI_MPI_1Iprobe(
    JNIEnv *env, 
    jclass class, 
    jint source, 
    jint tag, 
    jint comm, 
    jobject status)
{
    int result;
    MPI_Status stat;
    int flag;

    result = MPI_Iprobe(source,tag,comm,&flag,&stat);
    jni_mpi_convert_MPI_Status(env,status,&stat,
        FROM_MPI_STATUS_TO_JAVA_MPI_STATUS);
    
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
 * Method:    MPI_Mprobe
 * Signature: (IIILorg/mpich/MPI_Message;Lorg/mpich/MPI_Status;)I
 */
JNIEXPORT jint JNICALL Java_org_mpich_MPI_MPI_1Mprobe(
    JNIEnv *env, 
    jclass class, 
    jint source, 
    jint tag, 
    jint comm, 
    jobject message, 
    jobject status)
{
    int result;
    MPI_Status stat;
    MPI_Message msg;

    result = MPI_Mprobe(source,tag,comm,&msg,&stat);
    jni_mpi_convert_MPI_Status(env,status,&stat,
        FROM_MPI_STATUS_TO_JAVA_MPI_STATUS);
    (*env)->SetIntField(env,message,JNI_MPI_MESSAGE_HANDLER,msg);
    
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return result;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Improbe
 * Signature: (IIILorg/mpich/MPI_Message;Lorg/mpich/MPI_Status;)Z
 */
JNIEXPORT jboolean JNICALL Java_org_mpich_MPI_MPI_1Improbe
  (JNIEnv *env, 
  jclass clss, 
  jint source, 
  jint tag, 
  jint comm, 
  jobject message, 
  jobject status)
{
    int result;
    MPI_Status stat;
    int flag;
    MPI_Message msg;

    result = MPI_Improbe(source,tag,comm,&flag,&msg,&stat);
    jni_mpi_convert_MPI_Status(env,status,&stat,
        FROM_MPI_STATUS_TO_JAVA_MPI_STATUS);
    (*env)->SetIntField(env,message,JNI_MPI_MESSAGE_HANDLER,msg);
    
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }
    
    if(flag == 1){
        return JNI_TRUE;
    }
    return JNI_FALSE;
}
