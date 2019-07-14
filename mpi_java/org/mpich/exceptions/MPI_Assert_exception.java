
package org.mpich.exceptions;

public class MPI_Assert_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Assert_exception(String txt){
        super(txt);
    }
}
