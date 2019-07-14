package test;

import java.nio.ByteBuffer;

import mpi.MPI;
import mpi.datatype.Datatype;
import mpi.op.ObjectOp;
import mpi.op.Op;
import test.types.Here;

public class Scanco {
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

        Op op = new Op(new ObjectOp(her) {
					
            @Override
            public Object operation(Object a, Object b) {
                Here _a = (Here)a;
                Here _b = (Here)b;
                System.out.printf("%d %d\n",_a.getId(),_b.getId());
                _b.setId(_b.getId()+_a.getId());
                return _b;
            }
        } , true);


        Datatype.commit(her);
        op.create(her);
        int rank = MPI.COMM_WORLD.rank();
        Here[] hSend = new Here[10];
        Here[] hRecv = new Here[3];

        hSend[0] = new Here();
        hSend[0].setId(rank);

        ByteBuffer buff = ByteBuffer.allocateDirect(124);
        ByteBuffer buff1= ByteBuffer.allocateDirect(124);

        long start = System.nanoTime();
        MPI.COMM_WORLD.scan(hSend, hRecv, 0, 0, 1, her, op, buff,buff1);
        long end = System.nanoTime();

        Utils.sleepRand(500);
        System.out.printf("%f\n", (end-start)/1000000.0);
        System.out.printf("result: %d\n",hRecv[0].getId());

        MPI.Finalize();
    }
}