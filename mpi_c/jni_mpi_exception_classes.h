#ifndef JNI_MPI_EXCEPTIONS_H
#define JNI_MPI_EXCEPTIONS_H

static const char* JNI_MPI_EXCEPTIONS[] = 
{
    "" // MPI_SUCCESS 0
    "org/mpich/exceptions/MPI_Buffer_exception", // BUFFER 1
    "org/mpich/exceptions/MPI_Count_exception", // COUNT 2
    "org/mpich/exceptions/MPI_Type_exception", // TYPE 3
    "org/mpich/exceptions/MPI_Tag_exception", // TAG 4
    "org/mpich/exceptions/MPI_Comm_exception", // COMM 5
    "org/mpich/exceptions/MPI_Rank_exception", // RANK 6
    "org/mpich/exceptions/MPI_Root_exception", // ROOT 7
    "org/mpich/exceptions/MPI_Truncate_exception", // TRUNCATE 14
    "org/mpich/exceptions/MPI_Group_exception", // GROUP 8
    "org/mpich/exceptions/MPI_Op_exception", // OP 9
    "org/mpich/exceptions/MPI_Request_exception", // REQUEST 19
    "org/mpich/exceptions/MPI_Topology_exception", // TOPOLOGY 10
    "org/mpich/exceptions/MPI_Dims_exception", // DIMS 11
    "org/mpich/exceptions/MPI_Arg_exception", // ARG 12
    "org/mpich/exceptions/MPI_Other_exception", // OTHER 15
    "org/mpich/exceptions/MPI_Unknown_exception", // UNKNOWN 13
    "org/mpich/exceptions/MPI_Intern_exception", // INTERN 16
    "org/mpich/exceptions/MPI_In_status_exception", // IN_STATUS 17
    "org/mpich/exceptions/MPI_Pending_exception", // PENDING 18
    "org/mpich/exceptions/MPI_Access_exception", // ACCESS 20
    "org/mpich/exceptions/MPI_Amode_exception", // AMODE 21
    "org/mpich/exceptions/MPI_Bad_file_exception", // BAD_FILE 22
    "org/mpich/exceptions/MPI_Conversion_exception", // CONVERSION 23
    "org/mpich/exceptions/MPI_Dup_datarep_exception", // DUP_DATAREP 24
    "org/mpich/exceptions/MPI_File_exists_exception", // FILE_EXISTS 25
    "org/mpich/exceptions/MPI_File_in_use_exception", // FILE_IN_USE 26
    "org/mpich/exceptions/MPI_File_exception", // FILE 27
    "org/mpich/exceptions/MPI_Info_exception", // INFO 28
    "org/mpich/exceptions/MPI_Info_key_exception", // INFO_KEY 29
    "org/mpich/exceptions/MPI_Info_value_exception", // INFO_VALUE 30
    "org/mpich/exceptions/MPI_Info_nokey_exception", // INFO_NOKEY 31
    "org/mpich/exceptions/MPI_Io_exception", // IO 32
    "org/mpich/exceptions/MPI_Name_exception", // NAME 33
    "org/mpich/exceptions/MPI_No_mem_exception", // NO_MEM 34
    "org/mpich/exceptions/MPI_Not_same_exception", // NOT_SAME 35
    "org/mpich/exceptions/MPI_No_space_exception", // NO_SPACE 36
    "org/mpich/exceptions/MPI_No_such_file_exception", // NO_SUCH_FILE 37
    "org/mpich/exceptions/MPI_Port_exception", // PORT 38
    "org/mpich/exceptions/MPI_Quota_exception", // QUOTA 39
    "org/mpich/exceptions/MPI_Read_only_exception", // READ_ONLY 40
    "org/mpich/exceptions/MPI_Service_exception", // SERVICE 41
    "org/mpich/exceptions/MPI_Spawn_exception", // SPAWN 42
    "org/mpich/exceptions/MPI_Unsupported_datarep_exception", // UNSUPPORTED_DATAREP 43
    "org/mpich/exceptions/MPI_Unsupported_operation_exception", // UNSUPPORTED_OPERATION 44
    "org/mpich/exceptions/MPI_Win_exception", // WIN 45
    "org/mpich/exceptions/MPI_Base_exception", // BASE 46
    "org/mpich/exceptions/MPI_Locktype_exception", // LOCKTYPE 47
    "org/mpich/exceptions/MPI_Keyval_exception", // KEYVAL 48
    "org/mpich/exceptions/MPI_Rma_conflict_exception", // RMA_CONFLICT 49
    "org/mpich/exceptions/MPI_Rma_sync_exception", // RMA_SYNC 50
    "org/mpich/exceptions/MPI_Size_exception", // SIZE 51
    "org/mpich/exceptions/MPI_Disp_exception", // DISP 52
    "org/mpich/exceptions/MPI_Assert_exception", // ASSERT 53
    "org/mpich/exceptions/MPI_Rma_range_exception", // RMA_RANGE 55
    "org/mpich/exceptions/MPI_Rma_attach_exception", // RMA_ATTACH 56
    "org/mpich/exceptions/MPI_Rma_shared_exception", // RMA_SHARED 57
    "org/mpich/exceptions/MPI_Rma_flavor_exception", // RMA_FLAVOR 58
    "org/mpich/exceptions/MPI_Lastcode_exception", // LASTCODE 0
};

#endif // JNI_MPI_EXCEPTIONS_H
