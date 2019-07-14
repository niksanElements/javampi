package mpi.exception;

/**
 * MPI_ERR_REQUEST
 */
public class RequestException extends RuntimeException{
    private static final long serialVersionUID = 1L;
    public RequestException(String txt){
        super(txt);
    }
}