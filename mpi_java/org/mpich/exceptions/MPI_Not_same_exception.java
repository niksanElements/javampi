
package org.mpich.exceptions;

public class MPI_Not_same_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Not_same_exception(String txt){
        super(txt);
    }
}
