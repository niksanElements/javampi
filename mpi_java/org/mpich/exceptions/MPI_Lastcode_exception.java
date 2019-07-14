
package org.mpich.exceptions;

public class MPI_Lastcode_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Lastcode_exception(String txt){
        super(txt);
    }
}
