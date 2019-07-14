package test;

import java.util.Arrays;

import mpi.MPI;
import mpi.Request;

public class Ialltoall {
    public static void main(String[] args) {
        MPI.Init(args);

        int[] buffer = new int[10];
        int[] recvBuff = new int[10];

        int rank = MPI.COMM_WORLD.rank();

        for(int i = 0;i < 10;i++){
            buffer[i] = rank*rank*i+1;
        }

        System.out.printf("%d %s\n",rank,Arrays.toString(buffer));

        long start = System.nanoTime();
        Request req =  MPI.COMM_WORLD.ialltoall(buffer, 0, 1, MPI.INT, 
            recvBuff, 0, 1, MPI.INT,
            null, null);
        long end = System.nanoTime();

        req.Wait();

        System.out.printf("%f\n",(end-start)/1000000.0);

        Utils.sleepRand(300);
        // buffer[0] = rank;
        System.out.printf("%d %s\n",rank,Arrays.toString(recvBuff));

        MPI.Finalize();
    }
}