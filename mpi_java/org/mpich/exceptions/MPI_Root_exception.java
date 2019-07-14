
package org.mpich.exceptions;

public class MPI_Root_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Root_exception(String txt){
        super(txt);
    }
}
