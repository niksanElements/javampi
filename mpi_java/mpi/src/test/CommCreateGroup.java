package test;

import mpi.Comm;
import mpi.Group;
import mpi.MPI;

public class CommCreateGroup {
    public static void main(String[] args) {
        MPI.Init(args);

        int world_rank = MPI.COMM_WORLD.rank();
        int world_size = MPI.COMM_WORLD.size();

        Group world_group = MPI.COMM_WORLD.group();

        int n = 5;
        int[] ranks = new int[]{1,3,5,7,9};

        Group prime_group = world_group.incl(0, n, ranks);

        Comm comm = MPI.COMM_WORLD.create(prime_group, 0);

        int prime_rank = -1, prime_size = -1;
        int comm_result = -1;
        if(!comm.isNull()){
            prime_rank = comm.rank();
            prime_size = comm.size();
            comm_result = MPI.COMM_WORLD.compare(comm);
        }

        Utils.sleepRand(500);
        System.out.printf("compare res: %d\n",comm_result);
        System.out.printf("%d/%d,%d/%d\n",world_rank,world_size,prime_rank,prime_size);

        world_group.free();
        prime_group.free();
        comm.free();

        MPI.Finalize();
    }
}