
package org.mpich.exceptions;

public class MPI_Comm_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Comm_exception(String txt){
        super(txt);
    }
}
