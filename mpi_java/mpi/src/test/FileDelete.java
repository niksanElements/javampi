package test;

import java.util.Random;

import mpi.MPI;
import mpi.File;

/**
 * FileDelete
 */
public class FileDelete {

    public static void main(String[] args) {
        MPI.Init(args);

        int rank = MPI.COMM_WORLD.rank();
        if(rank == 0){
            MPI.file_delete("/home/nikolay/workspace/test.out", MPI.INFO_NULL);
        }


        MPI.Finalize();
    }
}