package test;

import java.util.Arrays;

import mpi.MPI;
import mpi.Request;

public class Igather {
    public static void main(String[] args) {
        MPI.Init(args);

        int[] buffer = new int[1];
        int[] recvBuff = new int[10];

        int rank = MPI.COMM_WORLD.rank();

        buffer[0] = rank+1;

        Request req =  MPI.COMM_WORLD.igather(buffer, 0, 1, MPI.INT, 
            recvBuff, 0, 1, MPI.INT, 0, 
            null, null);
        req.Wait();
        Utils.sleepRand(300);
        // buffer[0] = rank;
        if(rank == 0){
            System.out.printf("%d %s\n",rank,Arrays.toString(recvBuff));
        }

        MPI.Finalize();
    }
}