#include "jni_mpi.h"
#include "jni_mpi_exception.h"

#include <malloc.h>

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Send
 * Signature: (Ljava/lang/Object;IIII)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Send(
    JNIEnv *env, 
    jclass class, 
    jobject buff, 
    jint type, 
    jint dest, 
    jint tag, 
    jint comm)
{
    int result = 0;
    void *c_buff;
    int count;
    int mpi_type;

    if(type != org_mpich_MPI_OBJECT){
        count = (*env)->GetArrayLength(env,buff);
        jni_mpi_get_buffer(env,buff,c_buff,type,mpi_type);
    }
    else{
        jni_mpi_get_obj_addr(env,buff,c_buff,count,type,mpi_type,JNI_TRUE);
    }

    result = MPI_Send(c_buff,count,mpi_type,dest,tag,comm);

    if(type != org_mpich_MPI_OBJECT){
        jni_mpi_rel_buffer(env,buff,c_buff,type,JNI_ABORT);
    }

    JNI_MPI_RETURN(result);
}


/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Bsend
 * Signature: (Ljava/lang/Object;IIII)I
 */
JNIEXPORT jint JNICALL Java_org_mpich_MPI_MPI_1Bsend(
    JNIEnv *env, 
    jclass class, 
    jobject buff, 
    jint type, 
    jint dest, 
    jint tag, 
    jint comm)
{
    int result = 0;
    void *c_buff;
    int count;
    int mpi_type;

    if(type != org_mpich_MPI_OBJECT){
        count = (*env)->GetArrayLength(env,buff);
        jni_mpi_get_buffer(env,buff,c_buff,type,mpi_type);
    }
    else{
        jni_mpi_get_obj_addr(env,buff,c_buff,count,type,mpi_type,JNI_TRUE);
    }
    
    result = MPI_Bsend(c_buff,count,mpi_type,dest,tag,comm);

    if(type != org_mpich_MPI_OBJECT){
        jni_mpi_rel_buffer(env,buff,c_buff,type,JNI_ABORT);
    }

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Ssend
 * Signature: (Ljava/lang/Object;IIII)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Ssend(
    JNIEnv *env, 
    jclass class, 
    jobject buff, 
    jint type, 
    jint dest, 
    jint tag, 
    jint comm)
{
    int result = 0;
    void *c_buff;
    int count;
    int mpi_type;

    if(type != org_mpich_MPI_OBJECT){
        count = (*env)->GetArrayLength(env,buff);
        jni_mpi_get_buffer(env,buff,c_buff,type,mpi_type);
    }
    else{
        jni_mpi_get_obj_addr(env,buff,c_buff,count,type,mpi_type,JNI_TRUE);
    }
    
    result = MPI_Ssend(c_buff,count,mpi_type,dest,tag,comm);

    if(type != org_mpich_MPI_OBJECT){
        jni_mpi_rel_buffer(env,buff,c_buff,type,JNI_ABORT);
    }

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Rsend
 * Signature: (Ljava/lang/Object;IIII)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Rsend(
    JNIEnv *env, 
    jclass class, 
    jobject buff, 
    jint type, 
    jint dest, 
    jint tag, 
    jint comm)
{
    int result = 0;
    void *c_buff;
    int count;
    int mpi_type;

    if(type != org_mpich_MPI_OBJECT){
        count = (*env)->GetArrayLength(env,buff);
        jni_mpi_get_buffer(env,buff,c_buff,type,mpi_type);
    }
    else{
        jni_mpi_get_obj_addr(env,buff,c_buff,count,type,mpi_type,JNI_TRUE);
    }
    
    result = MPI_Rsend(c_buff,count,mpi_type,dest,tag,comm);

    if(type != org_mpich_MPI_OBJECT){
        jni_mpi_rel_buffer(env,buff,c_buff,type,JNI_ABORT);
    }

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Isend
 * Signature: (Ljava/lang/Object;IIII)I
 */
JNIEXPORT jint JNICALL Java_org_mpich_MPI_MPI_1Isend(
    JNIEnv *env, 
    jclass class, 
    jobject buff, 
    jint datatype, 
    jint dest, 
    jint tag, 
    jint comm,
    jobject req)
{
    int result;
    icom_element_t *element;
    int mpi_type;
    int count;

    element = malloc(sizeof(icom_element_t));
    if(element == NULL){
        goto fn_fail;
    }
    init_icom_element(element);
    element->datatype = datatype;
    if(datatype != org_mpich_MPI_OBJECT){
        element->glob_array_ref = (*env)->NewGlobalRef(env,buff);
        jni_mpi_get_buffer(env,element->glob_array_ref,
        element->buff, datatype,mpi_type);
        count = (*env)->GetArrayLength(env,element->glob_array_ref);
    }
    else{
        jni_mpi_gobj_addr(env,buff,element->glob_array_ref,
            element->buff,count,datatype,mpi_type,JNI_TRUE);
    }

    OPA_Queue_enqueue(&JNI_MPI_QHEAD_ISEND,
        element,icom_element_t,hdr);

    result = MPI_Isend(element->buff,count,
        mpi_type,dest,tag,comm,&element->req);

    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_HANDLER,
        element->req);
    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_TYPE,
        JNI_MPI_REQUEST_TYPE_SEND);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Ibsend
 * Signature: (Ljava/lang/Object;IIII)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Ibsend(
    JNIEnv *env, 
    jclass class, 
    jobject buff, 
    jint datatype, 
    jint dest, 
    jint tag, 
    jint comm,
    jobject req)
{
int result;
    icom_element_t *element;
    int mpi_type;
    int count;

    element = malloc(sizeof(icom_element_t));
    if(element == NULL){
        goto fn_fail;
    }
    init_icom_element(element);
    element->datatype = datatype;
    if(datatype != org_mpich_MPI_OBJECT){
        element->glob_array_ref = (*env)->NewGlobalRef(env,buff);
        jni_mpi_get_buffer(env,element->glob_array_ref,
        element->buff, datatype,mpi_type);
        count = (*env)->GetArrayLength(env,element->glob_array_ref);
    }
    else{
        jni_mpi_gobj_addr(env,buff,element->glob_array_ref,
            element->buff,count,datatype,mpi_type,JNI_TRUE);
    }

    OPA_Queue_enqueue(&JNI_MPI_QHEAD_ISEND,
        element,icom_element_t,hdr);

    result = MPI_Ibsend(element->buff,count,
        mpi_type,dest,tag,comm,&element->req);

    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_HANDLER,
        element->req);
    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_TYPE,
        JNI_MPI_REQUEST_TYPE_SEND);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Issend
 * Signature: (Ljava/lang/Object;IIII)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Issend(
    JNIEnv *env, 
    jclass class, 
    jobject buff, 
    jint datatype, 
    jint dest, 
    jint tag, 
    jint comm,
    jobject req)
{
int result;
    icom_element_t *element;
    int mpi_type;
    int count;

    element = malloc(sizeof(icom_element_t));
    if(element == NULL){
        goto fn_fail;
    }
    init_icom_element(element);
    element->datatype = datatype;
    if(datatype != org_mpich_MPI_OBJECT){
        element->glob_array_ref = (*env)->NewGlobalRef(env,buff);
        jni_mpi_get_buffer(env,element->glob_array_ref,
        element->buff, datatype,mpi_type);
        count = (*env)->GetArrayLength(env,element->glob_array_ref);
    }
    else{
        jni_mpi_gobj_addr(env,buff,element->glob_array_ref,
            element->buff,count,datatype,mpi_type,JNI_TRUE);
    }

    OPA_Queue_enqueue(&JNI_MPI_QHEAD_ISEND,
        element,icom_element_t,hdr);

    result = MPI_Issend(element->buff,count,
        mpi_type,dest,tag,comm,&element->req);

    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_HANDLER,
        element->req);
    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_TYPE,
        JNI_MPI_REQUEST_TYPE_SEND);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Irsend
 * Signature: (Ljava/lang/Object;IIII)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Irsend(
    JNIEnv *env, 
    jclass class, 
    jobject buff, 
    jint datatype, 
    jint dest, 
    jint tag, 
    jint comm,
    jobject req)
{
int result;
    icom_element_t *element;
    int mpi_type;
    int count;

    element = malloc(sizeof(icom_element_t));
    if(element == NULL){
        goto fn_fail;
    }
    init_icom_element(element);
    element->datatype = datatype;
    if(datatype != org_mpich_MPI_OBJECT){
        element->glob_array_ref = (*env)->NewGlobalRef(env,buff);
        jni_mpi_get_buffer(env,element->glob_array_ref,
        element->buff, datatype,mpi_type);
        count = (*env)->GetArrayLength(env,element->glob_array_ref);
    }
    else{
        jni_mpi_gobj_addr(env,buff,element->glob_array_ref,
            element->buff,count,datatype,mpi_type,JNI_TRUE);
    }

    OPA_Queue_enqueue(&JNI_MPI_QHEAD_ISEND,
        element,icom_element_t,hdr);

    result = MPI_Irsend(element->buff,count,
        mpi_type,dest,tag,comm,&element->req);

    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_HANDLER,
        element->req);
    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_TYPE,
        JNI_MPI_REQUEST_TYPE_SEND);

    JNI_MPI_RETURN(result);
}
