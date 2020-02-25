package test;

import mpi.MPI;
import mpi.op.IIntOp;
import mpi.op.Op;

public class Allreducec {
    public static void main(String[] args) {
        MPI.Init(args);

        int[] sendbuff = new int[2];
        int[] recvbuff = new int[1];
        Op op = new Op(new IIntOp() {
			
			@Override
			public int operation(int a, int b) {
				// System.out.printf("%d %d\n",a,b);
				return a+b;
			}
		},true);
        op.create(MPI.INT);

        int rank = MPI.COMM_WORLD.rank();

        sendbuff[0] = rank;

        MPI.COMM_WORLD.allreduce(sendbuff, recvbuff, 0, 0, 1, MPI.INT, op,null,null);

        int size = MPI.COMM_WORLD.size();
        int sum = size*(size-1)/2;
        boolean check  = sum == recvbuff[0];
 
        Utils.check(rank,check,"Allreducec");

        op.free();

        MPI.Finalize();
    }
}