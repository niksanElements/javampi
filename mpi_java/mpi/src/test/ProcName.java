package test;

import mpi.MPI;

public class ProcName {
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
        String str = MPI.processor_name();
        double wtime = MPI.wtime();
        try{
            Thread.sleep(1000);
        }catch(Exception e){
            e.printStackTrace();
        }
        double wtick = MPI.wtick();
        System.out.printf("%f %f\n",wtime,wtick);
        System.out.println(str);
        System.out.flush();
		MPI.Finalize();
	}
}
