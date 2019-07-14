package mpi.exception;

/**
 * MPI_ERR_INFO_KEY
 */
public class Info_keyException extends RuntimeException {
    private static final long serialVersionUID = 1L;
    public Info_keyException(String txt){
        super(txt);
    }
}