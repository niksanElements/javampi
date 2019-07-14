package test;

import java.nio.ByteBuffer;

import mpi.MPI;
import mpi.datatype.Datatype;
import test.types.Here;

public class Scattero {
    static String[] h_hapes = {
            "Id"
    };
    static Datatype[] h_types = {
            MPI.INT
    };
    static int[] h_counts = {
            1
    };

    static Datatype her = new Datatype(h_hapes, h_types, h_counts, Here.class);

    public static void main(String[] args) {
        MPI.Init(args);

        Datatype.commit(her);
        int rank = MPI.COMM_WORLD.rank();
        Here[] hSend = new Here[10];
        Here[] hRecv = new Here[3];

        if(rank == 0){
            for(int i = 0;i < 10;i++){
                hSend[i] = new Here();
                hSend[i].setId(i);
            }
        }
        ByteBuffer buff = ByteBuffer.allocateDirect(124);
        ByteBuffer buff1 =ByteBuffer.allocateDirect(124);
        long start = System.nanoTime();
        MPI.COMM_WORLD.scatter(hSend, 0, 1, her, hRecv, 0, 1, her, 0, buff, buff1);
        long end = System.nanoTime();

        Utils.sleepRand(500);
        System.out.printf("%f\n", (end-start)/1000000.0);

        System.out.println(hRecv[0].getId());

        MPI.Finalize();
    }
}