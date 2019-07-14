#include "jni_mpi.h"
#include "mpi_datatype_Datatype.h"
#include "jni_mpi_types.h"

// TODO: check for malloc header
#include "malloc.h"

/*
 * Class:     mpi_datatype_Datatype
 * Method:    _commit
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_datatype_Datatype__1commit__I(
    JNIEnv *env, 
    jclass class, 
    jint size)
{
    int result;
    tJniType *custom_type;
    jlong handler;
    MPI_Datatype new_type = 0;

    // allocate the type
    custom_type = malloc(sizeof(tJniType));
    if(custom_type == NULL){
        jniOutOfMemoryException(env,"malloc");
        return -1;
    }
    // configure the type
    result = MPI_Type_contiguous(size,MPI_BYTE,&new_type);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Type_contiguous");
        free(custom_type);
        return -1;
    }
    // create the type
    result = MPI_Type_commit(&new_type);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Type_commit");
        free(custom_type);
        return -1;
    }
    // init the custom type
    custom_type->mpi_type = new_type;
    custom_type->isBufferType = JNI_TRUE;
    custom_type->getBuffAddr = getAddrDirectBuffer;
    custom_type->isCustom = JNI_TRUE;
    // the custom type uses direct buffer so it doesn't need 
    // release function
    custom_type->relBuffAddr = NULL;
    custom_type->size = size;

    return (jlong)custom_type;
}