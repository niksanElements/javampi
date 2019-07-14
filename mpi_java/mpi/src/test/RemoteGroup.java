package test;

import java.nio.ByteBuffer;
import java.util.Arrays;

import mpi.Group;
import mpi.Intercomm;
import mpi.Intracomm;
import mpi.MPI;

public class RemoteGroup{
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

        System.out.printf("rank: %d, size:%d\n",rank,size);
    
        for (int j=0; j<10; j++) {
            for (int i=0; i<10; i++) {
                a[i] = (rank + 10 * j) * size + i;
            }
            comm.bsend(a, 0, 10, MPI.INT, 0, 27+j, null);
        }
        if (rank == 0) {
            for (int i=0; i<size; i++) {
                for (int j=0; j<10; j++) {
                    comm.recv(b, 0, 10, MPI.INT, i, 27+j, null);

                    System.out.printf("%d %d %s\n",i,27+j,Arrays.toString(b));
                }
            }
        }

        Group remote_group = comm.remote_group();
        Utils.sleepRand(400);
        rank = remote_group.rank();
        size = remote_group.size();

        System.out.printf("rank: %d, size:%d\n",rank,size);


        MPI.buffer_detach(buff);
        scomm.free();
        comm.free();
        remote_group.free();
        MPI.Finalize();
    }
}