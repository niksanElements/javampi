
package org.mpich.exceptions;

public class MPI_Rma_shared_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Rma_shared_exception(String txt){
        super(txt);
    }
}
