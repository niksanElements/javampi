package test;

import java.util.Arrays;

import mpi.MPI;

public class DimsCreate {

    /*
    * Test edge cases of Dims_create
    */
    public static int prodof( int ndims, int dims[] )
    {
        int prod=1;
        for (int i=0; i<ndims; i++) 
            prod *= dims[i];
        return prod;
    }
    public static void main(String[] args) {

        int[] dims = new int[4];
        int[] dimsb = new int[4];
    
        MPI.Init(args);
        /* 2 dimensional tests */
        for (int nnodes=1; nnodes <= 32; nnodes = nnodes * 2) {
            dims[0] = 0;
            dims[1] = nnodes;

            dimsb[0] = 0;
            dimsb[1] = nnodes;
    
            MPI.dims_create(nnodes,0, 2, dims);
            if (prodof(2, dims) != nnodes) {
                System.out.printf( "Dims_create returned the wrong decomposition. " );
                System.out.printf( "Is [%d x %d], should be 1 x %d\n", dims[0], dims[1], nnodes );
                System.out.flush();
            }
            System.out.printf("%s %s\n",Arrays.toString(dimsb),Arrays.toString(dims));
            System.out.flush();
    
            /* Try calling Dims_create with nothing to do (all dimensions specified) */
            dims[0] = 1;
            dims[1] = nnodes;

            dimsb[0] = 0;
            dimsb[1] = nnodes;

            MPI.dims_create( nnodes,0, 2, dims );
            if (prodof(2, dims) != nnodes) {
                System.out.printf( "Dims_create returned the wrong decomposition (all given). " );
                System.out.printf( "Is [%d x %d], should be 1 x %d\n", dims[0], dims[1], nnodes );
                System.out.flush();
            }
            System.out.printf("%s %s\n",Arrays.toString(dimsb),Arrays.toString(dims));
            System.out.flush();
        }
    
        /* 4 dimensional tests */
        for (int nnodes=4; nnodes <= 32; nnodes = nnodes * 2) {
            dims[0] = 0;
            dims[1] = nnodes/2;
            dims[2] = 0;
            dims[3] = 2;

            dimsb[0] = 0;
            dimsb[1] = nnodes/2;
            dimsb[2] = 0;
            dimsb[3] = 2;
    
            MPI.dims_create( nnodes,0, 4, dims );
            if (prodof(4, dims) != nnodes) {
                System.out.printf( "Dims_create returned the wrong decomposition. " );
                System.out.printf( "Is [%d x %d x %d x %d], should be 1 x %d x 1 x 2\n", dims[0], dims[1], dims[2], dims[3], nnodes/2 );
                System.out.flush();
            }
            System.out.printf("%s %s\n",Arrays.toString(dimsb),Arrays.toString(dims));
            System.out.flush();
    
            /* Try calling Dims_create with nothing to do (all dimensions specified) */
            dims[0] = 1;
            dims[1] = nnodes/2;
            dims[2] = 1;
            dims[3] = 2;

            dimsb[0] = 0;
            dimsb[1] = nnodes/2;
            dimsb[2] = 0;
            dimsb[3] = 2;

            MPI.dims_create( nnodes,0,2, dims );
            if (prodof(4, dims) != nnodes) {
                System.out.printf( "Dims_create returned the wrong decomposition (all given). " );
                System.out.printf( "Is [%d x %d x %d x %d], should be 1 x %d x 1 x 2\n", dims[0], dims[1], dims[2], dims[3], nnodes/2 );
                System.out.flush();
            }
            System.out.printf("%s %s\n",Arrays.toString(dimsb),Arrays.toString(dims));
            System.out.flush();
        }
    
        MPI.Finalize();
    }
}