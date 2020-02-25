/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class mpi_Comm */

#ifndef _Included_mpi_Comm
#define _Included_mpi_Comm
#ifdef __cplusplus
extern "C" {
#endif
#undef mpi_Comm_null_handler
#define mpi_Comm_null_handler 67108864LL
/*
 * Class:     mpi_Comm
 * Method:    _rank
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_mpi_Comm__1rank
  (JNIEnv *, jclass, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _size
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_mpi_Comm__1size
  (JNIEnv *, jclass, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_mpi_Comm__1free
  (JNIEnv *, jclass, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _group
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_mpi_Comm__1group
  (JNIEnv *, jclass, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _abort
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_mpi_Comm__1abort
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     mpi_Comm
 * Method:    _compare
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL Java_mpi_Comm__1compare
  (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _dup
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_mpi_Comm__1dup
  (JNIEnv *, jclass, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _send
 * Signature: (Ljava/lang/Object;IIJIIJ)V
 */
JNIEXPORT void JNICALL Java_mpi_Comm__1send
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jint, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _bsend
 * Signature: (Ljava/lang/Object;IIJIIJ)V
 */
JNIEXPORT void JNICALL Java_mpi_Comm__1bsend
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jint, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _ssend
 * Signature: (Ljava/lang/Object;IIJIIJ)V
 */
JNIEXPORT void JNICALL Java_mpi_Comm__1ssend
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jint, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _rsend
 * Signature: (Ljava/lang/Object;IIJIIJ)V
 */
JNIEXPORT void JNICALL Java_mpi_Comm__1rsend
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jint, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _recv
 * Signature: (Ljava/lang/Object;IIJIIJ)Lmpi/Status;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1recv
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jint, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _isend
 * Signature: (Ljava/lang/Object;IIJIIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1isend
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jint, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _ibsend
 * Signature: (Ljava/lang/Object;IIJIIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1ibsend
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jint, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _issend
 * Signature: (Ljava/lang/Object;IIJIIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1issend
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jint, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _irsend
 * Signature: (Ljava/lang/Object;IIJIIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1irsend
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jint, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _irecv
 * Signature: (Ljava/lang/Object;IIJIIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1irecv
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jint, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _probe
 * Signature: (IIJ)Lmpi/Status;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1probe
  (JNIEnv *, jclass, jint, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _iprobe
 * Signature: (IIJ)Lmpi/Status;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1iprobe
  (JNIEnv *, jclass, jint, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _send_init
 * Signature: (Ljava/lang/Object;IIJIIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1send_1init
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jint, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _bsend_init
 * Signature: (Ljava/lang/Object;IIJIIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1bsend_1init
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jint, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _ssend_init
 * Signature: (Ljava/lang/Object;IIJIIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1ssend_1init
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jint, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _rsend_init
 * Signature: (Ljava/lang/Object;IIJIIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1rsend_1init
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jint, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _recv_init
 * Signature: (Ljava/lang/Object;IIJIIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1recv_1init
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jint, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _mprobe
 * Signature: (IIJ)Lmpi/Message;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1mprobe
  (JNIEnv *, jclass, jint, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _improbe
 * Signature: (IIJ)Lmpi/Message;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1improbe
  (JNIEnv *, jclass, jint, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _sendrecv
 * Signature: (Ljava/lang/Object;IIJIILjava/lang/Object;IIJIIJ)Lmpi/Status;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1sendrecv
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jint, jint, jobject, jint, jint, jlong, jint, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _sendrecv_replace
 * Signature: (Ljava/lang/Object;IIJIIIIJ)Lmpi/Status;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1sendrecv_1replace
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jint, jint, jint, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _barrier
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_mpi_Comm__1barrier
  (JNIEnv *, jclass, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _ibarrier
 * Signature: (J)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1ibarrier
  (JNIEnv *, jclass, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _bcast
 * Signature: (Ljava/lang/Object;IIJIJ)V
 */
JNIEXPORT void JNICALL Java_mpi_Comm__1bcast
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _ibcast
 * Signature: (Ljava/lang/Object;IIJIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1ibcast
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _scatter
 * Signature: (Ljava/lang/Object;IIJLjava/lang/Object;IIJIJ)V
 */
JNIEXPORT void JNICALL Java_mpi_Comm__1scatter
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jobject, jint, jint, jlong, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _iscatter
 * Signature: (Ljava/lang/Object;IIJLjava/lang/Object;IIJIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1iscatter
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jobject, jint, jint, jlong, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _gather
 * Signature: (Ljava/lang/Object;IIJLjava/lang/Object;IIJIJ)V
 */
JNIEXPORT void JNICALL Java_mpi_Comm__1gather
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jobject, jint, jint, jlong, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _igather
 * Signature: (Ljava/lang/Object;IIJLjava/lang/Object;IIJIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1igather
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jobject, jint, jint, jlong, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _allgather
 * Signature: (Ljava/lang/Object;IIJLjava/lang/Object;IIJJ)V
 */
JNIEXPORT void JNICALL Java_mpi_Comm__1allgather
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jobject, jint, jint, jlong, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _iallgather
 * Signature: (Ljava/lang/Object;IIJLjava/lang/Object;IIJJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1iallgather
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jobject, jint, jint, jlong, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _alltoall
 * Signature: (Ljava/lang/Object;IIJLjava/lang/Object;IIJJ)V
 */
JNIEXPORT void JNICALL Java_mpi_Comm__1alltoall
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jobject, jint, jint, jlong, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _ialltoall
 * Signature: (Ljava/lang/Object;IIJLjava/lang/Object;IIJJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1ialltoall
  (JNIEnv *, jclass, jobject, jint, jint, jlong, jobject, jint, jint, jlong, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _reduce
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;IIIJJIJ)V
 */
JNIEXPORT void JNICALL Java_mpi_Comm__1reduce
  (JNIEnv *, jclass, jobject, jobject, jint, jint, jint, jlong, jlong, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _ireduce
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;IIIJJIJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1ireduce
  (JNIEnv *, jclass, jobject, jobject, jint, jint, jint, jlong, jlong, jint, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _allreduce
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;IIIJJJ)V
 */
JNIEXPORT void JNICALL Java_mpi_Comm__1allreduce
  (JNIEnv *, jclass, jobject, jobject, jint, jint, jint, jlong, jlong, jlong);

/*
 * Class:     mpi_Comm
 * Method:    _iallreduce
 * Signature: (Ljava/lang/Object;Ljava/lang/Object;IIIJJJ)Lmpi/Request;
 */
JNIEXPORT jobject JNICALL Java_mpi_Comm__1iallreduce
  (JNIEnv *, jclass, jobject, jobject, jint, jint, jint, jlong, jlong, jlong);

#ifdef __cplusplus
}
#endif
#endif
