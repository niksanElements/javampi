
package org.mpich.exceptions;

public class MPI_Truncate_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Truncate_exception(String txt){
        super(txt);
    }
}
