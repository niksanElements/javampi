package test;


import mpi.Group;
import mpi.MPI;

public class CommGroup {
    public static void main(String[] args) {
        MPI.Init(args);

        Group world_group = MPI.COMM_WORLD.group();

        int comm_rank = MPI.COMM_WORLD.rank();
        int comm_size = MPI.COMM_WORLD.size();

        int group_rank = world_group.rank();
        int group_size = world_group.size();

        Utils.sleepRand(500);

        System.out.printf("%d/%d,%d/%d\n",comm_rank,comm_size,group_rank,group_size);

        world_group.free();

        MPI.Finalize();
    }
}