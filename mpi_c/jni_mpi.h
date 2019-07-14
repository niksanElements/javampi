#ifndef JNI_MPI_H
#define JNI_MPI_H

/**
 * MPI Java Native Interface
 * // TODO: license 
 * author: Nikolay
 * email: niksan9411@gmail.com
 */

#include <jni.h>
#include <mpi.h>

#include "org_mpich_MPI.h"
#include "utils.h"

// set this in the mpi.h
#define JNI_FUNCTION_FAIL -1

#define JNI_MPI_REQUEST_TYPE_SEND 10
#define JNI_MPI_REQUEST_TYPE_RECV 74


#endif // JNI_MPI_H