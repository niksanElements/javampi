#include "jni_mpi.h"
#include "jni_mpi_exception.h"

#include <malloc.h>

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Recv
 * Signature: (Ljava/lang/Object;IIIILorg/mpich/MPI_Status;)I
 */
JNIEXPORT jint JNICALL Java_org_mpich_MPI_MPI_1Recv(
    JNIEnv *env, 
    jclass class, 
    jobject buff, 
    jint type, 
    jint source, 
    jint tag, 
    jint comm, 
    jobject status)
{
    int result = 0;

    int count;                                      
    void* c_buff = NULL;                            
    MPI_Status s;  
    int mpi_type;      
                                
    if(type != org_mpich_MPI_OBJECT){
        count = (*env)->GetArrayLength(env,buff); 
        jni_mpi_get_buffer(env,buff,c_buff,type,mpi_type); 
    }  
    else{
        jni_mpi_get_obj_addr(env,buff,c_buff,count,type,mpi_type,JNI_FALSE);
    }                                

    if(status == NULL){                                                                 
        result = MPI_Recv(c_buff,count,mpi_type,source,tag,comm,MPI_STATUS_IGNORE);     
    }                                                                                   
    else{                                                                               
        result = MPI_Recv(c_buff,count,mpi_type,source,tag,comm,&s);                    
        jni_mpi_convert_MPI_Status(env,status,&s,FROM_MPI_STATUS_TO_JAVA_MPI_STATUS);   
    }         

    if(type != org_mpich_MPI_OBJECT){
        jni_mpi_rel_buffer(env,buff,c_buff,type,JNI_COMMIT); 
    }
    else{
        (*env)->CallVoidMethod(env,buff,JNI_MPI_SERIALIZABLE_SET);
    }                                                                         

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Irecv
 * Signature: (Ljava/lang/Object;IIIILorg/mpich/MPI_Status;Ljava/lang/Integer;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Irecv(
    JNIEnv *env, 
    jclass class, 
    jobject buff, 
    jint type, 
    jint source, 
    jint tag, 
    jint comm, 
    jobject req)
{
    int result = 0;

    icom_element_t *element;
    int mpi_type;
    int count;

    element = malloc(sizeof(icom_element_t));
    if(element == NULL){
        goto fn_fail;
    }
    init_icom_element(element);
    element->datatype = type;  
    if(type != org_mpich_MPI_OBJECT){                         
        element->glob_array_ref = (*env)->NewGlobalRef(env,buff);        
        jni_mpi_get_buffer(env,element->glob_array_ref,
            element->buff,type,mpi_type);
        count =                                                         
            (*env)->GetArrayLength(env,element->glob_array_ref);  
    }
    else{
        jni_mpi_gobj_addr(env,buff,element->glob_array_ref,
            element->buff,count,type,mpi_type,JNI_FALSE);
    }
                            
    OPA_Queue_enqueue(&JNI_MPI_QHEAD_IRECV,element,icom_element_t,hdr);    
          
    result = MPI_Irecv(element->buff,count,                              
        mpi_type,source,tag,comm,&element->req);

    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_HANDLER,
        element->req);                          
    (*env)->SetIntField(env,req,JNI_MPI_REQUEST_TYPE,               
        JNI_MPI_REQUEST_TYPE_RECV);                              

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_MRecv
 * Signature: (Ljava/lang/Object;ILorg/mpich/MPI_Message;Lorg/mpich/MPI_Status;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Mrecv(
    JNIEnv *env, 
    jclass class, 
    jobject buffer, 
    jint type, 
    jobject message, 
    jobject status)
{
    int result;
    MPI_Message msg = (*env)->GetIntField(env,message,JNI_MPI_MESSAGE_HANDLER);
    MPI_Status stat;
    int count;
    void *buff = (*env)->GetByteArrayElements(env,buffer,NULL);
    int mpi_type;
    if(type != org_mpich_MPI_OBJECT){
        count = (*env)->GetArrayLength(env,buffer);
        jni_mpi_get_buffer(env,buffer,buff,type,mpi_type);
    }
    else{
        jni_mpi_get_obj_addr(env,buffer,buff,count,type,mpi_type,JNI_FALSE);
    }

    result = MPI_Mrecv(buff,count,mpi_type,&msg,&stat);
    jni_mpi_convert_MPI_Status(env,status,&stat,
        FROM_MPI_STATUS_TO_JAVA_MPI_STATUS);

    (*env)->SetIntField(env,message,JNI_MPI_MESSAGE_HANDLER,msg);

    jni_mpi_rel_buffer(env,buffer,buff,type,JNI_COMMIT);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Imrecv
 * Signature: (Ljava/lang/Object;ILorg/mpich/MPI_Message;Lorg/mpich/MPI_Request;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Imrecv(
    JNIEnv *env, 
    jclass class, 
    jobject buffer, 
    jint datatype, 
    jobject message, 
    jobject request)
{
    int result = 0;

    icom_element_t *element;    
    MPI_Message msg;
    int count;
    int mpi_type;

    element = malloc(sizeof(icom_element_t));
    if(element == NULL){
        goto fn_fail;
    }
    init_icom_element(element);
    element->datatype = datatype;  
    if(datatype != org_mpich_MPI_OBJECT){                                                               
        element->glob_array_ref = (*env)->NewGlobalRef(env,buffer);      
        jni_mpi_get_buffer(env,element->glob_array_ref,
            element->buff,datatype,mpi_type);
        count = (*env)->GetArrayLength(env,element->glob_array_ref); 
    }
    else{
        jni_mpi_gobj_addr(env,buffer,element->glob_array_ref,
            element->buff,count,datatype,mpi_type,JNI_FALSE);
    }
    msg = (*env)->GetIntField(env,message,JNI_MPI_MESSAGE_HANDLER);   

    result = MPI_Imrecv(element->buff,count,mpi_type,
        &msg,&element->req); 
                         
    OPA_Queue_enqueue(&JNI_MPI_QHEAD_IRECV,element,icom_element_t,hdr); 

    (*env)->SetIntField(env,message,JNI_MPI_MESSAGE_HANDLER,msg);                        
    (*env)->SetIntField(env,request,JNI_MPI_REQUEST_HANDLER,element->req);                          
    (*env)->SetIntField(env,request,JNI_MPI_REQUEST_TYPE,JNI_MPI_REQUEST_TYPE_RECV);                              

    JNI_MPI_RETURN(result);
}
