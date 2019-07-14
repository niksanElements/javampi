#include "mpi_Win.h"
#include "jni_mpi.h"

/*
 * Class:     mpi_Win
 * Method:    _put
 * Signature: (Ljava/lang/Object;IIJIJIJJ)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Win__1put(
    JNIEnv *env, jclass class, jobject origin_address,jint origin_offset, jint origin_count, jlong origin_type, 
    jint target_rank, jlong target_disp, jint target_count, jlong target_type, jlong win)
{
    int result;
    tJniType *_origin_type = (tJniType*)origin_type;
    tJniType *_target_type = (tJniType*)target_type;

    void *_origin;

    if(_origin_type->isBufferType){

        _origin_type->getBuffAddr(env,origin_address,origin_offset,
            origin_count,&_origin,_origin_type->size,0);

        result = MPI_Put(_origin,origin_count,_origin_type->mpi_type,
            target_count,(MPI_Aint)target_disp,target_count,_target_type->mpi_type,(MPI_Win)win);

        if(result != MPI_SUCCESS){
            mpiErr(env,result,"MPI_Put");
        }
    }

}