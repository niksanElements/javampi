package test;

import java.nio.ByteBuffer;
import java.util.Arrays;

import mpi.Intercomm;
import mpi.Intracomm;
import mpi.MPI;

public class IntercommCollective{
    public static void main(String[] args) {
        int[] a = new int[10];
        int[] b = new int[10];
        ByteBuffer buff = ByteBuffer.allocateDirect(1024);
    
        MPI.Init(null);
        int rank = MPI.COMM_WORLD.rank();
        int color = rank % 2;
        Intracomm scomm = MPI.COMM_WORLD.split(color, rank);
        Intercomm comm = new Intercomm(); 
        comm.create(scomm, 0, MPI.COMM_WORLD, 1-color, 52);
        rank = comm.rank();
        int size = comm.size();
        MPI.buffer_attach(buff);

        System.out.println(rank);
    
        a[0] = rank;

        MPI.COMM_WORLD.gather(a, 0, 1, MPI.INT, b, 0, 1, MPI.INT, 0, null, null);

        if(rank == 0){
            System.out.println(Arrays.toString(b));
        }

        MPI.buffer_detach(buff);
        scomm.free();
        comm.free();
        MPI.Finalize();
    }
}