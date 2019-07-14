#include "jni_mpi_status.h"
#include "jni_mpi.h"

void getStatus(JNIEnv *env,jobject obj,MPI_Status* stat)
{
    jobject status;
    int *_status;

    status = (*env)->CallObjectMethod(env,obj,gJniStatusGetStatus);
    if(status == NULL){
        return;
    }

    // get the data
#ifdef JNI_REGION_COPY
    // TODO: Java_mpi_datatype_Subarray__1create_1subarray JNI_REGION_COPY
#elif defined JNI_CRITICAL_SECTION
    getCriticalSection(env,status,0,JNI_STATUS_max_param,
        (void **)&_status,sizeof(int),0);
#endif
    stat->count_hi_and_cancelled = _status[JNI_STATUS_count_hi_and_cancelled];
    stat->count_lo = _status[JNI_STATUS_count_lo];
    stat->MPI_ERROR = _status[JNI_STATUS_mpi_error];
    stat->MPI_SOURCE = _status[JNI_STATUS_mpi_source];
    stat->MPI_TAG = _status[JNI_STATUS_mpi_tag];

    // get the data
#ifdef JNI_REGION_COPY
    // TODO: Java_mpi_datatype_Subarray__1create_1subarray JNI_REGION_COPY
#elif defined JNI_CRITICAL_SECTION
    relCriticalSection(env,status,0,JNI_STATUS_max_param,
        (void **)&_status,sizeof(int),JNI_ABORT);
#endif

    (*env)->DeleteLocalRef(env,status);
}


/**
 * setStatus(int count_lo,int count_hi_and_cancelled,
        int mpi_source,int mpi_tag,int mpi_error,boolean isReqFinish
 */
void setStatus(JNIEnv *env,jobject obj,MPI_Status* stat,jboolean flag)
{
    (*env)->CallVoidMethod(env,obj,gJniStatusSetStatus,
        stat->count_lo,stat->count_hi_and_cancelled,
        stat->MPI_SOURCE,stat->MPI_TAG,stat->MPI_ERROR,flag);
}