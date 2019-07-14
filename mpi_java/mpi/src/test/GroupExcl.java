package test;

import mpi.Comm;
import mpi.Group;
import mpi.MPI;

public class GroupExcl {
    public static void main(String[] args) {
        MPI.Init(args);

        Group world_group = MPI.COMM_WORLD.group();

        int n = 2;
        int[] ranks = new int[]{1,3};

        Group prime_group = world_group.excl(0, n, ranks);
        Group diff_group = world_group.difference(prime_group);


        Utils.sleepRand(500);

        System.out.printf("%d/%d,%d/%d,%d/%d\n",
            world_group.rank(),world_group.size(),
            prime_group.rank(),prime_group.size(),
            diff_group.rank(),prime_group.size());

        world_group.free();
        prime_group.free();
        diff_group.free();

        MPI.Finalize();
    }
}