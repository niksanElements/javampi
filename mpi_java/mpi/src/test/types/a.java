package test.types;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.nio.ByteBuffer;
import java.util.Arrays;

import mpi.MPI;
import mpi.Status;
import mpi.datatype.Datatype;

public class a{
	
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

    public static byte[] serialize(Object obj){
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        ObjectOutputStream out = null;
        byte[] array = null;
        try {
            out = new ObjectOutputStream(bos);   
            out.writeObject(obj);
            out.flush();
            array = bos.toByteArray();
        }
        catch(IOException e){

        } 
        finally {
            try {
                bos.close();
            } catch (IOException ex) {
                // ignore close exception
            }
        }
        return array;
    }

    public static void main(String[] args) {
		MPI.Init(args);
		
		Datatype.commit(person);
		Datatype.commit(here);

		ByteBuffer buff = Datatype.allocBuff(1024);

    	int rank = MPI.COMM_WORLD.rank();
    	if(rank == 0) {
	        Person p = new Person(new int[]{0x000000FF,0x000000FF,0x000000FF},0x55AA55AA);
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
	        pArr[0] = p;
	        MPI.COMM_WORLD.send(pArr,0,1,person,1,0,buff);
    	}
    	else if(rank == 1) {
    		Person[] pArr = new Person[2];
    		Status stat = MPI.COMM_WORLD.recv(pArr,0,1,person,0,0,buff);
    		
	        System.out.printf("0x%x",pArr[0].getAge());
	        System.out.println(Arrays.toString(pArr[0].getName()));
	        System.out.println(Arrays.toString(pArr[0].getSome()));
	        System.out.println(pArr[0].getHere().getId());
	        for(int i = 0;i < 3;i++) {
	        	System.out.println(pArr[0].getH()[i].getId());
	        }
	        System.out.println(stat.count(person));
    	}
    	
    	MPI.Finalize();
    }
}