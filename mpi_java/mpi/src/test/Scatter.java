package test;

import java.util.Arrays;

import mpi.MPI;

public class Scatter {
    public static void main(String[] args) {
        MPI.Init(args);

        int[] buffer = new int[10];
        int[] recvBuff = new int[1];

        int rank = MPI.COMM_WORLD.rank();

        if(rank == 0){
            buffer[1] = 0;
            buffer[2] = 1;
            buffer[3] = 2;
            buffer[4] = 3;
            buffer[5] = 4;
            buffer[6] = 5;
            buffer[7] = 6;
            buffer[8] = 7;
            buffer[9] = 8;
        }

        MPI.COMM_WORLD.scatter(buffer, 0, 1, MPI.INT, 
            recvBuff, 0, 1, MPI.INT, 0, 
            null, null);

        Utils.sleepRand(300);
        // buffer[0] = rank;
        System.out.printf("%d %s\n",rank,Arrays.toString(recvBuff));

        MPI.Finalize();

    }
}