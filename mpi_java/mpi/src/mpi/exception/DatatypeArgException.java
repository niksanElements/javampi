package mpi.exception;

/**
 * It is used in the construction of a new datatype.
 * This exception is thrown when a wrongly formated
 * exception has been passed to the constructor of
 * Objecttype.
 */
public class DatatypeArgException extends RuntimeException{
    private static final long serialVersionUID = 1L;
    public DatatypeArgException(String txt){
        super(txt);
    }
}