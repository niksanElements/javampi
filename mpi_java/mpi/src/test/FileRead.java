package test;

import java.util.Arrays;
import java.util.Random;

import mpi.MPI;
import mpi.File;

/**
 * FileRead
 */
public class FileRead {

    public static void main(String[] args) {
        MPI.Init(args);

        int[] buff = new int[1000];

        int rank = MPI.COMM_WORLD.rank();
        File fh = MPI.COMM_WORLD.file_open("/home/nikolay/workspace/test.out", 
            MPI.MODE_CREATE|MPI.MODE_RDWR, MPI.INFO_NULL);
        if(rank == 0){

            fh.read(buff, 0, 1000, MPI.INT, null, null);

            for(int i = 0 ;i < 1000;i++){
                System.out.printf("(%d,%d)",i,buff[i]);
            }
        }

        MPI.COMM_WORLD.barrier();

        fh.close();

        MPI.Finalize();
    }
}