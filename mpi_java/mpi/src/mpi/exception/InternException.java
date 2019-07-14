package mpi.exception;

/**
 * MPI_ERR_INTER
 */
public class InternException extends RuntimeException {
    private static final long serialVersionUID = 1L;
    public InternException(String txt){
        super(txt);
    }
}