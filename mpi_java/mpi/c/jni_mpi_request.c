#include "jni_mpi_request.h"

#include "malloc.h"

void jniMpiRequestFree(JNIEnv *env,tJniRequest* request)
{
    for(int i = 0;i < JNI_IMAX_BUFFERS;i++){
        if(request->buffers[i] != NULL){
            if(!request->isSendRequest){
                request->type[i]->setBuffer(env,request->buffers[i],
                    request->offset[i],request->count[i],&request->address[i],
                    request->type[i]->size,JNI_COMMIT);
            }
            (*env)->DeleteGlobalRef(env,request->buffers[i]);
            free(request->address[i]);
        }
    }

    free(request);
}