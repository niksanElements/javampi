/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class mpi_Win */

#ifndef _Included_mpi_Win
#define _Included_mpi_Win
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     mpi_Win
 * Method:    _fence
 * Signature: (IJ)V
 */
JNIEXPORT void JNICALL Java_mpi_Win__1fence
  (JNIEnv *, jclass, jint, jlong);

/*
 * Class:     mpi_Win
 * Method:    _accumulate
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_mpi_Win__1accumulate
  (JNIEnv *, jclass);

/*
 * Class:     mpi_Win
 * Method:    _get
 * Signature: (Ljava/lang/Object;IIJIJIJJ)V
 */
JNIEXPORT void JNICALL Java_mpi_Win__1get
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jint, jlong, jint, jlong, jlong);

/*
 * Class:     mpi_Win
 * Method:    _put
 * Signature: (Ljava/lang/Object;IIJIJIJJ)V
 */
JNIEXPORT void JNICALL Java_mpi_Win__1put
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jint, jlong, jint, jlong, jlong);

/*
 * Class:     mpi_Win
 * Method:    _flush
 * Signature: (IJ)V
 */
JNIEXPORT void JNICALL Java_mpi_Win__1flush
  (JNIEnv *, jclass, jint, jlong);

/*
 * Class:     mpi_Win
 * Method:    _flush_all
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_mpi_Win__1flush_1all
  (JNIEnv *, jclass, jlong);

/*
 * Class:     mpi_Win
 * Method:    _flush_local
 * Signature: (IJ)V
 */
JNIEXPORT void JNICALL Java_mpi_Win__1flush_1local
  (JNIEnv *, jclass, jint, jlong);

/*
 * Class:     mpi_Win
 * Method:    _flush_local_all
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_mpi_Win__1flush_1local_1all
  (JNIEnv *, jclass, jlong);

/*
 * Class:     mpi_Win
 * Method:    _get_info
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_mpi_Win__1get_1info
  (JNIEnv *, jclass, jlong);

/*
 * Class:     mpi_Win
 * Method:    _set_info
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_mpi_Win__1set_1info
  (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     mpi_Win
 * Method:    _get_group
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_mpi_Win__1get_1group
  (JNIEnv *, jclass, jlong);

/*
 * Class:     mpi_Win
 * Method:    _get_name
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_mpi_Win__1get_1name
  (JNIEnv *, jclass, jlong);

/*
 * Class:     mpi_Win
 * Method:    _set_name
 * Signature: (Ljava/lang/String;J)V
 */
JNIEXPORT void JNICALL Java_mpi_Win__1set_1name
  (JNIEnv *, jclass, jstring, jlong);

/*
 * Class:     mpi_Win
 * Method:    _lock
 * Signature: (IIIJ)V
 */
JNIEXPORT void JNICALL Java_mpi_Win__1lock
  (JNIEnv *, jclass, jint, jint, jint, jlong);

/*
 * Class:     mpi_Win
 * Method:    _lock_all
 * Signature: (IJ)V
 */
JNIEXPORT void JNICALL Java_mpi_Win__1lock_1all
  (JNIEnv *, jclass, jint, jlong);

/*
 * Class:     mpi_Win
 * Method:    _unlock
 * Signature: (IJ)V
 */
JNIEXPORT void JNICALL Java_mpi_Win__1unlock
  (JNIEnv *, jclass, jint, jlong);

/*
 * Class:     mpi_Win
 * Method:    _unlock_all
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_mpi_Win__1unlock_1all
  (JNIEnv *, jclass, jlong);

/*
 * Class:     mpi_Win
 * Method:    _sync
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_mpi_Win__1sync
  (JNIEnv *, jclass, jlong);

/*
 * Class:     mpi_Win
 * Method:    _free
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_mpi_Win__1free
  (JNIEnv *, jclass, jlong);

/*
 * Class:     mpi_Win
 * Method:    _shared_query
 * Signature: (JILmpi/Win/Win_allocate_ret;)V
 */
JNIEXPORT void JNICALL Java_mpi_Win__1shared_1query
  (JNIEnv *, jclass, jlong, jint, jobject);

#ifdef __cplusplus
}
#endif
#endif
