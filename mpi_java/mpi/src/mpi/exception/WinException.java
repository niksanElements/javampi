package mpi.exception;

// MPI_ERR_WIN
public class WinException extends RuntimeException {
    public static final long serialVersionUID = 0;
    public WinException(String msg){
        super(msg);
    }
}