package test;

import java.util.Arrays;

import mpi.MPI;
import mpi.Request;

public class Sendrecv {
    public static void main(String[] args) {
        MPI.Init(args);

        byte[] sendbuff = new byte[]{
            (byte)0xAA,
            (byte)0x55,
            (byte)0xAA,
            (byte)0x55,
            (byte)0xAA,
            (byte)0x55,
            (byte)0xAA,
            (byte)0x55
        };
        byte[] recvbuff = new byte[8];

        int rank = MPI.COMM_WORLD.rank();
        int size = MPI.COMM_WORLD.size();
        sendbuff[7] = (byte)rank;

        int next_rank = (rank + 1) % size;
        int pre_rank = rank - 1;
        if (pre_rank < 0)
            pre_rank = size - 1;
        Utils.sleepRand(400);
        System.out.printf("%d: %d %d\n",rank,next_rank,pre_rank);
        Request req = MPI.COMM_WORLD.ibarrier();
        req.Wait();
        MPI.COMM_WORLD.sendrecv(sendbuff, 0, 8, MPI.BYTE, 
            pre_rank, 123, null, 
            recvbuff, 0, 8, MPI.BYTE, 
            next_rank, 123, null);
        Utils.sleepRand(500);
        System.out.printf("%d ",rank);
        System.out.println(Arrays.toString(recvbuff));

        MPI.Finalize();
    }
}