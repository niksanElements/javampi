package test;

import mpi.File;
import mpi.MPI;
import mpi.Request;

/**
 * FileIWRS
 */
public class FileIWRS {

    public static void main(String[] args) {
        MPI.Init(args);

        int rank = MPI.COMM_WORLD.rank();
        int size = MPI.COMM_WORLD.size();

        File file = MPI.COMM_WORLD.file_open(
            "/home/nikolay/workspace/trash/IWriteReadShared.out", 
            MPI.MODE_CREATE | MPI.MODE_RDWR, MPI.INFO_NULL);
        
        int[] buffer = new int[size*2];
        buffer[0] = rank;
        buffer[1] = rank+20;

        Request req1;

        for(int i = 0;i < size;i++){
            req1 = file.iwrite_shared(buffer, 0, 2, MPI.INT,null);
            req1.Wait();
            MPI.COMM_WORLD.barrier();
        }
        
        file.seek_shared(100, MPI.SEEK_SET);

        Request req = file.iread_shared(buffer, 0, 2, MPI.INT);
        req.Wait();

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