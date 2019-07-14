package test;

import mpi.Comm;
import mpi.Intracomm;
import mpi.MPI;

public class CommSplit{
    public static void main(String[] args) {
        MPI.Init(args);

        int rank = MPI.COMM_WORLD.rank();
        int size = MPI.COMM_WORLD.size();

        int color = rank/4;

        Comm comm = MPI.COMM_WORLD.split(color, rank);

        int split_rank = comm.rank();
        int split_size = comm.size();

        Utils.sleepRand(600);
        System.out.printf("Rank:%d Size %d,Split Rank: %d Split Size: %d\n",rank,size,split_rank,split_size);
        comm.free();

        MPI.Finalize();
    }
}