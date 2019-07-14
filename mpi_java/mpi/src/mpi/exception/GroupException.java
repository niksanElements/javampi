package mpi.exception;

/**
 * MPI_ERR_GROUP
 */
public class GroupException extends RuntimeException {
    private static final long serialVersionUID = 1L;
    public GroupException(String txt){
        super(txt);
    }
}