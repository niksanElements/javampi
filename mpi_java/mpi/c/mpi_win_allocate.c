#include "mpi_Intracomm.h"
#include "jni_mpi.h"
#include "jni_mpi_win.h"


/*
 * Class:     mpi_Intracomm
 * Method:    _allocate
 * Signature: (JIJJLmpi/Win/Win_allocate_ret;)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Intracomm__1allocate(
    JNIEnv *env, jclass class, jlong size, jint disp_unit, 
    jlong info, jlong comm, jobject objwin)
{
    int result;
    long win = 0;
    void* baseptr = NULL;
    jobject direct_buffer;

    result = MPI_Win_allocate(size,disp_unit,
        (MPI_Info)info,(MPI_Comm)comm,&baseptr,(MPI_Win*)&win);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Win_allocate");
        return;
    }

    // create the direct buffer
    direct_buffer = (*env)->NewDirectByteBuffer(env,baseptr,size);
    if(direct_buffer == NULL){
        // JNI must thorow run time exception 
        return;
    }

    // fill the return object (objwin)
    (*env)->SetLongField(env,objwin,gJniWinReturnWin,win);
    (*env)->SetLongField(env,objwin,gJniWinReturnAddress,(long)baseptr);
    (*env)->SetObjectField(env,objwin,gJniWinReturnBuffer,direct_buffer);
}

/*
 * Class:     mpi_Intracomm
 * Method:    _allocate_shared
 * Signature: (JIJJLmpi/Win/Win_allocate_ret;)V
 */
JNIEXPORT void JNICALL 
Java_mpi_Intracomm__1allocate_1shared(
    JNIEnv *env, jclass class, jlong size, jint disp_unit, 
    jlong info, jlong comm, jobject objwin)
{
    int result;
    long win = 0;
    void* baseptr = NULL;
    jobject direct_buffer;

    result = MPI_Win_allocate_shared(size,disp_unit,
        (MPI_Info)info,(MPI_Comm)comm,&baseptr,(MPI_Win*)&win);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Win_allocate_shared");
        return;
    }

    // create the direct buffer
    direct_buffer = (*env)->NewDirectByteBuffer(env,baseptr,size);
    if(direct_buffer == NULL){
        // JNI must thorow run time exception 
        return;
    }

    // fill the return object (objwin)
    (*env)->SetLongField(env,objwin,gJniWinReturnWin,win);
    (*env)->SetLongField(env,objwin,gJniWinReturnAddress,(long)baseptr);
    (*env)->SetObjectField(env,objwin,gJniWinReturnBuffer,direct_buffer);
}