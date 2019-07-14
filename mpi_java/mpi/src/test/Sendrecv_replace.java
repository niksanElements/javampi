package test;

import java.util.Arrays;

import mpi.MPI;

public class Sendrecv_replace {
    public static void main(String[] args) {
        MPI.Init(args);


        int rank = MPI.COMM_WORLD.rank();
        int size = MPI.COMM_WORLD.size();

        byte[] sendbuff = new byte[1];
        sendbuff[0] = (byte)rank;

        int next_rank = (rank + 1) % size;
        int pre_rank = rank - 1;
        if (pre_rank < 0)
            pre_rank = size - 1;
        Utils.sleepRand(400);

        System.out.printf("%d: %d %d\n",rank,next_rank,pre_rank);

        MPI.COMM_WORLD.sendrecv_replace(sendbuff, 0, 1, MPI.BYTE, 
            pre_rank, 123, next_rank, 123, null);

        MPI.COMM_WORLD.barrier();
        Utils.sleepRand(500);
        System.out.printf("%d ",rank);
        System.out.println(Arrays.toString(sendbuff));

        MPI.Finalize();
    }
}