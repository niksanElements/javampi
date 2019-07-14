#ifndef JNI_MPI_C_COLLECTIVE
#define JNI_MPI_C_COLLECTIVE

#include "jni_mpi.h"
#include "jni_mpi_exception.h"

#include <malloc.h>

#define FUNCTION_SCATTGATH(operation)\
    int result;\
    void *c_send_buff = NULL;\
    void *c_recv_buff = NULL;\
    int send_mpi_type;\
    int recv_mpi_type;\
    if(sendtype != org_mpich_MPI_OBJECT){\
        jni_mpi_get_buffer(env,sendbuff,\
            c_send_buff,sendtype,send_mpi_type);\
    }\
    if(recvtype != org_mpich_MPI_OBJECT){\
        jni_mpi_get_buffer(env,recvbuff,c_recv_buff,\
            recvtype,recv_mpi_type);\
    }\
    result = operation(c_send_buff,sendcount,send_mpi_type,\
        c_recv_buff,recvcount,recv_mpi_type,root,comm);\
    \
    if(sendtype != org_mpich_MPI_OBJECT){\
        jni_mpi_rel_buffer(env,sendbuff,c_send_buff,sendtype,JNI_ABORT);\
    }\
    if(recvtype != org_mpich_MPI_OBJECT){\
        jni_mpi_rel_buffer(env,recvbuff,c_recv_buff,recvtype,JNI_COMMIT);\
    }\
    JNI_MPI_RETURN(result);

#define FUNCTION_ISCATGATH(operation)\
    int result = 0;\
    int send_mpi_type;\
    int recv_mpi_type;\
    icom_element_t *ele = malloc(sizeof(icom_element_t));\
    if(ele == NULL){\
        goto fn_fail;\
    }\
    init_icom_element(ele);\
    if(sendtype != org_mpich_MPI_OBJECT){\
        ele->sendbuff = (*env)->NewGlobalRef(env,sendbuff);\
        ele->sendtype = sendtype;\
        jni_mpi_get_buffer(env,ele->sendbuff,\
            ele->c_sendbuff,sendtype,send_mpi_type);\
    }\
    if(recvtype != org_mpich_MPI_OBJECT){\
        ele->glob_array_ref = (*env)->NewGlobalRef(env,recvbuff);\
        ele->datatype = recvtype;\
        jni_mpi_get_buffer(env,ele->glob_array_ref,\
            ele->buff,recvtype,recv_mpi_type);\
    }\
    OPA_Queue_enqueue(&JNI_MPI_QHEAD_IRECV,\
        ele,icom_element_t,hdr);\
    result = operation(ele->c_sendbuff,sendcount,send_mpi_type,\
        ele->buff,recvcount,recv_mpi_type,root,comm,&ele->req);\
     (*env)->SetIntField(env,req,JNI_MPI_REQUEST_HANDLER,\
        ele->req);\
    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_TYPE,\
        JNI_MPI_REQUEST_TYPE_RECV);\
    JNI_MPI_RETURN(result);

#define FUNCTION_COLLALL(operation)\
    int result;\
    void *c_send_buff = NULL;\
    void *c_recv_buff = NULL;\
    int send_mpi_type;\
    int recv_mpi_type;\
    if(sendtype != org_mpich_MPI_OBJECT){\
        jni_mpi_get_buffer(env,sendbuff,\
            c_send_buff,sendtype,send_mpi_type);\
    }\
    if(recvtype != org_mpich_MPI_OBJECT){\
        jni_mpi_get_buffer(env,recvbuff,c_recv_buff,\
            recvtype,recv_mpi_type);\
    }\
    result = operation(c_send_buff,sendcount,send_mpi_type,\
        c_recv_buff,recvcount,recv_mpi_type,comm);\
    \
    if(sendtype != org_mpich_MPI_OBJECT){\
        jni_mpi_rel_buffer(env,sendbuff,c_send_buff,sendtype,JNI_ABORT);\
    }\
    if(recvtype != org_mpich_MPI_OBJECT){\
        jni_mpi_rel_buffer(env,recvbuff,c_recv_buff,recvtype,JNI_COMMIT);\
    }\
    JNI_MPI_RETURN(result);

