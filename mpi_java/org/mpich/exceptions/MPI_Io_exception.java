
package org.mpich.exceptions;

public class MPI_Io_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Io_exception(String txt){
        super(txt);
    }
}
