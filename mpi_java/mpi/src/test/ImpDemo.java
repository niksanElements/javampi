package test;

import mpi.MPI;

public class ImpDemo {
	public static void main(String[] args) {
		long start = System.nanoTime();
		String[] args1 = {
				"sodifaup",
				"sodifaupsf",
				"ks;dfjaipof",
				"sjpodfa",
				"piuerwer",
				"sodifjalfkj"
		};
		MPI.Init(args1);
		long end = System.nanoTime();
		System.out.printf("rank: %d size: %d\n",
				MPI.COMM_WORLD.rank(),
				MPI.COMM_WORLD.size());
		MPI.Finalize();
	}
}
