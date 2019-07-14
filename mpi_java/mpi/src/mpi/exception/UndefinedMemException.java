package mpi.exception;

public class UndefinedMemException extends RuntimeException{
    private static final long serialVersionUID = 1L;
    public UndefinedMemException(String str){
        super(str);
    }
}