package test;

import java.nio.ByteBuffer;

import mpi.MPI;
import mpi.Message;
import mpi.Request;

public class Imrecv {
	public static void main(String[] args) {
		MPI.Init(args);
		int rank = MPI.COMM_WORLD.rank();
		ByteBuffer buff = ByteBuffer.allocateDirect(30);

		if(rank == 0){
			buff.putInt(0,0x55AA55AA);
			Request req = MPI.COMM_WORLD.isend(buff, 0, 4, 
				MPI.BYTE_BUFFER, 1, 0,null);
			req.Wait();
		}
		else if(rank == 1){
			Message msg = MPI.COMM_WORLD.improbe(0, 0);
			while(!msg.getStatus().isRequestFinish()){
				msg = MPI.COMM_WORLD.improbe(0, 0);
			}
			Request req = msg.imrecv(buff, 0, 4, MPI.BYTE_BUFFER);
			req.Wait();
			int result = buff.getInt(0);
			System.out.printf("0x%x\n",result);
		}

		MPI.Finalize();
	}
}
