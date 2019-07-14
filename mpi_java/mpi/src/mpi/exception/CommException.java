package mpi.exception;

/**
 * MPI_ERR_COMM
 */
public class CommException extends RuntimeException {

	private static final long serialVersionUID = 1L;
	public CommException(String txt) {
		super(txt);
	}

}
