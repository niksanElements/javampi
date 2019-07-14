package mpi.exception;

/**
 * MPI_ERR_COUNT
 */
public class CountException extends Exception {
    private static final long serialVersionUID = 1L;
    public CountException(String txt){
        super(txt);
    }
}