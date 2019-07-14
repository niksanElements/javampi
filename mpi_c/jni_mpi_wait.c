#include "jni_mpi.h"
#include "jni_mpi_exception.h"

#include "malloc.h"

// TODO: Exception handaling for the check functions (non blocking communication)!

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Wait
 * Signature: (Lorg/mpich/MPI_Request;Lorg/mpich/MPI_Status;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Wait(
    JNIEnv *env, 
    jclass class, 
    jobject request, 
    jobject status)
{
    MPI_Status stat;
    MPI_Request req;
    int result;
    int req_type;
    MPI_Request req_copy;

    req = (*env)->GetIntField(env,request,JNI_MPI_REQUEST_HANDLER);
    req_type = (*env)->GetIntField(env,request,JNI_MPI_REQUEST_TYPE);
    req_copy = req;
    if(status == NULL){
        result = MPI_Wait(&req,MPI_STATUS_IGNORE);
    }
    else{
        result = MPI_Wait(&req,&stat);
        jni_mpi_convert_MPI_Status(env,status,&stat,FROM_MPI_STATUS_TO_JAVA_MPI_STATUS);
    }
    
    // delete the global referece
    if(req_type == JNI_MPI_REQUEST_TYPE_RECV){
        release_icom_element(env,&JNI_MPI_QHEAD_IRECV,&req_copy,JNI_COMMIT);
    }  
    else if(req_type == JNI_MPI_REQUEST_TYPE_SEND){
        release_icom_element(env,&JNI_MPI_QHEAD_ISEND,&req_copy,JNI_ABORT);
    }
    
    (*env)->SetIntField(env,request,JNI_MPI_REQUEST_HANDLER,req);

    JNI_MPI_RETURN(result);
}


/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Test
 * Signature: (Lorg/mpich/MPI_Request;Lorg/mpich/MPI_Status;)I
 */
JNIEXPORT jboolean JNICALL 
Java_org_mpich_MPI_MPI_1Test(
    JNIEnv *env, 
    jclass clss, 
    jobject request, 
    jobject status)
{
    MPI_Request req;
    MPI_Request req_copy;
    MPI_Status stat;
    int result = -1;
    int flag;

    req = (*env)->GetIntField(env,request,JNI_MPI_REQUEST_HANDLER);
    req_copy = req;
    if(status == NULL){
        result = MPI_Test(&req,&flag,MPI_STATUS_IGNORE);
    }
    else{
        result = MPI_Test(&req,&flag,&stat);
        // populate the result
        jni_mpi_convert_MPI_Status(env,status,&stat,FROM_MPI_STATUS_TO_JAVA_MPI_STATUS);
    }
    // release the reference if it's ready
    if(flag == 1){
        int type = (*env)->GetIntField(env,request,JNI_MPI_REQUEST_TYPE);
        if(type == JNI_MPI_REQUEST_TYPE_SEND){
            release_icom_element(env,&JNI_MPI_QHEAD_ISEND,&req_copy,JNI_ABORT);
        }
        else if(type = JNI_MPI_REQUEST_TYPE_RECV){
            release_icom_element(env,&JNI_MPI_QHEAD_IRECV,&req_copy,JNI_COMMIT);
        }
        (*env)->SetIntField(env,request,JNI_MPI_REQUEST_HANDLER,(jint)req);
    }

    fn_exit:
        if(result != MPI_SUCCESS){
            jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
        }
        if(flag == 1)
            return JNI_TRUE;
        else
            return JNI_FALSE;
    fn_fail:
        return -1;
}
/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Waitany
 * Signature: ([Lorg/mpich/MPI_Request;Lorg/mpich/MPI_Status;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Waitany(
    JNIEnv *env, 
    jclass class, 
    jobjectArray requests, 
    jobject status)
{
    int count = (*env)->GetArrayLength(env,requests);
    int result;
    int index = 0;
    MPI_Status stat;
    
    MPI_Request *req_vec = malloc(sizeof(MPI_Request)*count);
    MPI_Request *req_buff_vec = malloc(sizeof(MPI_Request)*count);
    jobject *req_cache = malloc(sizeof(jobject)*count);
    int *req_type = malloc(sizeof(int)*count);

    if (req_vec == NULL || req_buff_vec == NULL ||
            req_cache == NULL || req_type == NULL) {
        goto fn_fail;
    }
    
    // for each request object
    for(int i = 0;i < count;i++){
        req_cache[i] = (*env)->GetObjectArrayElement(env,requests,i);
        req_vec[i] = (*env)->GetIntField(env,req_cache[i],
            JNI_MPI_REQUEST_HANDLER);
        req_buff_vec[i] = req_vec[i];
        req_type[i] = (*env)->GetIntField(env,req_cache[i],JNI_MPI_REQUEST_TYPE);
    }

    if(status == NULL){
        result = MPI_Waitany(count,req_vec,&index,MPI_STATUS_IGNORE);
    }
    else{
        result = MPI_Waitany(count,req_vec,&index,&stat);
        jni_mpi_convert_MPI_Status(env,
            status,&stat,
            FROM_MPI_STATUS_TO_JAVA_MPI_STATUS);
    }

    // delete the global referece
    if(req_type[index] == JNI_MPI_REQUEST_TYPE_RECV){
        release_icom_element(env,&JNI_MPI_QHEAD_IRECV,&req_buff_vec[index],JNI_COMMIT);
    }  
    else if(req_type[index] == JNI_MPI_REQUEST_TYPE_SEND){
        release_icom_element(env,&JNI_MPI_QHEAD_ISEND,&req_buff_vec[index],JNI_ABORT);
    }
    
    (*env)->SetIntField(env,req_cache[index],JNI_MPI_REQUEST_HANDLER,req_vec[index]);

    for(int i = 0;i < count;i++){
        (*env)->DeleteLocalRef(env,req_cache[i]);
    }
    // free all buffers
    free(req_cache);
    free(req_vec);
    free(req_buff_vec);
    free(req_type);

    fn_exit:
        if(result != MPI_SUCCESS){
            jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
        }
        return index;
    fn_fail:
        return -1;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Testany
 * Signature: ([Lorg/mpich/MPI_Request;Lorg/mpich/MPI_Status;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Testany(
    JNIEnv *env, 
    jclass class, 
    jobjectArray requests, 
    jobject status)
{
        int count = (*env)->GetArrayLength(env,requests);
    int result;
    int index = 0;
    int flag;
    MPI_Status stat;
    
    MPI_Request *req_vec = malloc(sizeof(MPI_Request)*count);
    MPI_Request *req_buff_vec = malloc(sizeof(MPI_Request)*count);
    jobject *req_cache = malloc(sizeof(jobject)*count);
    int *req_type = malloc(sizeof(int)*count);

    if (req_vec == NULL || req_buff_vec == NULL ||
            req_cache == NULL || req_type == NULL) {
        goto fn_fail;
    }
    
    // for each request object
    for(int i = 0;i < count;i++){
        req_cache[i] = (*env)->GetObjectArrayElement(env,requests,i);
        req_vec[i] = (*env)->GetIntField(env,req_cache[i],
            JNI_MPI_REQUEST_HANDLER);
        req_buff_vec[i] = req_vec[i];
        req_type[i] = (*env)->GetIntField(env,req_cache[i],JNI_MPI_REQUEST_TYPE);
    }

    if(status == NULL){
        result = MPI_Testany(count,req_vec,&index,&flag,MPI_STATUS_IGNORE);
    }
    else{
        result = MPI_Testany(count,req_vec,&index,&flag,&stat);
        jni_mpi_convert_MPI_Status(env,status,&stat,
            FROM_MPI_STATUS_TO_JAVA_MPI_STATUS);
    }

    if(index != MPI_UNDEFINED && flag == 1){
        // delete the global referece
        if(req_type[index] == JNI_MPI_REQUEST_TYPE_RECV){
            release_icom_element(env,&JNI_MPI_QHEAD_IRECV,&req_buff_vec[index],JNI_COMMIT);
        }  
        else if(req_type[index] == JNI_MPI_REQUEST_TYPE_SEND){
            release_icom_element(env,&JNI_MPI_QHEAD_ISEND,&req_buff_vec[index],JNI_ABORT);
        }
        
        (*env)->SetIntField(env,req_cache[index],JNI_MPI_REQUEST_HANDLER,req_vec[index]);
    }

    for(int i = 0;i < count;i++){
        (*env)->DeleteLocalRef(env,req_cache[i]);
    }
    // free all buffers
    free(req_cache);
    free(req_vec);
    free(req_buff_vec);
    free(req_type);

    fn_exit:
        if(result != MPI_SUCCESS){
            jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
        }
        return index;
    fn_fail:
        return -1;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Waitall
 * Signature: ([Lorg/mpich/MPI_Request;[Lorg/mpich/MPI_Status;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Waitall(
    JNIEnv *env, 
    jclass class, 
    jobjectArray requests, 
    jobjectArray statuses)
{
    int count = (*env)->GetArrayLength(env,requests);
    int result = 0;

    MPI_Request *req_vec = malloc(sizeof(MPI_Request)*count);
    MPI_Request *req_buff_vec = malloc(sizeof(MPI_Request)*count);
    jobject *req_cache = malloc(sizeof(jobject)*count);
    int *req_type = malloc(sizeof(int)*count);

    if (req_vec == NULL || req_buff_vec == NULL ||
            req_cache == NULL || req_type == NULL) {
        goto fn_fail;
    }

     // for each request object
    for(int i = 0;i < count;i++){
        req_cache[i] = (*env)->GetObjectArrayElement(env,requests,i);
        req_vec[i] = (*env)->GetIntField(env,req_cache[i],
            JNI_MPI_REQUEST_HANDLER);
        req_buff_vec[i] = req_vec[i];
        req_type[i] = (*env)->GetIntField(env,req_cache[i],JNI_MPI_REQUEST_TYPE);
    }

    if(statuses == NULL){
        result = MPI_Waitall(count,req_vec,MPI_STATUSES_IGNORE);
    }
    else {
        MPI_Status *stat = malloc(sizeof(MPI_Status)*count);
        result = MPI_Waitall(count,req_vec,stat);
        // set all statuses
        for(int i = 0;i < count;i++){
            jobject _stat = (*env)->GetObjectArrayElement(env,statuses,i);
            jni_mpi_convert_MPI_Status(env,_stat,&stat[i],
                FROM_MPI_STATUS_TO_JAVA_MPI_STATUS);
            (*env)->DeleteLocalRef(env,_stat);
        }
        free(stat);
    }

    for(int i = 0;i < count;i++){

        // delete the global referece
        if(req_type[i] == JNI_MPI_REQUEST_TYPE_RECV){
            release_icom_element(env,&JNI_MPI_QHEAD_IRECV,&req_buff_vec[i],JNI_COMMIT);
        }  
        else if(req_type[i] == JNI_MPI_REQUEST_TYPE_SEND){
            release_icom_element(env,&JNI_MPI_QHEAD_ISEND,&req_buff_vec[i],JNI_ABORT);
        }
        
        (*env)->SetIntField(env,req_cache[i],JNI_MPI_REQUEST_HANDLER,req_vec[i]);

        (*env)->DeleteLocalRef(env,req_cache[i]);
    }
    // free all buffers
    free(req_cache);
    free(req_vec);
    free(req_buff_vec);
    free(req_type);

    fn_exit:
        if(result != MPI_SUCCESS){
            jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
        }
        return MPI_SUCCESS;
    fn_fail:
        return -1;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Testall
 * Signature: ([Lorg/mpich/MPI_Request;[Lorg/mpich/MPI_Status;)I
 */
JNIEXPORT jboolean JNICALL 
Java_org_mpich_MPI_MPI_1Testall(
    JNIEnv *env, 
    jclass class, 
    jobjectArray requests, 
    jobjectArray statuses)
{
    int count = (*env)->GetArrayLength(env,requests);
    int result = 0;
    int flag;

    MPI_Request *req_vec = malloc(sizeof(MPI_Request)*count);
    MPI_Request *req_buff_vec = malloc(sizeof(MPI_Request)*count);
    jobject *req_cache = malloc(sizeof(jobject)*count);
    int *req_type = malloc(sizeof(int)*count);

    if (req_vec == NULL || req_buff_vec == NULL ||
            req_cache == NULL || req_type == NULL) {
        goto fn_fail;
    }

     // for each request object
    for(int i = 0;i < count;i++){
        req_cache[i] = (*env)->GetObjectArrayElement(env,requests,i);
        req_vec[i] = (*env)->GetIntField(env,req_cache[i],
            JNI_MPI_REQUEST_HANDLER);
        req_buff_vec[i] = req_vec[i];
        req_type[i] = (*env)->GetIntField(env,req_cache[i],JNI_MPI_REQUEST_TYPE);
    }

    if(statuses == NULL){
        result = MPI_Testall(count,req_vec,&flag,MPI_STATUSES_IGNORE);
    }
    else {
        MPI_Status *stat = malloc(sizeof(MPI_Status)*count);
        result = MPI_Testall(count,req_vec,&flag,stat);
        // set all statuses
        for(int i = 0;i < count;i++){
            jobject _stat = (*env)->GetObjectArrayElement(env,statuses,i);
            jni_mpi_convert_MPI_Status(env,_stat,&stat[i],
                FROM_MPI_STATUS_TO_JAVA_MPI_STATUS);
            (*env)->DeleteLocalRef(env,_stat);
        }
        free(stat);
    }

    if(flag == 1){

        for(int i = 0;i < count;i++){

            // delete the global referece
            if(req_type[i] == JNI_MPI_REQUEST_TYPE_RECV){
                release_icom_element(env,&JNI_MPI_QHEAD_IRECV,&req_buff_vec[i],JNI_COMMIT);
            }  
            else if(req_type[i] == JNI_MPI_REQUEST_TYPE_SEND){
                release_icom_element(env,&JNI_MPI_QHEAD_ISEND,&req_buff_vec[i],JNI_ABORT);
            }
            
            (*env)->SetIntField(env,req_cache[i],JNI_MPI_REQUEST_HANDLER,req_vec[i]);

            (*env)->DeleteLocalRef(env,req_cache[i]);
        }
    }
    // free all buffers
    free(req_cache);
    free(req_vec);
    free(req_buff_vec);
    free(req_type);

    fn_exit:
        if(result != MPI_SUCCESS){
            jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
        }
        if(flag == 1)
            return JNI_TRUE;
        else
            return JNI_FALSE;
    fn_fail:
        return JNI_FALSE;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Waitsome
 * Signature: ([Lorg/mpich/MPI_Request;[I[Lorg/mpich/MPI_Status;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Waitsome(
    JNIEnv *env, 
    jclass class, 
    jobjectArray requests, 
    jintArray indexes, 
    jobjectArray statuses)
{
    int count = (*env)->GetArrayLength(env,requests);
    jint* idxs= (*env)->GetIntArrayElements(env,indexes,NULL);
    int outcount = 0;
    int result = 0;

    MPI_Request *req_vec = malloc(sizeof(MPI_Request)*count);
    MPI_Request *req_buff_vec = malloc(sizeof(MPI_Request)*count);
    jobject *req_cache = malloc(sizeof(jobject)*count);
    int *req_type = malloc(sizeof(int)*count);

    if (req_vec == NULL || req_buff_vec == NULL ||
            req_cache == NULL || req_type == NULL) {
        goto fn_fail;
    }

     // for each request object
    for(int i = 0;i < count;i++){
        req_cache[i] = (*env)->GetObjectArrayElement(env,requests,i);
        req_vec[i] = (*env)->GetIntField(env,req_cache[i],
            JNI_MPI_REQUEST_HANDLER);
        req_buff_vec[i] = req_vec[i];
        req_type[i] = (*env)->GetIntField(env,req_cache[i],JNI_MPI_REQUEST_TYPE);
    }

    if(statuses == NULL){
        result = MPI_Waitsome(count,req_vec,&outcount,idxs,MPI_STATUSES_IGNORE);
    }
    else {
        MPI_Status *stat = malloc(sizeof(MPI_Status)*count);
        result = MPI_Waitsome(count,req_vec,&outcount,idxs,stat);
        // set all statuses
        for(int i = 0;i < count;i++){
            jobject _stat = (*env)->GetObjectArrayElement(env,statuses,i);
            jni_mpi_convert_MPI_Status(env,_stat,&stat[i],
                FROM_MPI_STATUS_TO_JAVA_MPI_STATUS);
            (*env)->DeleteLocalRef(env,_stat);
        }
        free(stat);
    }

    for(int i = 0;i < outcount;i++){
        // delete the global referece
        if(req_type[idxs[i]] == JNI_MPI_REQUEST_TYPE_RECV){
            release_icom_element(env,&JNI_MPI_QHEAD_IRECV,&req_buff_vec[idxs[i]],JNI_COMMIT);
        }  
        else if(req_type[idxs[i]] == JNI_MPI_REQUEST_TYPE_SEND){
            release_icom_element(env,&JNI_MPI_QHEAD_ISEND,&req_buff_vec[idxs[i]],JNI_ABORT);
        }
        
        (*env)->SetIntField(env,req_cache[idxs[i]],JNI_MPI_REQUEST_HANDLER,req_vec[idxs[i]]);
    }

    for(int i = 0;i < count;i++){
        (*env)->DeleteLocalRef(env,req_cache[i]);
    }
    // free all buffers
    free(req_cache);
    free(req_vec);
    free(req_buff_vec);
    free(req_type);

    (*env)->ReleaseIntArrayElements(env,indexes,idxs,JNI_COMMIT);

    fn_exit:
        if(result != MPI_SUCCESS){
            jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
        }
        return outcount;
    fn_fail:
        return -1;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Testsome
 * Signature: ([Lorg/mpich/MPI_Request;[I[Lorg/mpich/MPI_Status;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Testsome(
    JNIEnv *env, 
    jclass class, 
    jobjectArray requests, 
    jintArray indexes, 
    jobjectArray statuses)
{
        int count = (*env)->GetArrayLength(env,requests);
    jint* idxs= (*env)->GetIntArrayElements(env,indexes,NULL);
    int outcount = 0;
    int result = 0;

    MPI_Request *req_vec = malloc(sizeof(MPI_Request)*count);
    MPI_Request *req_buff_vec = malloc(sizeof(MPI_Request)*count);
    jobject *req_cache = malloc(sizeof(jobject)*count);
    int *req_type = malloc(sizeof(int)*count);

    if (req_vec == NULL || req_buff_vec == NULL ||
            req_cache == NULL || req_type == NULL) {
        goto fn_fail;
    }

     // for each request object
    for(int i = 0;i < count;i++){
        req_cache[i] = (*env)->GetObjectArrayElement(env,requests,i);
        req_vec[i] = (*env)->GetIntField(env,req_cache[i],
            JNI_MPI_REQUEST_HANDLER);
        req_buff_vec[i] = req_vec[i];
        req_type[i] = (*env)->GetIntField(env,req_cache[i],JNI_MPI_REQUEST_TYPE);
    }

    if(statuses == NULL){
        result = MPI_Testsome(count,req_vec,&outcount,idxs,MPI_STATUSES_IGNORE);
    }
    else {
        MPI_Status *stat = malloc(sizeof(MPI_Status)*count);
        result = MPI_Testsome(count,req_vec,&outcount,idxs,stat);
        // set all statuses
        for(int i = 0;i < count;i++){
            jobject _stat = (*env)->GetObjectArrayElement(env,statuses,i);
            jni_mpi_convert_MPI_Status(env,_stat,&stat[i],
                FROM_MPI_STATUS_TO_JAVA_MPI_STATUS);
            (*env)->DeleteLocalRef(env,_stat);
        }
        free(stat);
    }

    for(int i = 0;i < outcount;i++){
        // delete the global referece
        if(req_type[idxs[i]] == JNI_MPI_REQUEST_TYPE_RECV){
            release_icom_element(env,&JNI_MPI_QHEAD_IRECV,&req_buff_vec[idxs[i]],JNI_COMMIT);
        }  
        else if(req_type[idxs[i]] == JNI_MPI_REQUEST_TYPE_SEND){
            release_icom_element(env,&JNI_MPI_QHEAD_ISEND,&req_buff_vec[idxs[i]],JNI_ABORT);
        }
        
        (*env)->SetIntField(env,req_cache[idxs[i]],JNI_MPI_REQUEST_HANDLER,req_vec[idxs[i]]);
    }

    for(int i = 0;i < count;i++){
        (*env)->DeleteLocalRef(env,req_cache[i]);
    }
    // free all buffers
    free(req_cache);
    free(req_vec);
    free(req_buff_vec);
    free(req_type);

    (*env)->ReleaseIntArrayElements(env,indexes,idxs,JNI_COMMIT);

    fn_exit:
        if(result != MPI_SUCCESS){
            jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
        }
        return outcount;
    fn_fail:
        return -1;
}
