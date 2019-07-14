package mpi.exception;

/**
 * It is thrown when there is called a routine 
 * before initializing MPI.
 */
public class NotInitializedException extends RuntimeException {

	private static final long serialVersionUID = 1L;
	public NotInitializedException(String txt) {
		super(txt);
	}
}
