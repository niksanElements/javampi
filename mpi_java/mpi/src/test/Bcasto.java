package test;

import java.util.Arrays;

import mpi.MPI;
import mpi.datatype.Datatype;
import test.types.Here;
import test.types.Person;

public class Bcasto {
    static String[] h_hapes = {
            "Id"
    };
    static Datatype[] h_types = {
            MPI.INT
    };
    static int[] h_counts = {
            1
    };

    static Datatype here = new Datatype(h_hapes, h_types, h_counts, Here.class);

    static String[] names = {
        "Age",
        "Name",
        "Some",
        "Here",
        "H"
    };

    static Datatype[] types = {
        MPI.INT,
        MPI.INT,
        MPI.LONG,
        here,
        here
        
    };

    static int[] counts = {
        1,10,20,1,3
    };
    static Datatype person = new Datatype(names, types,counts,Person.class);
    public static void main(String[] args) {
        MPI.Init(args);
        Datatype.commit(person);
        Datatype.commit(here);

        int[] buffer = new int[10];

        int rank = MPI.COMM_WORLD.rank();

        Person p = new Person(new int[]{rank,0x000000FF,0x000000FF,0x000000FF},0x55AA55AA);
        Here h = new Here();
        Here[] hs = new Here[3];
        hs[0] = new Here();
        hs[0].setId(13);
        hs[1] = new Here();
        hs[1].setId(14);
        hs[2] = new Here();
        hs[2].setId(15);
        h.setId(12);
        p.setHere(h);
        p.setH(hs);
        long[] array = new long[] {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
        p.setSome(array);
        // send the object
        Person pArr[] = new Person[1];
        if(rank == 0){
            pArr[0] = p;
        }
        
        MPI.COMM_WORLD.bcast(pArr,0,1,person,0,null);
        Utils.sleepRand(300);
        System.out.printf("0x%x",pArr[0].getAge());
        System.out.println(Arrays.toString(pArr[0].getName()));
        System.out.println(Arrays.toString(pArr[0].getSome()));
        System.out.println(pArr[0].getHere().getId());
        for(int i = 0;i < 3;i++) {
            System.out.println(pArr[0].getH()[i].getId());
        }
        // buffer[0] = rank;

        MPI.Finalize();

    }
}