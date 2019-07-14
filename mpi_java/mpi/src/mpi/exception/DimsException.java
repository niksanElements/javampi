package mpi.exception;

/**
 * MPI_ERR_DIMS
 */
public class DimsException extends RuntimeException {
    private static final long serialVersionUID = 1L;
    public DimsException(String txt){
        super(txt);
    }
}