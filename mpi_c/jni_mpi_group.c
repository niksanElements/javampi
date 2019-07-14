#include "jni_mpi.h"
#include "jni_mpi_exception.h"

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Group_size
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Group_1size(
    JNIEnv *env, jclass class, jint group)
{
    int result;
    int size;

    result = MPI_Group_size(group,&size);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return size;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Group_rank
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Group_1rank(
    JNIEnv *env, jclass class, jint group)
{
    int result;
    int rank;

    result = MPI_Group_rank(group,&rank);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return rank;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Group_translate_ranks
 * Signature: (II[II[I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Group_1translate_1ranks(
    JNIEnv *env, 
    jclass class, 
    jint group1, 
    jint n, 
    jintArray ranks1, 
    jint group2, 
    jintArray ranks2)
{
    int result;
    jint* _ranks1;
    jint* _ranks2;

    _ranks1 = (*env)->GetIntArrayElements(env,ranks1,NULL);
    _ranks2 = (*env)->GetIntArrayElements(env,ranks2,NULL);

    result = MPI_Group_translate_ranks(group1,n,_ranks1,group2,_ranks2);

    (*env)->ReleaseIntArrayElements(env,ranks1,_ranks1,JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env,ranks2,_ranks2,JNI_COMMIT);

    JNI_MPI_RETURN(result);
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Group_compare
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Group_1compare(
    JNIEnv *env, 
    jclass class, 
    jint group1, 
    jint group2)
{
    int result;
    int flag;

    result = MPI_Group_compare(group1,group2,&flag);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return flag;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Group_union
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Group_1union(
    JNIEnv *env, 
    jclass class, 
    jint group1, 
    jint group2)
{
    int newgroup;
    int result;

    result = MPI_Group_union(group1,group2,&newgroup);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return newgroup;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Group_intersection
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Group_1intersection(
    JNIEnv *env, 
    jclass class, 
    jint group1, 
    jint group2)
{
    int newgroup;
    int result;

    result = MPI_Group_intersection(group1,group2,&newgroup);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return newgroup;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Group_difference
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Group_1difference(
    JNIEnv *env, 
    jclass class, 
    jint group1, 
    jint group2)
{
    int newgroup;
    int result;

    result = MPI_Group_difference(group1,group2,&newgroup);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return newgroup;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Group_incl
 * Signature: (II[I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Group_1incl(
    JNIEnv *env, 
    jclass class, 
    jint group, 
    jint n, 
    jintArray ranks)
{
    int result;
    int newgroup;
    jint* _ranks;

    _ranks = (*env)->GetIntArrayElements(env,ranks,NULL);

    result = MPI_Group_incl(group,n,_ranks,&newgroup);

    (*env)->ReleaseIntArrayElements(env,ranks,_ranks,JNI_ABORT);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return newgroup;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Group_excl
 * Signature: (II[I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Group_1excl(
    JNIEnv *env, 
    jclass class, 
    jint group, 
    jint n, 
    jintArray ranks)
{
    int result;
    int newgroup;
    jint* _ranks;

    _ranks = (*env)->GetIntArrayElements(env,ranks,NULL);

    result = MPI_Group_excl(group,n,_ranks,&newgroup);

    (*env)->ReleaseIntArrayElements(env,ranks,_ranks,JNI_ABORT);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return newgroup;
}

/*
 * Class:     org_mpich_MPI
 * Method:      
 * Signature: (II[I[I[I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Group_1range_1incl(
    JNIEnv *env, 
    jclass class, 
    jint group, 
    jint n, 
    jintArray first, 
    jintArray last, 
    jintArray stride)
{
    int newgroup;
    int result;
    jint* _first;
    jint* _last;
    jint* _stride;
    int ranges[n][3];

    _first = (*env)->GetIntArrayElements(env,first,NULL);
    _last = (*env)->GetIntArrayElements(env,last,NULL);
    _stride = (*env)->GetIntArrayElements(env,stride,NULL);

    for(int i = 0;i < n;i++){
        ranges[i][0] = _first[i];
        ranges[i][1] = _last[i];
        ranges[i][2] = _stride[i];
    }

    result = MPI_Group_range_incl(group,n,ranges,&newgroup);

    (*env)->ReleaseIntArrayElements(env,first,_first,JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env,last,_last,JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env,stride,_stride,JNI_ABORT);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return newgroup;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Group_range_excl
 * Signature: (II[I[I[I)I
 */
JNIEXPORT jint JNICALL 
Java_org_mpich_MPI_MPI_1Group_1range_1excl(
    JNIEnv *env, 
    jclass class, 
    jint group, 
    jint n, 
    jintArray first, 
    jintArray last, 
    jintArray stride)
{
    int newgroup;
    int result;
    jint* _first;
    jint* _last;
    jint* _stride;
    int ranges[n][3];

    _first = (*env)->GetIntArrayElements(env,first,NULL);
    _last = (*env)->GetIntArrayElements(env,last,NULL);
    _stride = (*env)->GetIntArrayElements(env,stride,NULL);

    for(int i = 0;i < n;i++){
        ranges[i][0] = _first[i];
        ranges[i][1] = _last[i];
        ranges[i][2] = _stride[i];
    }

    result = MPI_Group_range_excl(group,n,ranges,&newgroup);

    (*env)->ReleaseIntArrayElements(env,first,_first,JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env,last,_last,JNI_ABORT);
    (*env)->ReleaseIntArrayElements(env,stride,_stride,JNI_ABORT);
    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return newgroup;
}

/*
 * Class:     org_mpich_MPI
 * Method:    MPI_Group_free
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL
Java_org_mpich_MPI_MPI_1Group_1free(
    JNIEnv * env, jclass class, jint group)
{
    int result = MPI_Group_free(&group);

    if(result != MPI_SUCCESS){
        jni_mpi_throw_new(env,JNI_MPI_EXCEPTIONS[result]);
    }

    return group;
}