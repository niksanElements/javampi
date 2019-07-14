package test;

import java.util.Arrays;

import mpi.MPI;
import mpi.Request;

public class Ibcast {
    public static void main(String[] args) {
        MPI.Init(args);

        int[] buffer = new int[10];

        int rank = MPI.COMM_WORLD.rank();

        if(rank == 0){
            buffer[0] = rank+1;
            buffer[1] = 0x55;
            buffer[2] = 0xAA;
            buffer[3] = 0x55;
            buffer[4] = 0xAA;
            buffer[5] = 0x55;
            buffer[6] = 0xAA;
            buffer[7] = 0x55;
            buffer[8] = 0xBA;
            buffer[9] = 0xCF;
        }

        Request req =  MPI.COMM_WORLD.ibcast(buffer,0,1,MPI.INT,0,null);
        req.Wait();

        Utils.sleepRand(300);
        // buffer[0] = rank;
        System.out.println(Arrays.toString(buffer));

        MPI.Finalize();
    }
}