package test;

import java.util.Arrays;

import mpi.Intracomm;
import mpi.MPI;

public class DistGraphCreate {
    public static void main(String[] args) {
        MPI.Init(args);

        int[] sources = {1,2,7};
        int[] degrees = {2,2,2};
        int[] destinations = {4,5,7,8,9,6};
        int[] weights = {1,2,3,4,5,6};

        Intracomm graph = MPI.COMM_WORLD.dist_graph_create(0, 3, sources, 0, degrees, 0, 
            destinations, 0, weights, MPI.INFO_NULL, false);
        Intracomm graphcpy = graph.dup();


        int rank = graph.rank();

        if(rank == 1){
            int type = graph.topo_test();
            System.out.println(type);
            graphcpy.send(new int[]{1,2,4}, 0, 3, MPI.INT, 3, 0, null);
        }
        else if (rank == 3){
            int[] recv = new int[3];
            graphcpy.recv(recv, 0, 3, MPI.INT, 1, 0, null);
            System.out.println(Arrays.toString(recv));
        }

        graph.free();

        MPI.Finalize();
    }
}