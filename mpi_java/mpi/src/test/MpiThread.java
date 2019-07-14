package test;

import mpi.MPI;

/**
 * MpiThread
 */
public class MpiThread {

    public static void main(String[] args) {
        MPI.Init_thread(args, MPI.THREAD_MULTIPLE);

        Thread th = new Thread(new Runnable(){
        
            @Override
            public void run() {
                int rank = MPI.COMM_WORLD.rank();
                int size = MPI.COMM_WORLD.size();

                System.out.printf("0,%d,%d\n",rank,size);
            }
        });

        Thread th1 = new Thread(new Runnable(){
        
            @Override
            public void run() {
                int rank = MPI.COMM_WORLD.rank();
                int size = MPI.COMM_WORLD.size();

                System.out.printf("1,%d,%d\n",rank,size);
            }
        });

        th.start();
        th1.start();

        try{
            th.join();
            th1.join();
        }
        catch(InterruptedException ex){
            ex.printStackTrace();
        }


        MPI.Finalize();
    }
}