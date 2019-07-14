package test;

import java.util.Arrays;

import mpi.Cart;
import mpi.Intracomm;
import mpi.MPI;

public class CartCreate{
    public static void main(String[] args) {
        MPI.Init(args);
        int rank = MPI.COMM_WORLD.rank();
        int size = MPI.COMM_WORLD.size();
        if (size != 12)
        {
            System.out.println("Please run with 12 processes.");
            System.out.flush();
            MPI.COMM_WORLD.abort(1);
        }
        int[] dim = new int[2];
        int[] period = new int[2];

        dim[0]=4; dim[1]=3;
        period[0]=1; period[1]=0;
        int[] coord = new int[2];
        boolean reorder = true;
        Cart comm = MPI.COMM_WORLD.cart_create(0,2, dim,0, period, reorder);
        if (rank == 11)
        {
            comm.coords(rank,0, 2, coord);
            System.out.printf("Rank %d coordinates are %d %d\n", rank, coord[0], coord[1]);
            System.out.flush();

            comm.send(new int[] {1,2,3,4}, 0, 4, MPI.INT, 0, 0, null);
        }
        if(rank==0)
        {
            coord[0]=3; coord[1]=1;
            int id = comm.rank(0,2,coord);
            System.out.printf("The processor at position (%d, %d) has rank %d\n", coord[0], coord[1], id);
            System.out.flush();

            int[] recv = new int[4];
            comm.recv(recv, 0, 4, MPI.INT, 11, 0, null);
            System.out.println(Arrays.toString(recv));
        }
        MPI.Finalize();
    }
}