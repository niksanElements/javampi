package test;

import java.nio.ByteBuffer;

import mpi.MPI;
import mpi.Request;
import mpi.datatype.Datatype;
import test.types.Here;

public class Ialltoallo {
    static String[] h_hapes = {
            "Id","Id2"
    };
    static Datatype[] h_types = {
            MPI.INT,MPI.INT
    };
    static int[] h_counts = {
        1,1
    };

    static Datatype her = new Datatype(h_hapes, h_types, h_counts, Here.class);

    public static void main(String[] args) {
        MPI.Init(args);

        Datatype.commit(her);
        int rank = MPI.COMM_WORLD.rank();
        Here[] hSend = new Here[10];
        Here[] hRecv = new Here[10];

        for(int i = 0;i < 10;i++){
            hSend[i] = new Here();
            hSend[i].setId(rank+1);
            hSend[i].setId2((rank*rank)+i);
        }
        
        ByteBuffer buff = ByteBuffer.allocateDirect(124);
        ByteBuffer buff1 =ByteBuffer.allocateDirect(124);
        long start = System.nanoTime();
        Request req =  MPI.COMM_WORLD.ialltoall(hSend, 0, 1, her, hRecv, 0, 1, her, buff, buff1);
        long end = System.nanoTime();
    
        System.out.printf("%f\n", (end-start)/1000000.0);
        Utils.sleepRand(500);
        req.wait(hRecv, 0, 10, her, buff1);
        System.out.println(hRecv[0].getId());
        for(int i = 0;i < 10;i++){
            System.out.printf("%d, ID: %d ID2: %d\n",i,hRecv[i].getId(),hRecv[i].getId2());
        }

        MPI.Finalize();
    }
}