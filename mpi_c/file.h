#ifndef JNI_MPI_C_FILE_H
#define JNI_MPI_C_FILE_H

#include <mpi.h>

#define JNI_MPI_FILE_T_SIZE 128

extern int init_file();
extern int insert_file(MPI_File* file);
extern MPI_File* get_file(int key);
extern int delete_file(int key);

#define FILE_GET_HANDLER(env,file,fh)\
    file = get_file(fh);\
    if(file == NULL){\
        jni_mpi_throw_new(env,\
            "org/mpich/exceptions/MPI_File_handler_exception");\
        goto fn_fail;\
    }

#endif // JNI_MPI_C_FILE_H