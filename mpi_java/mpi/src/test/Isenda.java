package test;

import java.nio.ByteBuffer;

import mpi.MPI;
import mpi.Request;
import mpi.Status;

public class Isenda {
	public static void main(String[] args) {
		MPI.Init(args);
		int rank = MPI.COMM_WORLD.rank();
		// ByteBuffer buff = ByteBuffer.allocateDirect(30);

		if(rank == 0){
			int buff[] =  new int[] {0x55AA55AA};
			Request req = MPI.COMM_WORLD.isend(buff, 0, 1, 
				MPI.INT, 1, 0,null);
			req.Wait();
		}
		else if(rank == 1){
            int buff[] =  new int[1];
			Request req = MPI.COMM_WORLD.irecv(buff, 0, 1, 
				MPI.INT, 0, 0);
			Status stat = req.Wait();
            System.out.printf("0x%x\n",buff[0]);
            System.out.println(stat.count(MPI.INT));
		}

		MPI.Finalize();
	}
}
