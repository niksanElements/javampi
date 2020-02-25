package test;

import java.nio.ByteBuffer;

import mpi.MPI;
import mpi.datatype.Datatype;
import test.types.Here;

public class Alltoallo {
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
            hSend[i].setId(rank+rank);
            hSend[i].setId2((rank*rank));
        }
        
        ByteBuffer buff = ByteBuffer.allocateDirect(124);
        ByteBuffer buff1 =ByteBuffer.allocateDirect(124);
        long start = System.nanoTime();
        MPI.COMM_WORLD.alltoall(hSend, 0, 1, her, hRecv, 0, 1, her, buff, buff1);
        long end = System.nanoTime();
    
        System.out.printf("%f\n", (end-start)/1000000.0);
        boolean check = true;
        for(int i = 0;i < 10 && check;i++){
            int value_id = i+i;
            int value_id2 = i*i;
            
            if(value_id != hRecv[i].getId() || value_id2 != hRecv[i].getId2()){
                check = false;
            }
        }

        Utils.check(rank, check, "Alltoallo");

        MPI.Finalize();
    }
}