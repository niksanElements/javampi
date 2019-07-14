package mpi.exception;

/**
 * MPI_ERR_INFO_VALUE
 */
public class Info_valueException extends RuntimeException {
    private static final long serialVersionUID = 1L;
    public Info_valueException(String txt){
        super(txt);
    }
}