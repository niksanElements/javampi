#include "mpi_datatype_Datatype.h"
#include "jni_mpi.h"

#include "malloc.h"

/*
 * Class:     mpi_datatype_Datatype
 * Method:    _type_free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL 
Java_mpi_datatype_Datatype__1type_1free(
    JNIEnv *env, jclass class, jlong type)
{
    tJniType *_type = (tJniType*)type;

    MPI_Type_free(&_type->mpi_type);

    free(_type);
}