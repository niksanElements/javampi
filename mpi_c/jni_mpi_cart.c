#include "jni_mpi.h"
#include "jni_mpi_exception.h"

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Cart_create
 * Signature: (II[I[II)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Cart_1create(
    JNIEnv *env, 
    jclass class, 
    jint comm_old, 
    jint ndims, 
    jintArray dims, 
    jintArray periods, 
    jint reorder)
{
    int result;
    int comm_cart;
    jint* _dims;
    jint* _periods;

    _dims = (*env)->GetIntArrayElements(env,dims,NULL);
    _periods = (*env)->GetIntArrayElements(env,periods,NULL);

    result = MPI_Cart_create(comm_old,ndims,_dims,_periods,
        reorder,&comm_cart);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    (*env)->ReleaseIntArrayElements(env,dims,_dims,JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env,periods,_periods,JNI_ABORT);

    return comm_cart;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Cartdim_get
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Cartdim_1get(
    JNIEnv *env, 
    jclass class, 
    jint comm)
{
    int result;
    int ndims;

    result = MPI_Cartdim_get(comm,&ndims);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return ndims;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Cart_get
 * Signature: (II[I[I[I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Cart_1get(
    JNIEnv *env, 
    jclass class, 
    jint comm, 
    jint maxdims, 
    jintArray dims, 
    jintArray periods, 
    jintArray coords)
{
    int result;
    jint* _dims;
    jint* _periods;
    jint* _coords;

    _dims = (*env)->GetIntArrayElements(env,dims,NULL);
    _periods = (*env)->GetIntArrayElements(env,periods,NULL);
    _coords = (*env)->GetIntArrayElements(env,coords,NULL);

    result = MPI_Cart_get(comm,maxdims,_dims,_periods,_coords);

    (*env)->ReleaseIntArrayElements(env,dims,_dims,JNI_COMMIT);
    (*env)->ReleaseIntArrayElements(env,periods,_periods,JNI_COMMIT);
    (*env)->ReleaseIntArrayElements(env,coords,_coords,JNI_COMMIT);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Cart_rank
 * Signature: (I[I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Cart_1rank(
    JNIEnv *env, 
    jclass class, 
    jint comm, 
    jintArray coords)
{
    int result;
    int rank;
    jint* _coords;

    _coords = (*env)->GetIntArrayElements(env,coords,NULL);

    result = MPI_Cart_rank(comm,_coords,&rank);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }   

    (*env)->ReleaseIntArrayElements(env,coords,_coords,JNI_ABORT);

    return rank;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Cart_coords
 * Signature: (III[I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Cart_1coords(
    JNIEnv *env, 
    jclass class, 
    jint comm, 
    jint rank, 
    jint maxdims, 
    jintArray coords)
{
    int result;
    jint* _coords = (*env)->GetIntArrayElements(env,coords,NULL);
    result = MPI_Cart_coords(comm,rank,maxdims,_coords);
    (*env)->ReleaseIntArrayElements(env,coords,_coords,JNI_COMMIT);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Cart_shift
 * Signature: (IIILorg/mpich/MPI_Integer_ref;Lorg/mpich/MPI_Integer_ref;)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Cart_1shift(
    JNIEnv *env, 
    jclass class, 
    jint comm, 
    jint direction, 
    jint dist, 
    jobject rank_source, 
    jobject rank_dest)
{
    int result;
    int _rank_source;
    int _rank_dest;

    result = MPI_Cart_shift(comm,direction,dist,
        &_rank_source,&_rank_dest);
    
    (*env)->SetIntField(env,rank_source,JNI_MPI_INTEGER_VALUE,
        _rank_source);
    (*env)->SetIntField(env,rank_dest,JNI_MPI_INTEGER_VALUE,_rank_dest);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Cart_sub
 * Signature: (I[I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Cart_1sub(
    JNIEnv *env, 
    jclass class, 
    jint comm, 
    jintArray remain_dims)
{
    int result;
    int newcomm;
    jint* _remain_dims;

    result = MPI_Cart_sub(comm,_remain_dims,&newcomm);
    (*env)->ReleaseIntArrayElements(env,remain_dims,_remain_dims,JNI_ABORT);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return newcomm;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Cart_map
 * Signature: (II[I[I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Cart_1map(
    JNIEnv *env, 
    jclass class, 
    jint comm, 
    jint ndims, 
    jintArray dims, 
    jintArray periods)
{
    int result;
    int newrank;
    jint* _dims = (*env)->GetIntArrayElements(env,dims,NULL);
    jint* _periods = (*env)->GetIntArrayElements(env,periods,NULL);

    result = MPI_Cart_map(comm,ndims,_dims,_periods,&newrank);
    (*env)->ReleaseIntArrayElements(env,dims,_dims,JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env,periods,_periods,JNI_ABORT);

    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return newrank;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Dims_create
 * Signature: (II[I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Dims_1create(
    JNIEnv *env, 
    jclass class, 
    jint nnodes, 
    jint ndims, 
    jintArray dims)
{
    int result;
    jint* _dims;
    _dims = (*env)->GetIntArrayElements(env,dims,NULL);
    result = MPI_Dims_create(nnodes,ndims,_dims);
    (*env)->ReleaseIntArrayElements(env,dims,_dims,JNI_COMMIT);

    JNI_MPI_RETURN(result);
}

