package mpi.exception;

/**
 * MPI_ERR_BUFFER
 */
public class BufferException extends RuntimeException{
    private static final long serialVersionUID = 1L;
    public BufferException(String txt){
        super(txt);
    }
}