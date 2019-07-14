package test;

import mpi.Comm;
import mpi.Intracomm;
import mpi.MPI;

public class CommDup{
    public static void main(String[] args) {
        MPI.Init(args);

        int rank = MPI.COMM_WORLD.rank();
        int size = MPI.COMM_WORLD.size();

        Comm comm = MPI.COMM_WORLD.dup();

        int split_rank = comm.rank();
        int split_size = comm.size();

        Utils.sleepRand(600);
        System.out.printf("%d/%d,%d/%d\n",rank,size,split_rank,split_size);
        comm.free();

        MPI.Finalize();
    }
}