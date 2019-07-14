package test;

import mpi.File;
import mpi.MPI;

/**
 * FileWriteReadAll
 */
public class FileWriteReadAll {

    public static void main(String[] args) {
        MPI.Init(args);

        int rank = MPI.COMM_WORLD.rank();
        int size = MPI.COMM_WORLD.size();

        File file = MPI.COMM_WORLD.file_open(
            "/home/nikolay/workspace/trash/WriteReadAll.out", 
            MPI.MODE_CREATE | MPI.MODE_RDWR, MPI.INFO_NULL);
        
        file.size(100);
        file.seek(rank*4, MPI.SEEK_SET);

        int[] buff = new int[4];
        buff[0] = rank;

        file.write_all(buff, 0, 1, MPI.INT, null, null);

        if(rank != 0){
            file.seek(-4, MPI.SEEK_CUR);
        }
        else{
            file.seek((size-1)*4, MPI.SEEK_SET);
        }

        file.read_all(buff, 1, 1, MPI.INT, null, null);

        Utils.sleepRand(300);
        System.out.printf("%d, %d\n", buff[0],buff[1]);
        System.out.flush();
        
        
        file.close();
        MPI.Finalize();
    }
}