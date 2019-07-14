package test;

import mpi.MPI;

public class OpenClosePort {
    public static void main(String[] args) {
        MPI.Init(args);

        String port = MPI.open_port(MPI.INFO_NULL);

        MPI.close_port(port);

        MPI.Finalize();
    }
}