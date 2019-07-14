package test;

import java.nio.ByteBuffer;
import java.util.Arrays;

import mpi.MPI;
import mpi.Request;
import mpi.datatype.Datatype;
import test.types.Here;

public class Iscattero {
    static String[] h_hapes = {
        "Id",
        "Id2"
    };
    static Datatype[] h_types = {
            MPI.INT,MPI.INT
    };
    static int[] h_counts = {
            1,1
    };

    static Datatype here = new Datatype(h_hapes, h_types, h_counts, Here.class);

    public static void main(String[] args) {
        MPI.Init(args);

        Datatype.commit(here);

        Here[] buffer = new Here[10];
        Here[] recvBuff = new Here[1];

        int rank = MPI.COMM_WORLD.rank();

        if(rank == 0){
            for(int i = 0;i < 10;i++){
                buffer[i] = new Here();
                buffer[i].setId(i);
                buffer[i].setId2(i*i);
            }
        }

        ByteBuffer bufferRecv = ByteBuffer.allocateDirect(1024);
        ByteBuffer bufferSend = ByteBuffer.allocateDirect(1024);

        Request req = MPI.COMM_WORLD.iscatter(buffer, 0, 1, here, 
            recvBuff, 0, 1, here, 0, 
            null,bufferRecv);

        req.wait(recvBuff, 0, 1, here, bufferRecv);
        // int id = bufferRecv.getInt(0);
        // System.out.print(id);

        Utils.sleepRand(300);
        // buffer[0] = rank;
        System.out.printf("%d Id: %d Id2: %d\n",rank,recvBuff[0].getId(),recvBuff[0].getId2());

        MPI.Finalize();
    }
}