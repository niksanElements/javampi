/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class mpi_Info */

#ifndef _Included_mpi_Info
#define _Included_mpi_Info
#ifdef __cplusplus
extern "C" {
#endif
#undef mpi_Info_null_handler
#define mpi_Info_null_handler 469762048LL
/*
 * Class:     mpi_Info
 * Method:    _create
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_mpi_Info__1create
  (JNIEnv *, jclass);

/*
 * Class:     mpi_Info
 * Method:    _delete
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_mpi_Info__1delete
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     mpi_Info
 * Method:    _dup
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_mpi_Info__1dup
  (JNIEnv *, jclass, jlong);

/*
 * Class:     mpi_Info
 * Method:    _free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_mpi_Info__1free
  (JNIEnv *, jclass, jlong);

/*
 * Class:     mpi_Info
 * Method:    _get
 * Signature: (JLjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_mpi_Info__1get
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     mpi_Info
 * Method:    _nkeys
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_mpi_Info__1nkeys
  (JNIEnv *, jclass, jlong);

/*
 * Class:     mpi_Info
 * Method:    _get_nthkey
 * Signature: (JI)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_mpi_Info__1get_1nthkey
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     mpi_Info
 * Method:    _set
 * Signature: (JLjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_mpi_Info__1set
  (JNIEnv *, jclass, jlong, jstring, jstring);

#ifdef __cplusplus
}
#endif
#endif
