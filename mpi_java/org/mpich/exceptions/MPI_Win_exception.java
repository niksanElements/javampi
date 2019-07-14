
package org.mpich.exceptions;

public class MPI_Win_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Win_exception(String txt){
        super(txt);
    }
}
