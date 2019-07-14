package test;

import java.nio.ByteBuffer;
import java.util.Random;

import mpi.MPI;
import mpi.Request;

public class Send_init {
    public static void main(String[] args) {
        MPI.Init(args);

        ByteBuffer buff = ByteBuffer.allocateDirect(1024);
        int rank = MPI.COMM_WORLD.rank();

        if(rank == 0){
            System.out.println("Send started ...");
            Request request = MPI.COMM_WORLD.send_init(buff, 
                0, 40, MPI.BYTE_BUFFER, 1, 0);
            Random rand =  new Random();

            for(int i = 0;i < 20;i++){
                buff.position(0);
                buff.limit(buff.capacity());

                buff.putInt(0, 0x55AA55AA);
                buff.putInt(4,i);
                buff.putInt(9,rand.nextInt());
                
                request.start();
                request.Wait();
            }
            request.free();

        }
        else if(rank == 1){
            System.out.println("Receive started ...");
            Request request = MPI.COMM_WORLD.recv_init(buff, 
                0, 40, MPI.BYTE_BUFFER, 0, 0);

            for(int i = 0;i < 20;i++){                
                request.start();
                request.Wait();
                buff.position(0);
                buff.limit(buff.capacity());
                System.out.printf("0x%x ",buff.getInt(0));
                System.out.printf("0x%x ",buff.getInt(4));
                System.out.printf("0x%x\n",buff.getInt(9));
            }
            request.free();
        }

        MPI.Finalize();
    }
}