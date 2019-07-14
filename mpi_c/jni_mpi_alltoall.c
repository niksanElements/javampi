#include "jni_mpi_collective.h"

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Alltoall
 * Signature: (Ljava/lang/Object;IILjava/lang/Object;III)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Alltoall(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jint sendcount, 
    jint sendtype, 
    jobject recvbuff, 
    jint recvcount, 
    jint recvtype, 
    jint comm)
{
    FUNCTION_COLLALL(MPI_Alltoall);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Ialltoall
 * Signature: (Ljava/lang/Object;IILjava/lang/Object;IIILorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Ialltoall(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jint sendcount, 
    jint sendtype, 
    jobject recvbuff, 
    jint recvcount, 
    jint recvtype, 
    jint comm, 
    jobject req)
{
    FUNCTION_ICOLLALL(MPI_Ialltoall);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Alltoallv
 * Signature: (Ljava/lang/Object;[I[IILjava/lang/Object;[I[III)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Alltoallv(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jintArray sendcounts, 
    jintArray senddisp, 
    jint sendtype, 
    jobject recvbuff, 
    jintArray recvcounts, 
    jintArray recvdisp, 
    jint recvtype, 
    jint comm)
{
    int result;
    int send_mpi_type;
    int recv_mpi_type;
    void* c_send_buff;
    void* c_recv_buff;
    jint* c_s_counts;
    jint* c_r_counts;
    jint* c_s_disp;
    jint* c_r_disp;

    if(sendtype != org_mpich_MPI_OBJECT){
        jni_mpi_get_buffer(env,sendbuff,
            c_send_buff,sendtype,send_mpi_type);
    }

    if(recvtype != org_mpich_MPI_OBJECT){
        jni_mpi_get_buffer(env,recvbuff,
            c_recv_buff,recvtype,recv_mpi_type);
    }
    c_s_counts = (*env)->GetIntArrayElements(env,sendcounts,NULL);
    c_r_counts = (*env)->GetIntArrayElements(env,recvcounts,NULL);
    c_s_disp = (*env)->GetIntArrayElements(env,senddisp,NULL);
    c_r_disp = (*env)->GetIntArrayElements(env,recvdisp,NULL);

    result = MPI_Alltoallv(c_send_buff,c_s_counts,c_s_disp,send_mpi_type,
        c_recv_buff,c_r_counts,c_s_counts,recv_mpi_type,comm);
    
    if(sendtype != org_mpich_MPI_OBJECT){
        jni_mpi_rel_buffer(env,sendbuff,c_send_buff,sendtype,JNI_ABORT);
    }

    if(recvtype != org_mpich_MPI_OBJECT){
        jni_mpi_rel_buffer(env,recvbuff,c_recv_buff,recvtype,JNI_COMMIT);
    }
    (*env)->ReleaseIntArrayElements(env,sendcounts,c_s_counts,JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env,recvcounts,c_r_counts,JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env,senddisp,c_s_disp,JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env,recvdisp,c_r_disp,JNI_ABORT);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Ialltoallv
 * Signature: (Ljava/lang/Object;[I[IILjava/lang/Object;[I[IIILorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Ialltoallv(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jintArray sendcounts, 
    jintArray senddisp, 
    jint sendtype, 
    jobject recvbuff, 
    jintArray recvcounts, 
    jintArray recvdisp, 
    jint recvtype, 
    jint comm, 
    jobject req)
{
    int result;
    int send_mpi_type;
    int recv_mpi_type;
    icom_element_t *ele = malloc(sizeof(icom_element_t));
    if(ele == NULL){
        goto fn_fail;
    }

    if(sendtype != org_mpich_MPI_OBJECT){
        ele->sendbuff = (*env)->NewGlobalRef(env,sendbuff);
        ele->sendtype = sendtype;
        jni_mpi_get_buffer(env,ele->sendbuff,
            ele->c_sendbuff,sendtype,send_mpi_type);
    }

    if(recvtype != org_mpich_MPI_OBJECT){
        ele->glob_array_ref = (*env)->NewGlobalRef(env,recvbuff);
        ele->datatype = recvtype;
        jni_mpi_get_buffer(env,ele->glob_array_ref,
            ele->buff,recvtype,recv_mpi_type);
    }
    ele->counts_object = (*env)->NewGlobalRef(env,sendcounts);
    ele->counts_buff = (*env)->GetIntArrayElements(env,
        ele->counts_object,NULL);
    ele->counts2_object = (*env)->NewGlobalRef(env,recvcounts);
    ele->counts2_buff = (*env)->GetIntArrayElements(env,
        ele->counts2_object,NULL);
    ele->disp_object = (*env)->NewGlobalRef(env,senddisp);
    ele->disp_buff = (*env)->GetIntArrayElements(env,
        ele->disp_object,NULL);
    ele->disp2_object = (*env)->NewGlobalRef(env,recvdisp);
    ele->disp2_buff = (*env)->GetIntArrayElements(env,
        ele->disp2_object,NULL);

    result = MPI_Ialltoallv(ele->c_sendbuff,ele->counts_buff,
        ele->disp_buff,send_mpi_type,
        ele->buff,ele->counts2_buff,ele->disp2_buff,recv_mpi_type,
        comm,&ele->req);
        
    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_HANDLER,
        ele->req);
    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_TYPE,
        JNI_MPI_REQUEST_TYPE_RECV);

    JNI_MPI_RETURN(result);
}