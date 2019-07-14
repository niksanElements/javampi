package test;

import java.nio.ByteBuffer;

import mpi.MPI;
import mpi.Status;
import mpi.datatype.Datatype;

public class ByteBufferTest {
    public static void main(String[] args) {
        MPI.Init(args);
        int rank = MPI.COMM_WORLD.rank();
        ByteBuffer buff = Datatype.allocBuff(128);

        if(rank == 0){
            System.out.println("rank 0");
            buff.put(0,(byte)0x11);
            buff.put(1,(byte)0x22);
            long start = System.nanoTime();
            MPI.COMM_WORLD.send(buff, 1, 2, MPI.BYTE_BUFFER, 1, 0,null);
            long end = System.nanoTime();
            System.out.println((end-start)/1000000.0);
        }
        else if(rank == 1){
            System.out.println("rank 1");
            long start = System.nanoTime();
            Status stat = MPI.COMM_WORLD.recv(buff, 1, 2, MPI.BYTE_BUFFER, 0, 0,null);
            long end = System.nanoTime();
            System.out.println((end-start)/1000000.0);
            buff.position(0);
            System.out.printf("%d %d %d\n",
                buff.get(),buff.get(),buff.get());
        }

        MPI.Finalize();
    }
}