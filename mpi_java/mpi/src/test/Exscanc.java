package test;

import mpi.MPI;
import mpi.op.IIntOp;
import mpi.op.Op;

public class Exscanc {
    public static void main(String[] args) {
        MPI.Init(args);

        int[] sendbuff = new int[2];
        int[] recvbuff = new int[1];
        Op op = new Op(new IIntOp() {
			
			@Override
			public int operation(int a, int b) {
				System.out.printf("%d %d\n",a,b);
				return a+b;
			}
		},true);
        op.create(MPI.INT);

        int rank = MPI.COMM_WORLD.rank();

        sendbuff[0] = rank;

        MPI.COMM_WORLD.exscan(sendbuff, recvbuff, 0, 0, 1, MPI.INT, op,null,null);
        Utils.sleepRand(400);
        System.out.printf("result: %d\n",recvbuff[0]);

        op.free();

        MPI.Finalize();
    }
}