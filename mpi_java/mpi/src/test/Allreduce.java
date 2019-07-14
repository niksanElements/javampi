package test;

import mpi.MPI;

public class Allreduce {
    public static void main(String[] args) {
        MPI.Init(args);

        int[] sendbuff = new int[2];
        int[] recvbuff = new int[1];

        int rank = MPI.COMM_WORLD.rank();

        sendbuff[0] = rank;

        MPI.COMM_WORLD.allreduce(sendbuff, recvbuff, 0, 0, 1, MPI.INT, MPI.SUM,null,null);

        System.out.println(recvbuff[0]);

        MPI.Finalize();
    }
}