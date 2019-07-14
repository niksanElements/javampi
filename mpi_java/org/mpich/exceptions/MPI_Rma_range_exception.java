
package org.mpich.exceptions;

public class MPI_Rma_range_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Rma_range_exception(String txt){
        super(txt);
    }
}
