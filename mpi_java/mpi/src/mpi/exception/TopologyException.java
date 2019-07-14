package mpi.exception;

/**
 * MPI_ERR_TOPOLOGY
 */
public class TopologyException extends RuntimeException {
    private static final long serialVersionUID = 1L;
    public TopologyException(String txt){
        super(txt);
    }
}