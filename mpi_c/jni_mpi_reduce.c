#include "jni_mpi_collective.h"

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Reduce
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;IIIII)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Reduce(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jobject recvbuff,
    jint count, 
    jint type, 
    jint op, 
    jint root, 
    jint comm)
{
    int result;
    int mpi_type;
    void *c_send_buf;
    void *c_recv_buf;

    if(type != org_mpich_MPI_OBJECT){
        jni_mpi_get_buffer(env,sendbuff,c_send_buf,type,mpi_type);
        jni_mpi_get_buffer(env,recvbuff,c_recv_buf,type,mpi_type);
    }

    result = MPI_Reduce(c_send_buf,c_recv_buf,count,mpi_type,op,root,comm);

    if(type != org_mpich_MPI_OBJECT){
        jni_mpi_rel_buffer(env,sendbuff,c_send_buf,type,JNI_ABORT);
        jni_mpi_rel_buffer(env,recvbuff,c_recv_buf,type,JNI_COMMIT);
    }

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Ireduce
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;IIIIILorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL
Java_org_mpich_MPI_MPI_1Ireduce(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jobject recvbuff, 
    jint count, 
    jint type, 
    jint op, 
    jint root, 
    jint comm, 
    jobject req)
{
    int result;
    int mpi_type;
    icom_element_t* ele = malloc(sizeof(icom_element_t));
    if(ele == NULL){
        goto fn_fail;
    }
    init_icom_element(ele);
    if(type != org_mpich_MPI_OBJECT){
        ele->sendbuff = (*env)->NewGlobalRef(env,sendbuff);
        ele->glob_array_ref = (*env)->NewGlobalRef(env,recvbuff);
        ele->datatype = type;
        ele->sendtype = type;
        jni_mpi_get_buffer(env,ele->sendbuff,
            ele->c_sendbuff,type,mpi_type);
        jni_mpi_get_buffer(env,ele->glob_array_ref,
            ele->buff,type,mpi_type);
    }

    OPA_Queue_enqueue(&JNI_MPI_QHEAD_IRECV,
        ele,icom_element_t,hdr);
    
    result = MPI_Ireduce(ele->c_sendbuff,ele->buff,
        count,mpi_type,op,root,comm,&ele->req);

    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_HANDLER,
        ele->req);
    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_TYPE,
        JNI_MPI_REQUEST_TYPE_RECV);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Allreduce
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;IIII)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Allreduce(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jobject recvbuff, 
    jint count, 
    jint type, 
    jint op, 
    jint comm)
{
    int result;
    int mpi_type;
    void *c_send_buf;
    void *c_recv_buf;

    if(type != org_mpich_MPI_OBJECT){
        jni_mpi_get_buffer(env,sendbuff,c_send_buf,type,mpi_type);
        jni_mpi_get_buffer(env,recvbuff,c_recv_buf,type,mpi_type);
    }

    result = MPI_Allreduce(c_send_buf,c_recv_buf,count,mpi_type,op,comm);

    if(type != org_mpich_MPI_OBJECT){
        jni_mpi_rel_buffer(env,sendbuff,c_send_buf,type,JNI_ABORT);
        jni_mpi_rel_buffer(env,recvbuff,c_recv_buf,type,JNI_COMMIT);
    }

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Iallreduce
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;IIIILorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Iallreduce(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jobject recvbuff, 
    jint count, 
    jint type, 
    jint op, 
    jint comm, 
    jobject req)
{
    int result;
    int mpi_type;
    icom_element_t* ele = malloc(sizeof(icom_element_t));
    if(ele == NULL){
        goto fn_fail;
    }
    init_icom_element(ele);
    if(type != org_mpich_MPI_OBJECT){
        ele->sendbuff = (*env)->NewGlobalRef(env,sendbuff);
        ele->glob_array_ref = (*env)->NewGlobalRef(env,recvbuff);
        ele->datatype = type;
        ele->sendtype = type;
        jni_mpi_get_buffer(env,ele->sendbuff,
            ele->c_sendbuff,type,mpi_type);
        jni_mpi_get_buffer(env,ele->glob_array_ref,
            ele->buff,type,mpi_type);
    }

    OPA_Queue_enqueue(&JNI_MPI_QHEAD_IRECV,
        ele,icom_element_t,hdr);
    
    result = MPI_Iallreduce(ele->c_sendbuff,ele->buff,
        count,mpi_type,op,comm,&ele->req);

    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_HANDLER,
        ele->req);
    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_TYPE,
        JNI_MPI_REQUEST_TYPE_RECV);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Reduce_scatter
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;[IIII)I
 */
