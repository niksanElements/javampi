
package org.mpich.exceptions;

public class MPI_Op_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Op_exception(String txt){
        super(txt);
    }
}