#define FUNCTION_ICOLLALL(operation)\
    int result = 0;\
    int send_mpi_type;\
    int recv_mpi_type;\
    icom_element_t *ele = malloc(sizeof(icom_element_t));\
    if(ele == NULL){\
        goto fn_fail;\
    }\
    init_icom_element(ele);\
    if(sendtype != org_mpich_MPI_OBJECT){\
        ele->sendbuff = (*env)->NewGlobalRef(env,sendbuff);\
        ele->sendtype = sendtype;\
        jni_mpi_get_buffer(env,ele->sendbuff,\
            ele->c_sendbuff,sendtype,send_mpi_type);\
    }\
    if(recvtype != org_mpich_MPI_OBJECT){\
        ele->glob_array_ref = (*env)->NewGlobalRef(env,recvbuff);\
        ele->datatype = recvtype;\
        jni_mpi_get_buffer(env,ele->glob_array_ref,\
            ele->buff,recvtype,recv_mpi_type);\
    }\
    OPA_Queue_enqueue(&JNI_MPI_QHEAD_IRECV,\
        ele,icom_element_t,hdr);\
    result = MPI_Iallgather(ele->c_sendbuff,sendcount,send_mpi_type,\
        ele->buff,recvcount,recv_mpi_type,comm,&ele->req);\
     (*env)->SetIntField(env,req,JNI_MPI_REQUEST_HANDLER,\
        ele->req);\
    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_TYPE,\
        JNI_MPI_REQUEST_TYPE_RECV);\
    JNI_MPI_RETURN(result);\

#define FUNCTION_REDBLOCK_SCAN(operation)\
    int result;\
    int mpi_type;\
    void *c_send_buf;\
    void *c_recv_buf;\
    if(type != org_mpich_MPI_OBJECT){\
        jni_mpi_get_buffer(env,sendbuff,c_send_buf,type,mpi_type);\
        jni_mpi_get_buffer(env,recvbuff,c_recv_buf,type,mpi_type);\
    }\
    result = operation(\
        c_send_buf,c_recv_buf,count,mpi_type,op,comm);\
    if(type != org_mpich_MPI_OBJECT){\
        jni_mpi_rel_buffer(env,sendbuff,c_send_buf,type,JNI_ABORT);\
        jni_mpi_rel_buffer(env,recvbuff,c_recv_buf,type,JNI_COMMIT);\
    }\
    JNI_MPI_RETURN(result);

#define FUNCTION_IREDBLOCK_SCAN(operation)\
    int result;\
    int mpi_type;\
    icom_element_t* ele = malloc(sizeof(icom_element_t));\
    if(ele == NULL){\
        goto fn_fail;\
    }\
    init_icom_element(ele);\
    if(type != org_mpich_MPI_OBJECT){\
        ele->sendbuff = (*env)->NewGlobalRef(env,sendbuff);\
        ele->glob_array_ref = (*env)->NewGlobalRef(env,recvbuff);\
        ele->datatype = type;\
        ele->sendtype = type;\
        jni_mpi_get_buffer(env,ele->sendbuff,\
            ele->c_sendbuff,type,mpi_type);\
        jni_mpi_get_buffer(env,ele->glob_array_ref,\
            ele->buff,type,mpi_type);\
    }\
    OPA_Queue_enqueue(&JNI_MPI_QHEAD_IRECV,\
        ele,icom_element_t,hdr);\
    result = operation(ele->c_sendbuff,ele->buff,\
        count,mpi_type,op,comm,&ele->req);\
\
    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_HANDLER,\
        ele->req);\
    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_TYPE,\
        JNI_MPI_REQUEST_TYPE_RECV);\
    JNI_MPI_RETURN(result);

#endif // JNI_MPI_C_COLLECTIVE