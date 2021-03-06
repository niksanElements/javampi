/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class mpi_Request */

#ifndef _Included_mpi_Request
#define _Included_mpi_Request
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     mpi_Request
 * Method:    _wait
 * Signature: (J)Lmpi/Status;
 */
JNIEXPORT jobject JNICALL Java_mpi_Request__1wait
  (JNIEnv *, jclass, jlong);

/*
 * Class:     mpi_Request
 * Method:    _test
 * Signature: (J)Lmpi/Status;
 */
JNIEXPORT jobject JNICALL Java_mpi_Request__1test
  (JNIEnv *, jclass, jlong);

/*
 * Class:     mpi_Request
 * Method:    _get_status
 * Signature: (J)Lmpi/Status;
 */
JNIEXPORT jobject JNICALL Java_mpi_Request__1get_1status
  (JNIEnv *, jclass, jlong);

/*
 * Class:     mpi_Request
 * Method:    _free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_mpi_Request__1free
  (JNIEnv *, jclass, jlong);

/*
 * Class:     mpi_Request
 * Method:    _cancel
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_mpi_Request__1cancel
  (JNIEnv *, jclass, jlong);

/*
 * Class:     mpi_Request
 * Method:    _start
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_mpi_Request__1start
  (JNIEnv *, jclass, jlong);

#ifdef __cplusplus
}
#endif
#endif
