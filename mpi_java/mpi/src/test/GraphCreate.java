package test;

import java.util.Arrays;

import mpi.Cart;
import mpi.Graph;
import mpi.Intracomm;
import mpi.MPI;

public class GraphCreate {
    public static void main(String[] args) {

        int[] dims = new int[2];
        int[] periods = new int[2];
        int[] outdims = new int[2];
        int[] outperiods = new int[2];
        int[] outcoords = new int[2];

        MPI.Init(args);
        int wsize = MPI.COMM_WORLD.size();
    
        /* Create a cartesian topology, get its characteristics, then 
            dup it and check that the new communicator has the same properties */
        dims[0] = 0;
        dims[1] = 0;
        MPI.dims_create(wsize,0,2,dims);
        periods[0] = 0;
        periods[1] = 0;
        Cart comm1 = MPI.COMM_WORLD.cart_create(0, 2, dims, 0, periods, false);
        Cart comm2 = comm1.dup();

        int topo_type = comm2.topo_test();
        if (topo_type != MPI.CART) {
            System.out.println("Topo type of duped cart was not cart.");
            System.out.flush();
        }
        else {
            comm2.get(0,2, outdims,0, outperiods,0, outcoords);
            for (int i=0; i<2; i++) {
                if (outdims[i] != dims[i]) {
                    System.out.printf( "%d = outdims[%d] != dims[%d] = %d\n", outdims[i], i, i, dims[i] );
                    System.out.flush();
                }
                if (outperiods[i] != periods[i]) {
                    System.out.printf( "%d = outperiods[%d] != periods[%d] = %d\n", 
                        outperiods[i], i, i, periods[i] );
                    System.out.flush();
                }
            }
        }
        comm1.free();
        comm2.free();
    
        /* Now do the same with a graph topology */
        if (wsize >= 3) {
            int[] index = new int[wsize];
            int[] edges = new int[2*wsize];
            index[0] = 2;
            for (int i=1; i<wsize; i++) {
                index[i] = 2 + index[i-1];
            }
            int k=0;
            for (int i=0; i<wsize; i++) {
                edges[k++] = (i-1+wsize) % wsize;
                edges[k++] = (i+1) % wsize;
            }
            Graph comm1_graph = MPI.COMM_WORLD.graph_create(0,wsize, index,0,edges,false);
            Graph comm2_graph = comm1_graph.dup();

            int[] neighbors = new int[5];

            int rank = comm1_graph.rank();
            int countneighbors = comm1_graph.neighbors_count(rank);
            comm1_graph.neighbors(rank, 0, 5, neighbors);
            System.out.printf("%d %d %s\n",rank,countneighbors,Arrays.toString(neighbors));

            topo_type = comm2_graph.topo_test();
            if (topo_type != MPI.GRAPH) {
                System.out.println( "Topo type of duped graph was not graph." );
                System.out.flush();
            }
            else {
                int nnodes = comm2_graph.nnodes();
                int nedges = comm2_graph.nedges();

                if (nnodes != wsize) {
                    System.out.printf( "Nnodes = %d, should be %d\n", nnodes, wsize );
                    System.out.flush();
                }
                if (nedges != 2*wsize) {
                    System.out.printf( "Nedges = %d, should be %d\n", nedges, 2*wsize );
                    System.out.flush();
                }
                int[] outindex = new int[wsize];
                int[] outedges = new int[2*wsize];
    
                comm2_graph.get(0,wsize,0, 2*wsize, outindex, outedges );
                for (int i=0; i<wsize; i++) {
                    if (index[i] != outindex[i]) {
                        System.out.printf( "%d = index[%d] != outindex[%d] = %d\n", index[i], i, i, 
                            outindex[i] );
                        System.out.flush();
                    }
                }
                for (int i=0; i<2*wsize; i++) {
                    if (edges[i] != outedges[i]) {
                        System.out.printf( "%d = edges[%d] != outedges[%d] = %d\n", edges[i], i, 
                            i, outedges[i] );
                        System.out.flush();
                    }
                }
            }
            comm2_graph.free();
            comm1_graph.free();
        }
    
        MPI.Finalize();
    }
}