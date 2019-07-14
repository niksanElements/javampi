package mpi.exception;

/**
 * MPI_ERR_ROOT
 */
public class RootException extends RuntimeException {
    private static final long serialVersionUID = 1L;
    public RootException(String txt){
        super(txt);
    }
}