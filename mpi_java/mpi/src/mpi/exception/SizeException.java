package mpi.exception;

// MPI_ERR_SIZE
public class SizeException extends RuntimeException {
    public static final long serialVersionUID = 0;
    public SizeException(String msg){
        super(msg);
    } 
}