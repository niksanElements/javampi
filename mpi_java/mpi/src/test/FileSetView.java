package test;

import mpi.File;
import mpi.MPI;
import mpi.Status;
import mpi.datatype.Subarray;

/**
 * FileSetView
 */
public class FileSetView {

    public static void main(String[] args) {
        MPI.Init(args);

        int rank = MPI.COMM_WORLD.rank();
        int size = MPI.COMM_WORLD.size();
        File fh = MPI.COMM_WORLD.file_open("/home/nikolay/workspace/trash/test123", 
            MPI.MODE_CREATE|MPI.MODE_RDWR, MPI.INFO_NULL);
        
        int[] sizes = new int[1];
        sizes[0] = size;
        int[] subsizes = new int[1];
        subsizes[0] = 1;
        int[] starts = new int[1];
        starts[0] = rank;

        Subarray filetype = new Subarray(1, sizes, subsizes, starts);
        filetype.create(MPI.BYTE, MPI.ORDER_C);
        filetype.commit();

        fh.view(0, MPI.BYTE, filetype, "native", MPI.INFO_NULL);

        byte[] buff = new byte[10];
        buff[0] = (byte)rank;
        buff[1] = (byte)(rank+0x1);

        Status stat = new Status();
        fh.write(buff, 0, 2, MPI.BYTE, stat, null);
        System.out.println(stat.mpi_error);
        fh.write(buff, 0, 2, MPI.BYTE, null, null);
        System.out.println(stat.mpi_error);
        // System.out.println("This is strange!");

        filetype.free();
        // System.out.println("This is stranger!");
        fh.close();

        MPI.Finalize();
    }
}