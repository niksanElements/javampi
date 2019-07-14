
package org.mpich.exceptions;

public class MPI_Pending_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Pending_exception(String txt){
        super(txt);
    }
}
