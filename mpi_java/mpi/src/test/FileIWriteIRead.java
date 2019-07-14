package test;

import mpi.File;
import mpi.MPI;
import mpi.Request;

/**
 * FileIWriteIRead
 */
public class FileIWriteIRead {

    public static void main(String[] args) {
        MPI.Init(args);

        int[] buff = new int[1000];

        int rank = MPI.COMM_WORLD.rank();
        File fh = MPI.COMM_WORLD.file_open("/home/nikolay/workspace/test12.out", 
            MPI.MODE_CREATE|MPI.MODE_RDWR, MPI.INFO_NULL);

        if(rank == 0){
            buff[0] = rank+1;
            buff[1] = rank+2;
            Request req = fh.iwrite(buff, 0, 2, MPI.INT, null);

            req.Wait();
        }

        System.out.println(rank);
        System.out.flush();

        MPI.COMM_WORLD.barrier();

        if(rank == 2){
            Request req = fh.iread(buff, 0, 2, MPI.INT);
            System.out.println(rank);
            System.out.flush();
            req.Wait();

            System.out.printf("%d, %d\n",buff[0],buff[1]);
            System.out.flush();
        }

        System.out.println(rank);
        System.out.flush();

        MPI.COMM_WORLD.barrier();
        fh.close();


        MPI.Finalize();
    }
}