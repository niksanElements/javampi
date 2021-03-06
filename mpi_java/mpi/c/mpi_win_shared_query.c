#include "mpi_Win.h"
#include "jni_mpi.h"
#include "jni_mpi_win.h"

/*
 * Class:     mpi_Win
 * Method:    _shared_query
 * Signature: (JILmpi/Win/Win_allocate_ret;)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Win__1shared_1query(
    JNIEnv *env, jclass class, jlong win, jint rank, jobject objwinret)
{
    int result;
    void *baseaddr = NULL;
    MPI_Aint size;
    int disp_unit;
    jobject direct_buffer;

    result = MPI_Win_shared_query((MPI_Win)win,rank,&size,&disp_unit,&baseaddr);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Win_shared_query");
        return;
    }

    // create a direct buffer
    direct_buffer =(*env)->NewDirectByteBuffer(env,baseaddr,size);
    if(direct_buffer == NULL){
        return; // exception from JNI
    }
    // fill the return object (objwin)
    (*env)->SetIntField(env,objwinret,gJniWinReturnSize,(jint)size);
    (*env)->SetLongField(env,objwinret,gJniWinReturnAddress,(long)baseaddr);
    (*env)->SetObjectField(env,objwinret,gJniWinReturnBuffer,direct_buffer);
    // TODO: disp_unit MPI_Win_shared_query return
}