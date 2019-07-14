package test;

import mpi.File;
import mpi.MPI;

/**
 * FileWriteReadAt
 */
public class FileWriteReadAt {

    public static void main(String[] args) {
        MPI.Init(args);

        int rank = MPI.COMM_WORLD.rank();
        int size = MPI.COMM_WORLD.size();

        File file = MPI.COMM_WORLD.file_open("/home/nikolay/workspace/trash/WriteReadAt.out", 
            MPI.MODE_RDWR, MPI.INFO_NULL);
        
        int[] buffer = new int[size*2];
        buffer[0] = rank;
        buffer[1] = rank+20;

        file.write_at(rank*8, buffer, 0, 2, MPI.INT, null, null);

        if(rank == 0){
            for(int i = 0;i < size*2;i += 2){
                file.read_at(i*4, buffer, 0, 2, MPI.INT, null, null);

                System.out.printf("(%d,%d)",buffer[0],buffer[1]);
            }
        }

        MPI.COMM_WORLD.barrier();

        file.close();

        MPI.Finalize();

    }
}