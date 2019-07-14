package mpi.exception;

/**
 * MPI_ERR_RANK
 */
public class RankException extends Exception {
    private static final long serialVersionUID = 1L;
    public RankException(String txt){
        super(txt);
    }
}