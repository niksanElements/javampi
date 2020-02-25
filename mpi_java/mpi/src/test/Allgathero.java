package test;

import java.nio.ByteBuffer;

import mpi.MPI;
import mpi.datatype.Datatype;
import test.types.Here;

public class Allgathero {
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
        Here[] hSend = new Here[2];
        Here[] hRecv = new Here[10];

        hSend[0] = new Here();
        hSend[0].setId(rank+1);
        hSend[0].setId2(rank*rank);
        
        ByteBuffer buff = ByteBuffer.allocateDirect(124);
        ByteBuffer buff1 =ByteBuffer.allocateDirect(124);
        MPI.COMM_WORLD.allgather(hSend, 0, 1, her, hRecv, 0, 1, her, buff, buff1);

        boolean check = true;

        for(int i = 0;i < hRecv.length && check;i++){
            if(hRecv[i].getId() != i+1 && hRecv[i].getId2() != (i+1)*(i+1)){
                check = false;
            }
        }

        Utils.check(rank,check,"Allgathero");

        MPI.Finalize();
    }
}