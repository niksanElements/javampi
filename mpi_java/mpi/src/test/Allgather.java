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
        MPI.COMM_WORLD.allgather(buffer, 0, 1, MPI.INT, 
            recvBuff, 0, 1, MPI.INT,
            null, null);

        // System.out.printf("%f\n",(end-start)/1000000.0);

        boolean check = true;

        for(int i = 0;i < recvBuff.length && check;i++){
            if(recvBuff[i] != i+1){
                check = false;
            }
        }

        Utils.check(rank,check,"Allgather");

        MPI.Finalize();
    }
}