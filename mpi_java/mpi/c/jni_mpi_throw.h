#ifndef JNI_MPI_THROW_H
#define JNI_MPI_THROW_H

#include "jni_mpi.h"

static const char* gMpiExceptionTable[] = 
{
    NULL, // MPI_SUCCESS 0
    "mpi/exception/BufferException", // MPI_ERR_BUFFER 1
    "mpi/exception/CountException", // MPI_ERR_COUNT 2
    "mpi/exception/TypeException", // MPI_ERR_TYPE 3
    "mpi/exception/TagException", // MPI_ERR_TAG 4
    "mpi/exception/CommException", // MPI_ERR_COMM 5
    "mpi/exception/RankException", // MPI_ERR_RANK 6
    "mpi/exception/RootException", // MPI_ERR_ROOT 7
    "mpi/exception/GroupException", // MPI_ERR_GROUP 8
    NULL, // "mpi/exception/OpException", // MPI_ERR_OP 9
    "mpi/exception/TopologyException", // MPI_ERR_TOPOLOGY 10
    "mpi/exception/DimsException", // MPI_ERR_DIMS 11
    "mpi/exception/ArgException", // MPI_ERR_ARG 12
    NULL, // "mpi/exception/UnknownException", // MPI_ERR_UNKNOWN 13
    NULL, // "mpi/exception/TruncateException", // MPI_ERR_TRUNCATE 14
    "mpi/exception/OtherException", // MPI_ERR_OTHER 15
    "mpi/exception/InternException", // MPI_ERR_INTERN 16
    NULL, // "mpi/exception/In_statusException", // MPI_ERR_IN_STATUS 17
    NULL, // "mpi/exception/PendingException", // MPI_ERR_PENDING 18
    "mpi/exception/RequestException", // MPI_ERR_REQUEST 19
    NULL, // "mpi/exception/AccessException", // MPI_ERR_ACCESS 20
    NULL, // "mpi/exception/AmodeException", // MPI_ERR_AMODE 21
    NULL, // "mpi/exception/Bad_fileException", // MPI_ERR_BAD_FILE 22
    NULL, // "mpi/exception/ConversionException", // MPI_ERR_CONVERSION 23
    NULL, // "mpi/exception/Dup_datarepException", // MPI_ERR_DUP_DATAREP 24
    NULL, // "mpi/exception/File_existsException", // MPI_ERR_FILE_EXISTS 25
    NULL, // "mpi/exception/File_in_useException", // MPI_ERR_FILE_IN_USE 26
    NULL, // "mpi/exception/FileException", // MPI_ERR_FILE 27
    NULL, // "mpi/exception/InfoException", // MPI_ERR_INFO 28
    "mpi/exception/Info_keyException", // MPI_ERR_INFO_KEY 29
    "mpi/exception/Info_valueException", // MPI_ERR_INFO_VALUE 30
    NULL, // "mpi/exception/Info_nokeyException", // MPI_ERR_INFO_NOKEY 31
    NULL, // "mpi/exception/IoException", // MPI_ERR_IO 32
    NULL, // "mpi/exception/NameException", // MPI_ERR_NAME 33
    NULL, // "mpi/exception/No_memException", // MPI_ERR_NO_MEM 34
    NULL, // "mpi/exception/Not_sameException", // MPI_ERR_NOT_SAME 35
    NULL, // "mpi/exception/No_spaceException", // MPI_ERR_NO_SPACE 36
    NULL, // "mpi/exception/No_such_fileException", // MPI_ERR_NO_SUCH_FILE 37
    NULL, // "mpi/exception/PortException", // MPI_ERR_PORT 38
    NULL, // "mpi/exception/QuotaException", // MPI_ERR_QUOTA 39
    NULL, // "mpi/exception/Read_onlyException", // MPI_ERR_READ_ONLY 40
    NULL, // "mpi/exception/ServiceException", // MPI_ERR_SERVICE 41
    NULL, // "mpi/exception/SpawnException", // MPI_ERR_SPAWN 42
    NULL, // "mpi/exception/Unsupported_datarepException", // MPI_ERR_UNSUPPORTED_DATAREP 43
    NULL, // "mpi/exception/Unsupported_operationException", // MPI_ERR_UNSUPPORTED_OPERATION 44
    "mpi/exception/WinException", // MPI_ERR_WIN 45
    NULL, // "mpi/exception/BaseException", // MPI_ERR_BASE 46
    NULL, // "mpi/exception/LocktypeException", // MPI_ERR_LOCKTYPE 47
    NULL, // "mpi/exception/KeyvalException", // MPI_ERR_KEYVAL 48
    NULL, // "mpi/exception/Rma_conflictException", // MPI_ERR_RMA_CONFLICT 49
    NULL, // "mpi/exception/Rma_syncException", // MPI_ERR_RMA_SYNC 50
    "mpi/exception/SizeException", // MPI_ERR_SIZE 51
    NULL, // "mpi/exception/DispException", // MPI_ERR_DISP 52
    NULL, // "mpi/exception/AssertException", // MPI_ERR_ASSERT 53
    NULL, // NULL, // there is no exception with this code
    NULL, // "mpi/exception/Rma_rangeException", // MPI_ERR_RMA_RANGE 55
    NULL, // "mpi/exception/Rma_attachException", // MPI_ERR_RMA_ATTACH 56
    NULL, // "mpi/exception/Rma_sharedException", // MPI_ERR_RMA_SHARED 57
    NULL, // "mpi/exception/Rma_flavorException", // MPI_ERR_RMA_FLAVOR 58
};

// general function for throwing a exception
extern void mpiErr(JNIEnv *env,int err_code,const char* func);
extern void 
jni_throw(
    JNIEnv *env,const char* cls_name,const char* msg);
// java/long/OutOfMemoryError
extern void jniOutOfMemoryException(JNIEnv *env,const char* msg);
// MPI_ERR_INIT
extern void mpiErrOther(JNIEnv *env,const char* func);
// MPI_ERR_COMM
extern void mpiErrComm(JNIEnv *env,const char* func);
// MPI_ERR_ARG
extern void mpiErrArg(JNIEnv *env,const char* func);
// MPI_ERR_TYPE
extern void mpiErrType(JNIEnv *env,const char* func);
// JNI undefined memory from DirectBuffer
extern void jniUndefinedMemException(JNIEnv *env,const char* func);
// java.long.IndexOutOfBoundsException
extern void jniIndexOutOfBoundsException(JNIEnv *env,const char* msg);
// mpi.exception.PermissionsException
extern void mpiPermissionsException(JNIEnv *env,const char* msg);
// mpi.exception.FileException
extern void mpiFileException(JNIEnv *env,const char* msg);

#endif // JNI_MPI_THROW_H