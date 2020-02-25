package test;

import java.util.Arrays;

import mpi.Intercomm;
import mpi.MPI;

public class OpenPort {

    /* This test checks to make sure that two MPI_Comm_connects to two different MPI ports
    * match their corresponding MPI_Comm_accepts. The root process opens two MPI ports and
    * sends the first port to process 1 and the second to process 2. Then the root process
    * accepts a connection from the second port followed by the first port. 
    * Processes 1 and 2 both connect back to the root but process 2 first sleeps for three 
    * seconds to give process 1 time to attempt to connect to the root. The root should wait 
    * until process 2 connects before accepting the connection from process 1.
    */

    public static void main(String[] args) {
        String port1,port2;
        Intercomm comm1,comm2;
        int[] data = new int[10];
        MPI.Init(args);
        int size = MPI.COMM_WORLD.size();
        int rank = MPI.COMM_WORLD.rank();
        if (size < 3){
            System.out.printf("Three processes needed to run this test.\n");
            System.out.flush();
            MPI.Finalize();
            return;
        }

        if (rank == 0){
            System.out.printf("0: opening ports.\n");
            System.out.flush();
            port1 = MPI.open_port(MPI.INFO_NULL);
            port2 = MPI.open_port(MPI.INFO_NULL);
            System.out.printf("opened port1: <%s>\n", port1);
            System.out.printf("opened port2: <%s>\n", port2);
            System.out.flush();
            char[] _port1 = port1.toCharArray();
            char[] _port2 = port2.toCharArray();
            MPI.COMM_WORLD.send(_port1, 0, _port1.length, MPI.CHAR, 1, 0, null);
            MPI.COMM_WORLD.send(_port2, 0, _port2.length, MPI.CHAR, 2, 0, null);
            System.out.printf("accepting port2.\n");
            System.out.flush();
            comm1 = MPI.COMM_SELF.accept(port1, MPI.INFO_NULL, 0);
            System.out.printf("accepting port1.\n");
            System.out.flush();
            comm2 = MPI.COMM_SELF.accept(port2, MPI.INFO_NULL, 0);
            MPI.close_port(port1);
            MPI.close_port(port2);
            data[0] = 1; data[1] = 2; data[2] = 3;
            comm1.send(data, 0, 3, MPI.INT, 0, 0, null);
            System.out.printf("sended %s to process 1.\n",Arrays.toString(data));
            System.out.flush();
            data[0] = 4; data[1] = 5; data[2] = 6;
            comm2.send(data, 0, 3, MPI.INT, 0, 0, null);
            System.out.printf("sended %s to process 2.\n",Arrays.toString(data));
            System.out.flush();
            comm1.disconnect();comm2.disconnect();
        }
        else if (rank == 1){
            char[] _port1 = new char[1028];
            MPI.COMM_WORLD.recv(_port1, 0, 1028, MPI.CHAR, 0, 0, null);
            port1 = new String(_port1);
            comm1 = MPI.COMM_SELF.connect(port1, MPI.INFO_NULL, 0);
            comm1.recv(data, 0, 3, MPI.INT, 0, 0, null);
            System.out.printf("1 recv %s\n",Arrays.toString(data));
            System.out.flush();
            comm1.disconnect();
        }
        else if (rank == 2){
            char[] _port2 = new char[1028];
            MPI.COMM_WORLD.recv(_port2, 0, 1028, MPI.CHAR, 0, 0, null);
            port2 = new String(_port2);
            /* make sure process 1 has time to do the connect before this process attempts to connect */
            try{ Thread.sleep(3000);} catch(Exception e){ e.printStackTrace(); }
            comm2 = MPI.COMM_SELF.connect(port2, MPI.INFO_NULL, 0);
            comm2.recv(data, 0, 3, MPI.INT, 0, 0, null);
            System.out.printf("2 recv %s\n",Arrays.toString(data));
            System.out.flush();
            comm2.disconnect();
        }
        MPI.COMM_WORLD.barrier();
        MPI.Finalize();
    }
}