JNIEXPORT jint JNICALL Java_org_mpich_MPI_MPI_1Reduce_1scatter(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jobject recvbuff, 
    jintArray counts, 
    jint type, 
    jint op, 
    jint comm)
{
    int result;
    int mpi_type;
    void *c_send_buf;
    void *c_recv_buf;
    jint* _counts;

    if(type != org_mpich_MPI_OBJECT){
        _counts = (*env)->GetIntArrayElements(env,counts,NULL);
        jni_mpi_get_buffer(env,sendbuff,c_send_buf,type,mpi_type);
        jni_mpi_get_buffer(env,recvbuff,c_recv_buf,type,mpi_type);
    }

    result = MPI_Reduce_scatter(c_send_buf,c_recv_buf,_counts,mpi_type,op,comm);

    if(type != org_mpich_MPI_OBJECT){
        (*env)->ReleaseIntArrayElements(env,counts,_counts,JNI_ABORT);
        jni_mpi_rel_buffer(env,sendbuff,c_send_buf,type,JNI_ABORT);
        jni_mpi_rel_buffer(env,recvbuff,c_recv_buf,type,JNI_COMMIT);
    }

    JNI_MPI_RETURN(result);
}


/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Ireduce_scatter
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;[IIIILorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Ireduce_1scatter(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jobject recvbuff, 
    jintArray counts, 
    jint type, 
    jint op, 
    jint comm, 
    jobject req)
{
    int result;
    int mpi_type;
    icom_element_t* ele = malloc(sizeof(icom_element_t));
    if(ele == NULL){
        goto fn_fail;
    }
    init_icom_element(ele);
    if(type != org_mpich_MPI_OBJECT){
        ele->sendbuff = (*env)->NewGlobalRef(env,sendbuff);
        ele->glob_array_ref = (*env)->NewGlobalRef(env,recvbuff);
        ele->counts_object = (*env)->NewGlobalRef(env,counts);
        ele->datatype = type;
        ele->sendtype = type;
        jni_mpi_get_buffer(env,ele->sendbuff,
            ele->c_sendbuff,type,mpi_type);
        jni_mpi_get_buffer(env,ele->glob_array_ref,
            ele->buff,type,mpi_type);
        ele->counts_buff = (*env)->GetIntArrayElements(env,ele->counts_object,NULL);
    }

    OPA_Queue_enqueue(&JNI_MPI_QHEAD_IRECV,
        ele,icom_element_t,hdr);
    
    result = MPI_Ireduce_scatter(ele->c_sendbuff,ele->buff,
        ele->counts_buff,mpi_type,op,comm,&ele->req);

    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_HANDLER,
        ele->req);
    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_TYPE,
        JNI_MPI_REQUEST_TYPE_RECV);

    JNI_MPI_RETURN(result);
}


/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Reduce_scatter_block
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;IIII)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Reduce_1scatter_1block(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jobject recvbuff, 
    jint count, 
    jint type, 
    jint op, 
    jint comm)
{
    FUNCTION_REDBLOCK_SCAN(MPI_Reduce_scatter_block);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Ireduce_scatter_block
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;IIIILorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Ireduce_1scatter_1block(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jobject recvbuff, 
    jint count, 
    jint type, 
    jint op, 
    jint comm, 
    jobject req)
{
    FUNCTION_IREDBLOCK_SCAN(MPI_Ireduce_scatter_block);
}