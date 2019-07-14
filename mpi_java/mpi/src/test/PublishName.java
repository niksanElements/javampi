package test;

import mpi.MPI;

public class PublishName {
    public static void main(String[] args) {
        MPI.Init(args);
        int rank = MPI.COMM_WORLD.rank();
     
        /* Note that according to the MPI standard, port_name must have been created by MPI_Open_port. For this example we'll use a fake name. */
        String port_name = "otherhost:122";
        String serv_name = "MyTest";
        if (rank == 0)
        {
            MPI.publish_name(serv_name, MPI.INFO_NULL, port_name);
            MPI.COMM_WORLD.barrier();
            MPI.COMM_WORLD.barrier();
    
            MPI.unpublish_name(serv_name, MPI.INFO_NULL, port_name);
        }
        else
        {
            MPI.COMM_WORLD.barrier();
    
            String port = MPI.lookup_name(serv_name, MPI.INFO_NULL);

            System.out.println(port);
            MPI.COMM_WORLD.barrier();
        }
     
        MPI.Finalize();
    }
}