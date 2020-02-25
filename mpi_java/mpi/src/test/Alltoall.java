package test;

import java.util.Arrays;

import mpi.MPI;

public class Alltoall {
    public static void main(String[] args) {
        MPI.Init(args);

        int[] buffer = new int[10];
        int[] recvBuff = new int[10];

        int rank = MPI.COMM_WORLD.rank();

        for(int i = 0;i < 10;i++){
            buffer[i] = rank*rank+1;
        }

        System.out.printf("%d %s\n",rank,Arrays.toString(buffer));

        long start = System.nanoTime();
        MPI.COMM_WORLD.alltoall(buffer, 0, 1, MPI.INT, 
            recvBuff, 0, 1, MPI.INT,
            null, null);
        long end = System.nanoTime();

        System.out.printf("%f\n",(end-start)/1000000.0);

        boolean check = true;

        for(int i = 0;i < 10 && check;i++){
            int value = i*i+1;
            if(value != recvBuff[i]){
                check = false;
            }
        }

        Utils.check(rank, check, "Alltoall");

        MPI.Finalize();
    }
}