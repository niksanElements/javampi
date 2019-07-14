package test;

import java.util.Arrays;

import mpi.Comm;
import mpi.Group;
import mpi.MPI;

public class GroupTranslate {
    public static void main(String[] args) {
        MPI.Init(args);

        Group world_group = MPI.COMM_WORLD.group();

        int n = 2;
        int[] ranks = new int[]{1,3};

        Group prime_group = world_group.incl(0, n, ranks);
        Group diff_group = world_group.union(prime_group);

        int[] trans_ranks = new int[2];
        ranks[0] = 0;
        diff_group.translate_ranks(0, n, ranks, prime_group, 0, trans_ranks);

        Utils.sleepRand(500);

        System.out.println(Arrays.toString(trans_ranks));

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