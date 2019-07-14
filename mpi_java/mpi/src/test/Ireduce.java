package test;

import mpi.MPI;
import mpi.Request;

public class Ireduce {
    public static void main(String[] args) {
        MPI.Init(args);

        int[] sendbuff = new int[2];
        int[] recvbuff = new int[1];

        int rank = MPI.COMM_WORLD.rank();

        sendbuff[0] = rank;

        Request req =  MPI.COMM_WORLD.ireduce(sendbuff, recvbuff, 0, 0, 1, MPI.INT, MPI.SUM, 0,null,null);

        req.Wait();

        if(rank == 0){
            System.out.println(recvbuff[0]);
        }

        MPI.Finalize();
    }
}