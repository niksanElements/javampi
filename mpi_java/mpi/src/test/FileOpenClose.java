package test;

import java.util.Random;

import mpi.MPI;
import mpi.File;

/**
 * FileOpenClose
 */
public class FileOpenClose {

    public static void main(String[] args) {
        MPI.Init(args);

        int rank = MPI.COMM_WORLD.rank();
        File fh = MPI.COMM_WORLD.file_open("/home/nikolay/workspace/test.out", 
            MPI.MODE_CREATE|MPI.MODE_WRONLY, MPI.INFO_NULL);
        if(rank == 0){
            int[] buff = new int[1000];
            Random rand = new Random(System.nanoTime());
            for(int i = 0;i < 1000;i++){
                buff[i] = i*100;
            }

            fh.write(buff, 0, 1000, MPI.INT, null, null);
        }

        int access_mode = fh.amode();
        System.out.println(access_mode);

        fh.close();

        MPI.Finalize();
    }
}