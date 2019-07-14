package test;

import mpi.File;
import mpi.MPI;

/**
 * FileWriteReadShared
 */
public class FileWriteReadShared {

    public static void main(String[] args) {
        MPI.Init(args);

        int rank = MPI.COMM_WORLD.rank();
        int size = MPI.COMM_WORLD.size();

        File file = MPI.COMM_WORLD.file_open(
            "/home/nikolay/workspace/trash/WriteReadShared.out", 
            MPI.MODE_CREATE | MPI.MODE_RDWR, MPI.INFO_NULL);
        
        int[] buffer = new int[size*2];
        buffer[0] = rank;
        buffer[1] = rank+20;

        for(int i = 0;i < size;i++){
            file.write_shared(buffer, 0, 2, MPI.INT, null, null);
            MPI.COMM_WORLD.barrier();
        }
        
        file.seek_shared(100, MPI.SEEK_SET);

        file.read_shared(buffer, 0, 2, MPI.INT, null, null);

        System.out.printf("%d,%d\n",buffer[0],buffer[1]);

        Utils.sleepRand(300);
        System.out.printf("(%d,%d)\n",rank,file.position_shared());
        System.out.flush();
        System.out.printf("(%d,%d)\n",rank,file.position());
        System.out.flush();

        file.close();

        MPI.Finalize();
    }
}