#include "mpi_datatype_Datatype.h"
#include "jni_mpi.h"


/*
 * Class:     mpi_datatype_Datatype
 * Method:    _commit
 * Signature: (J)V
 */
JNIEXPORT void JNICALL 
Java_mpi_datatype_Datatype__1commit__J(
    JNIEnv *env, jclass class, jlong type)
{
    tJniType *_type = (tJniType*)type;
    int result = MPI_Type_commit(&_type->mpi_type);

    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_Type_commit");
    }
}