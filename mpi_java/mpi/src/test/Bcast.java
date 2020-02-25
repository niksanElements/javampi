package test;

import java.util.Arrays;

import mpi.MPI;

public class Bcast {
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

        MPI.COMM_WORLD.bcast(buffer,0,2,MPI.INT,0,null);

        Utils.sleepRand(300);
        boolean check = (buffer[0] == 1 && buffer[1] == 0x55);
        Utils.check(rank, check, "Bcast");

        MPI.Finalize();

    }
}