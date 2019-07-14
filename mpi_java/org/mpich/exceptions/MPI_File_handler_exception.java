package org.mpich.exceptions;

public class MPI_File_handler_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_File_handler_exception(String txt){
        super(txt);
    }
}
