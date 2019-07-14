package test;

import mpi.Cart;
import mpi.MPI;

public class CartShift {

    public static int DIMS = 2;

    public static void main(String[] args) {
        MPI.Init(args);
        int size = MPI.COMM_WORLD.size();
        int rank = MPI.COMM_WORLD.rank();

        int[] dims = new int[DIMS];
        int[] periods = new int[DIMS];
    
        dims[0] = size;
        periods[0] = 1;

        Cart comm = MPI.COMM_WORLD.cart_create(0, 1, dims, 0, periods, false);
        int source = comm.source(0, 1);
        int dest = comm.dest(0, 1);
        if (source != ((rank - 1 + size) % size)) {
            System.out.printf( "source for shift 1 is %d\n", source );
            System.out.flush();
        }
        if (dest != ((rank + 1) % size)) {
            System.out.printf( "dest for shift 1 is %d\n", dest );
            System.out.flush();
        }
        source = comm.source(0, 0);
        dest = comm.dest(0, 0);

        if (source != rank) {
            System.out.printf( "Source for shift 0 is %d\n", source );
            System.out.flush();
        }
        if (dest != rank) {
            System.out.printf( "Dest for shift 0 is %d\n", dest );
            System.out.flush();
        }
        source = comm.source(0, -1);
        dest = comm.dest(0, -1);
        if (source != ((rank + 1) % size)) {
            System.out.printf( "source for shift -1 is %d\n", source );
            System.out.flush();
        }
        if (dest != ((rank - 1 + size) % size)) {
            System.out.printf( "dest for shift -1 is %d\n", dest );
            System.out.flush();
        }
    
        /* Now, with non-periodic */
        comm.free();
        periods[0] = 0;
        comm = MPI.COMM_WORLD.cart_create(0, 1, dims,0, periods, false);
        source = comm.source(0, 1);
        dest = comm.dest(0, 1);
        if ((rank > 0 && source != (rank - 1)) || (rank == 0 && source != MPI.PROC_NULL)) {
            System.out.printf( "source for non-periodic shift 1 is %d\n", source );
            System.out.flush();
        }
        if ((rank < size-1 && dest != rank + 1) || ((rank == size-1) && dest != MPI.PROC_NULL)) {
            System.out.printf( "dest for non-periodic shift 1 is %d\n", dest );
            System.out.flush();
        }
        source = comm.source(0, 0);
        dest = comm.dest(0, 0);
        if (source != rank) {
            System.out.printf( "Source for non-periodic shift 0 is %d\n", source );
            System.out.flush();
        }
        if (dest != rank) {
            System.out.printf( "Dest for non-periodic shift 0 is %d\n", dest );
            System.out.flush();
        }
        source = comm.source(0, -1);
        dest = comm.dest(0, -1);
        if ((rank < size - 1 && source != rank + 1) || (rank == size - 1 && source != MPI.PROC_NULL)) {
            System.out.printf( "source for non-periodic shift -1 is %d\n", source );
            System.out.flush();
        }
        if ((rank > 0 && dest != rank - 1) || (rank == 0 && dest != MPI.PROC_NULL)) {
            System.out.printf( "dest for non-periodic shift -1 is %d\n", dest );
            System.out.flush();
        }
        
        comm.free();
    
        MPI.Finalize();
    }
}