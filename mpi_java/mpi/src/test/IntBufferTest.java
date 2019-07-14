package test;

import java.nio.ByteBuffer;
import java.nio.IntBuffer;

import mpi.MPI;
import mpi.Status;
import mpi.datatype.Datatype;

public class IntBufferTest {
    public static void main(String[] args) {
        MPI.Init(args);
        int rank = MPI.COMM_WORLD.rank();
        IntBuffer buff = Datatype.allocBuff(128).asIntBuffer();

        if(rank == 0){
            System.out.println("rank 0");
            buff.put(0,0xAA55AA55);
            buff.put(1,0xFF00FF00);
            long start = System.nanoTime();
            MPI.COMM_WORLD.send(buff, 0, 2, MPI.INT_BUFFER, 1, 0,null);
            long end = System.nanoTime();
            System.out.println((end-start)/1000000.0);
        }
        else if(rank == 1){
            System.out.println("rank 1");
            long start = System.nanoTime();
            Status stat = MPI.COMM_WORLD.recv(buff, 0, 2, MPI.INT_BUFFER, 0, 0,null);
            long end = System.nanoTime();
            System.out.println((end-start)/1000000.0);
            buff.position(0);
            System.out.printf("0x%X 0x%X\n",
                buff.get(),buff.get());
            System.out.println(stat.count(MPI.INT_BUFFER));
        }

        MPI.Finalize();
    }
}