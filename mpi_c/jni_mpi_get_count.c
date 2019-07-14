#include "jni_mpi.h"
#include "jni_mpi_exception.h"

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Get_count
 * Signature: (Lorg/mpich/MPI_Status;I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Get_1count(
    JNIEnv *env, 
    jclass class, 
    jobject status, 
    jint datatype)
{
    MPI_Status s;
    int count;
    int result;
    int type;
    void* temp; // its never relay used

    jni_mpi_convert_MPI_Status(env,status,&s,FROM_JAVA_MPI_STATUS_TO_MPI_STATUS);
    jni_mpi_get_buffer(env,NULL,temp,datatype,type);

    result = MPI_Get_count(&s,type,&count);

    fn_exit:
        if(result != MPI_SUCCESS){
            jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
        }
        return count;
    fn_fail:
        return -1;

}
