package mpi.exception;

/**
 * MPI_ERR_ARG
 */
public class ArgException extends RuntimeException {

	private static final long serialVersionUID = 1L;
	public ArgException(String txt) {
		super(txt);
	}
}
