package test;

import mpi.Cart;
import mpi.MPI;

public class CartSub {
    public static void main(String[] args) {
        MPI.Init(args);

        int[] periods = new int[3];
        int[] dims = new int[3];
        int[] remain = new int[3];

        /* First, create a 1-dim cartesian communicator */
        periods[0] = 0;
        periods[1] = 1;
        int size = MPI.COMM_WORLD.size();
        dims[0] = 5;
        dims[1] = 2;
        Cart comm = MPI.COMM_WORLD.cart_create(0, 2, dims, 0, periods, false);
    
        /* Now, extract a communicator with no dimensions */
        remain[0] = 0;
        remain[1] = 1;
        Cart newcomm = comm.sub(0,remain);

        int ndims = comm.dims();
        System.out.printf("dims: %d\n",ndims);
        System.out.flush();
    
        /* This should be congruent to MPI_COMM_SELF */
        if(!newcomm.isNull()){
            int result = MPI.COMM_SELF.compare(newcomm);
            if (result != MPI.CONGRUENT) {
                System.out.printf( "COMM_SELF compare: %d\n",result);
                System.out.flush();
            }
            int rank = MPI.COMM_WORLD.rank();
            System.out.printf("%d\n",rank);
            System.out.flush();
        }
    
        /* Free the new communicator */
        newcomm.free();
        comm.free();
    
        MPI.Finalize();
    }
}