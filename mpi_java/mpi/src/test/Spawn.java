package test;

import mpi.Intercomm;
import mpi.MPI;

public class Spawn {

    public static final int NUM_SPAWNS = 2;

    public static void main(String[] args) {
        int np = NUM_SPAWNS;
        int[] errcodes = new int[NUM_SPAWNS];
        String[] _argv = {
            "-Djava.library.path=/home/nikolay/workspace/mpich-install-java/lib", 
            "test.Spawn",
            null
        };
    
        MPI.Init(args);
        Intercomm parentcomm =  MPI.parent();
        if (parentcomm.isNull())
        {
            /* Create 2 more processes - this example must be called spawn_example.exe for this to work. */
            parentcomm = MPI.COMM_WORLD.spawn(
                "java", _argv, np, MPI.INFO_NULL, 0,0,errcodes);
            System.out.printf("I'm the parent.\n");
        }
        else
        {
            System.out.printf("I'm the spawned.\n");
        }
        System.out.flush();
        MPI.Finalize();
    }
}