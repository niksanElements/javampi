package test;

import java.util.Arrays;

import mpi.MPI;
import mpi.Message;
import mpi.Status;

public class Mrecv {
    public static void main(String[] args) {
        MPI.Init(args);
        int rank = MPI.COMM_WORLD.rank();
        if(rank == 0){
            System.out.println("rank 0");
            long start = System.nanoTime();
            MPI.COMM_WORLD.send(new byte[] {0x11,0x22}, 0, 2, MPI.BYTE, 1, 0,null);
            long end = System.nanoTime();
            System.out.println((end-start)/1000000.0);
        }
        else if(rank == 1){
            System.out.println("rank 1");
            byte buff[] = new byte[2];
            Message msg = MPI.COMM_WORLD.mprobe(0, 0);
            long start = System.nanoTime();
            Status stat = msg.mrecv(buff, 0, 2, MPI.BYTE,null);
            long end = System.nanoTime();
            System.out.println((end-start)/1000000.0);
            System.out.println(Arrays.toString(buff));
            System.out.println(stat.count(MPI.BYTE));
        }

        MPI.Finalize();
    }
}