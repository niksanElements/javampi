
package org.mpich.exceptions;

public class MPI_In_status_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_In_status_exception(String txt){
        super(txt);
    }
}
