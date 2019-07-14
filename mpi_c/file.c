#include "file.h"

#include <semaphore.h>
#include <malloc.h>

MPI_File** file_table;
int f_table_count;
sem_t sem_file;

int init_file()
{
    file_table = calloc(JNI_MPI_FILE_T_SIZE,sizeof(MPI_File*));
    if(file_table == NULL){
        goto fn_fail;
    }
    f_table_count = 0;
    /**
     * We are initializing the the semaphore as 
     * follow:
     *  - semaphore shared between threads
     *  - his initial value is 0
     */
    if(sem_init(&sem_file,0,1) == -1){
        free(file_table);
        goto fn_fail;
    }

    printf("sem initialized!\n");

    fn_exit:
        return 0;
    fn_fail:
        return -1;
}

int insert_file(MPI_File* file)
{
    int result;
    int counts;
    sem_wait(&sem_file);

    while(file_table[f_table_count] != NULL){
        // We are checking all handlers if 
        // there isn't free once an error is 
        // returns.
        if(counts >= JNI_MPI_FILE_T_SIZE){
            goto fn_fail;
        }
        counts++;
        // we loop around all handlers
        f_table_count++;
        if(f_table_count >= JNI_MPI_FILE_T_SIZE){
            f_table_count = 0;
        }
    }
    
    file_table[f_table_count] = file;
    result = f_table_count;
    f_table_count++;

     // we loop around all handlers
    if(f_table_count >= JNI_MPI_FILE_T_SIZE){
        f_table_count = 0;
    }

    fn_exit:
        sem_post(&sem_file);
        return result;
    fn_fail:
        sem_post(&sem_file);
        return -1;
}

MPI_File* get_file(int key)
{
    MPI_File *temp = NULL;

    if(key >= JNI_MPI_FILE_T_SIZE){
        goto fn_fail;
    }

    sem_wait(&sem_file);
    temp = file_table[key];
    sem_post(&sem_file);

    fn_exit:
        return temp;
    fn_fail:
        return NULL;
}

int delete_file(int key)
{
    if(key >= JNI_MPI_FILE_T_SIZE){
        goto fn_fail;
    }
    
    sem_wait(&sem_file);
    file_table[key] = NULL;
    sem_post(&sem_file);

    fn_exit:
        return 0;
    fn_fail:
        return -1;
}