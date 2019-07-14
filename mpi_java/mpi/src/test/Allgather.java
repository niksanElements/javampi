package test;

import java.util.Arrays;

import mpi.MPI;

public class Allgather {
    public static void main(String[] args) {
        MPI.Init(args);

        int[] buffer = new int[1];
        int[] recvBuff = new int[10];

        int rank = MPI.COMM_WORLD.rank();

        buffer[0] = rank+1;
        long start = System.nanoTime();
        MPI.COMM_WORLD.allgather(buffer, 0, 1, MPI.INT, 
            recvBuff, 0, 1, MPI.INT,
            null, null);
        long end = System.nanoTime();

        System.out.printf("%f\n",(end-start)/1000000.0);

        Utils.sleepRand(300);
        // buffer[0] = rank;
        System.out.printf("%d %s\n",rank,Arrays.toString(recvBuff));

        MPI.Finalize();
    }
}