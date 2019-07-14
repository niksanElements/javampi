package test;

import mpi.MPI;
import mpi.Request;

public class Iscan {
    public static void main(String[] args) {
        MPI.Init(args);

        int[] sendbuff = new int[2];
        int[] recvbuff = new int[1];

        int rank = MPI.COMM_WORLD.rank();

        sendbuff[0] = rank;

        Request req =  MPI.COMM_WORLD.iscan(sendbuff, recvbuff, 0, 0, 1, MPI.INT, MPI.SUM,null,null);

        req.Wait();

        System.out.println(recvbuff[0]);

        MPI.Finalize();
    }
}