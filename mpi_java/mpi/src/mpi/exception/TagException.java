package mpi.exception;

/**
 * MPI_ERR_TAG
 */
public class TagException extends Exception {
    private static final long serialVersionUID = 1L;
    public TagException(String txt){
        super(txt);
    }
}