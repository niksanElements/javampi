#include "jni_mpi_collective.h"

#include "memory.h"

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Scatter
 * Signature: (Ljava/lang/Object;IILjava/lang/Object;IIII)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Scatter(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jint sendcount,
    jint sendtype,
    jobject recvbuff,
    jint recvcount,
    jint recvtype, 
    jint root, 
    jint comm)
{
    FUNCTION_SCATTGATH(MPI_Scatter);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Gather
 * Signature: (Ljava/lang/Object;IILjava/lang/Object;IIII)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Gather(
    JNIEnv *env, jclass class, 
    jobject sendbuff, 
    jint sendcount, 
    jint sendtype, 
    jobject recvbuff, 
    jint recvcount, 
    jint recvtype, 
    jint root, 
    jint comm)
{
    FUNCTION_SCATTGATH(MPI_Gather);
}

/**
 * NOTE:
 * The function bellow are using 2 dimensional array for the main operation.
 * For Scatter function you have to pass arguments:
 *      sendbuff: 2 dimensional array
 *      recvbuff: 1 dimensional array
 * For Gather is around:
 *      sendbuff: 1 dimensional array
 *      recvbuff: 2 dimensional array
 */


/*
 * Class:     org_mpich_MPI
 * Method:    MPI_2DScatter
 * Signature: (Ljava/lang/Object;IILjava/lang/Object;IIII)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_12DScatter(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jint sendcount,
    jint sendtype, 
    jobject recvbuff, 
    jint recvcount,
    jint recvtype, 
    jint root, 
    jint comm)
{
    int result;
    void *c_send_buff;
    void *c_recv_buff;
    int send_mpi_type;
    int recv_mpi_type;
    
    // get all send buffer
    if(sendtype != org_mpich_MPI_OBJECT){
        int ele_count = (*env)->GetArrayLength(env,sendbuff);
        int numOfBytes = jni_mpi_sizeof(sendtype);
        jint size = sendcount*numOfBytes;

        c_send_buff = malloc(ele_count*size);
        if(c_send_buff == NULL){
            goto fn_fail;
        }

        /**
         * Every element of the buffer is array e.c 
         * 2 dimensional array.
         */
        for(int i = 0;i < ele_count;i++){
            jarray ele = (*env)->GetObjectArrayElement(env,sendbuff,i);
            void *temp;
            void *ptr = (((jbyte*)c_send_buff)+(i*size));

            jni_mpi_get_buffer(env,ele,temp,sendtype,send_mpi_type);
            memcpy(ptr,temp,size);
            jni_mpi_rel_buffer(env,ele,(void*)temp,sendtype,JNI_ABORT);
            (*env)->DeleteLocalRef(env,ele);
        }
    }

    if(recvtype != org_mpich_MPI_OBJECT){
        jni_mpi_get_buffer(env,recvbuff,c_recv_buff,recvtype,recv_mpi_type);
    }

    // perform the main operation
    result = MPI_Scatter(c_send_buff,sendcount,send_mpi_type,
        c_recv_buff,recvcount,recv_mpi_type,root,comm);

    if(recvtype != org_mpich_MPI_OBJECT){
        jni_mpi_rel_buffer(env,recvbuff,c_recv_buff,recvtype,JNI_COMMIT);
    }

    if(sendtype != org_mpich_MPI_OBJECT){
        free(c_send_buff);
    }

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_2DGather
 * Signature: (Ljava/lang/Object;IILjava/lang/Object;IIII)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_12DGather(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jint sendcount, 
    jint sendtype, 
    jobject recvbuff, 
    jint recvcount, 
    jint recvtype, 
    jint root, 
    jint comm)
{
    int result;
    void *c_send_buff;
    void *c_recv_buff;
    int send_mpi_type;
    int recv_mpi_type;
    int sizeRow;
    int ele_count;

    if(sendtype != org_mpich_MPI_OBJECT){
        jni_mpi_get_buffer(env,sendbuff,c_send_buff,
            sendtype,send_mpi_type);
    }
    if(recvtype != org_mpich_MPI_OBJECT){
        int numOfBytes = jni_mpi_sizeof(recvtype);
        ele_count = (*env)->GetArrayLength(env,recvbuff);
        sizeRow = numOfBytes*recvcount;
        c_recv_buff = malloc(sizeRow*ele_count);
        if(c_recv_buff == NULL){
            goto fn_fail;
        }
        jni_mpi_get_buffer(env,NULL,c_recv_buff,recvtype,recv_mpi_type);
    }

    result = MPI_Gather(c_send_buff,sendcount,send_mpi_type,
        c_recv_buff,recvcount,recv_mpi_type,root,comm);
    
    if(sendtype != org_mpich_MPI_OBJECT){
        jni_mpi_rel_buffer(env,sendbuff,c_send_buff,sendtype,JNI_ABORT);
    }
    if(recvtype != org_mpich_MPI_OBJECT){
        for(int i = 0;i < ele_count;i++){
            jarray ele = (*env)->GetObjectArrayElement(env,recvbuff,i);
            void *temp;
            void *ptr = (((jbyte*)c_recv_buff)+(i*sizeRow));

            jni_mpi_get_buffer(env,ele,temp,sendtype,send_mpi_type);
            memcpy(temp,ptr,sizeRow);
            jni_mpi_rel_buffer(env,ele,(void*)temp,sendtype,JNI_COMMIT);
            (*env)->DeleteLocalRef(env,ele);
        }

        free(c_recv_buff);
    }

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Iscatter
 * Signature: (Ljava/lang/Object;IILjava/lang/Object;IIIILorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Iscatter(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jint sendcount, 
    jint sendtype, 
    jobject recvbuff, 
    jint recvcount, 
    jint recvtype, 
    jint root, 
    jint comm, 
    jobject req)
{
    FUNCTION_ISCATGATH(MPI_Iscatter);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Igather
 * Signature: (Ljava/lang/Object;IILjava/lang/Object;IIIILorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Igather(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jint sendcount, 
    jint sendtype, 
    jobject recvbuff, 
    jint recvcount, 
    jint recvtype, 
    jint root, 
    jint comm, 
    jobject req)
{
    FUNCTION_ISCATGATH(MPI_Igather);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Allgather
 * Signature: (Ljava/lang/Object;IILjava/lang/Object;III)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Allgather(
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
    FUNCTION_COLLALL(MPI_Allgather);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Iallgather
 * Signature: (Ljava/lang/Object;IILjava/lang/Object;IIILorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Iallgather(
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
    FUNCTION_ICOLLALL(MPI_Iallgather);
}


/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Scatterv
 * Signature: (Ljava/lang/Object;[I[IILjava/lang/Object;IIII)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Scatterv(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jintArray counts, 
    jintArray disp, 
    jint sendtype, 
    jobject recvbuff, 
    jint recvcount, 
    jint recvtype, 
    jint root, 
    jint comm)
{
    int result;
    void *c_send_buff = NULL;
    void *c_recv_buff = NULL;
    int* sendcounts;
    int* _disp;
    int send_mpi_type;
    int recv_mpi_type;

    if(sendtype != org_mpich_MPI_OBJECT){
        jni_mpi_get_buffer(env,sendbuff,
            c_send_buff,sendtype,send_mpi_type);
    }
    if(recvtype != org_mpich_MPI_OBJECT){
        jni_mpi_get_buffer(env,recvbuff,c_recv_buff,
            recvtype,recv_mpi_type);
    }
    sendcounts = (*env)->GetIntArrayElements(env,counts,NULL);
    _disp = (*env)->GetIntArrayElements(env,disp,NULL);

    result = MPI_Scatterv(c_send_buff,sendcounts,_disp,send_mpi_type,
        c_recv_buff,recvcount,recv_mpi_type,root,comm);
    
    if(sendtype != org_mpich_MPI_OBJECT){
        jni_mpi_rel_buffer(env,sendbuff,c_send_buff,sendtype,JNI_ABORT);
    }
    if(recvtype != org_mpich_MPI_OBJECT){
        jni_mpi_rel_buffer(env,recvbuff,c_recv_buff,recvtype,JNI_COMMIT);
    }
    (*env)->ReleaseIntArrayElements(env,counts,sendcounts,JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env,disp,_disp,JNI_ABORT);
    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Gatherv
 * Signature: (Ljava/lang/Object;IILjava/lang/Object;[I[IIII)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Gatherv(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jint sendcount, 
    jint sendtype, 
    jobject recvbuff, 
    jintArray counts, 
    jintArray disp, 
    jint recvtype, 
    jint root, 
    jint comm)
{
    int result;
    void *c_send_buff = NULL;
    void *c_recv_buff = NULL;
    int* recvcounts;
    int* _disp;
    int send_mpi_type;
    int recv_mpi_type;

    if(sendtype != org_mpich_MPI_OBJECT){
        jni_mpi_get_buffer(env,sendbuff,
            c_send_buff,sendtype,send_mpi_type);
    }
    if(recvtype != org_mpich_MPI_OBJECT){
        jni_mpi_get_buffer(env,recvbuff,c_recv_buff,
            recvtype,recv_mpi_type);
    }
    recvcounts = (*env)->GetIntArrayElements(env,counts,NULL);
    _disp = (*env)->GetIntArrayElements(env,disp,NULL);

    result = MPI_Gatherv(c_send_buff,sendcount,send_mpi_type,
        c_recv_buff,recvcounts,_disp,recv_mpi_type,root,comm);
    
    if(sendtype != org_mpich_MPI_OBJECT){
        jni_mpi_rel_buffer(env,sendbuff,c_send_buff,sendtype,JNI_ABORT);
    }
    if(recvtype != org_mpich_MPI_OBJECT){
        jni_mpi_rel_buffer(env,recvbuff,c_recv_buff,recvtype,JNI_COMMIT);
    }
    (*env)->ReleaseIntArrayElements(env,counts,recvcounts,JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env,disp,_disp,JNI_ABORT);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Iscatterv
 * Signature: (Ljava/lang/Object;[I[IILjava/lang/Object;IIIILorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Iscatterv(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jintArray counts, 
    jintArray disp, 
    jint sendtype, 
    jobject recvbuff, 
    jint recvcount, 
    jint recvtype, 
    jint root, 
    jint comm, 
    jobject req)
{
    int result = 0;
    int send_mpi_type;
    int recv_mpi_type;
    icom_element_t *ele = malloc(sizeof(icom_element_t));
    if(ele == NULL){
        goto fn_fail;
    }
    init_icom_element(ele);
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
    // counts
    ele->counts_object = (*env)->NewGlobalRef(env,counts);
    ele->counts_buff = (*env)->GetIntArrayElements(env,
        ele->counts_object,NULL);
    // disp
    ele->disp_object = (*env)->NewGlobalRef(env,disp);
    ele->disp_buff = (*env)->GetIntArrayElements(env,
        ele->disp_object,NULL);
    OPA_Queue_enqueue(&JNI_MPI_QHEAD_IRECV,
        ele,icom_element_t,hdr);
    result = MPI_Iscatterv(ele->c_sendbuff,ele->counts_buff,ele->disp_buff,send_mpi_type,
        ele->buff,recvcount,recv_mpi_type,root,comm,&ele->req);
     (*env)->SetIntField(env,req,JNI_MPI_REQUEST_HANDLER,
        ele->req);
    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_TYPE,
        JNI_MPI_REQUEST_TYPE_RECV);
    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Igatherv
 * Signature: (Ljava/lang/Object;IILjava/lang/Object;[I[IIIILorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Igatherv
  (JNIEnv *env, 
  jclass class, 
  jobject sendbuff, 
  jint sendcount, 
  jint sendtype, 
  jobject recvbuff, 
  jintArray counts, 
  jintArray disp, 
  jint recvtype, 
  jint root, 
  jint comm, 
  jobject req)
{
    int result = 0;
    int send_mpi_type;
    int recv_mpi_type;
    icom_element_t *ele = malloc(sizeof(icom_element_t));
    if(ele == NULL){
        goto fn_fail;
    }
    init_icom_element(ele);
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
    // counts
    ele->counts_object = (*env)->NewGlobalRef(env,counts);
    ele->counts_buff = (*env)->GetIntArrayElements(env,
        ele->counts_object,NULL);
    // disp
    ele->disp_object = (*env)->NewGlobalRef(env,disp);
    ele->disp_buff = (*env)->GetIntArrayElements(env,
        ele->disp_object,NULL);
    OPA_Queue_enqueue(&JNI_MPI_QHEAD_IRECV,
        ele,icom_element_t,hdr);
    result = MPI_Igatherv(ele->c_sendbuff,sendcount,send_mpi_type,
        ele->buff,ele->counts_buff,ele->disp_buff,recv_mpi_type,root,comm,&ele->req);
     (*env)->SetIntField(env,req,JNI_MPI_REQUEST_HANDLER,
        ele->req);
    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_TYPE,
        JNI_MPI_REQUEST_TYPE_RECV);
    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Allgatherv
 * Signature: (Ljava/lang/Object;IILjava/lang/Object;[I[III)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Allgatherv(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jint sendcount, 
    jint sendtype, 
    jobject recvbuff, 
    jintArray counts, 
    jintArray disp, 
    jint recvtype, 
    jint comm)
{
    int result;
    void *c_send_buff = NULL;
    void *c_recv_buff = NULL;
    int* recvcounts;
    int* _disp;
    int send_mpi_type;
    int recv_mpi_type;

    if(sendtype != org_mpich_MPI_OBJECT){
        jni_mpi_get_buffer(env,sendbuff,
            c_send_buff,sendtype,send_mpi_type);
    }
    if(recvtype != org_mpich_MPI_OBJECT){
        jni_mpi_get_buffer(env,recvbuff,c_recv_buff,
            recvtype,recv_mpi_type);
    }
    recvcounts = (*env)->GetIntArrayElements(env,counts,NULL);
    _disp = (*env)->GetIntArrayElements(env,disp,NULL);

    result = MPI_Allgatherv(c_send_buff,sendcount,send_mpi_type,
        c_recv_buff,recvcounts,_disp,recv_mpi_type,comm);
    
    if(sendtype != org_mpich_MPI_OBJECT){
        jni_mpi_rel_buffer(env,sendbuff,c_send_buff,sendtype,JNI_ABORT);
    }
    if(recvtype != org_mpich_MPI_OBJECT){
        jni_mpi_rel_buffer(env,recvbuff,c_recv_buff,recvtype,JNI_COMMIT);
    }
    (*env)->ReleaseIntArrayElements(env,counts,recvcounts,JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env,disp,_disp,JNI_ABORT);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Iallgatherv
 * Signature: (Ljava/lang/Object;IILjava/lang/Object;[I[IIILorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Iallgatherv(
    JNIEnv *env, 
    jclass class, 
    jobject sendbuff, 
    jint sendcount, 
    jint sendtype, 
    jobject recvbuff, 
    jintArray counts, 
    jintArray disp, 
    jint recvtype, 
    jint comm, 
    jobject req)
{
    int result = 0;
    int send_mpi_type;
    int recv_mpi_type;
    icom_element_t *ele = malloc(sizeof(icom_element_t));
    if(ele == NULL){
        goto fn_fail;
    }
    init_icom_element(ele);
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
    // counts
    ele->counts_object = (*env)->NewGlobalRef(env,counts);
    ele->counts_buff = (*env)->GetIntArrayElements(env,
        ele->counts_object,NULL);
    // disp
    ele->disp_object = (*env)->NewGlobalRef(env,disp);
    ele->disp_buff = (*env)->GetIntArrayElements(env,
        ele->disp_object,NULL);
    OPA_Queue_enqueue(&JNI_MPI_QHEAD_IRECV,
        ele,icom_element_t,hdr);
    result = MPI_Iallgatherv(ele->c_sendbuff,sendcount,send_mpi_type,
        ele->buff,ele->counts_buff,ele->disp_buff,recv_mpi_type,comm,&ele->req);
     (*env)->SetIntField(env,req,JNI_MPI_REQUEST_HANDLER,
        ele->req);
    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_TYPE,
        JNI_MPI_REQUEST_TYPE_RECV);
    JNI_MPI_RETURN(result);
}


