package test;

import mpi.MPI;

public class Reduce {
    public static void main(String[] args) {
        MPI.Init(args);

        int[] sendbuff = new int[2];
        int[] recvbuff = new int[1];

        int rank = MPI.COMM_WORLD.rank();

        sendbuff[0] = rank;

        MPI.COMM_WORLD.reduce(sendbuff, recvbuff, 0, 0, 1, MPI.INT, MPI.SUM, 0,null,null);

        if(rank == 0){
            System.out.println(recvbuff[0]);
        }

        MPI.Finalize();
    }
}