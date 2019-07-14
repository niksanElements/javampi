
package org.mpich.exceptions;

public class MPI_Unsupported_datarep_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Unsupported_datarep_exception(String txt){
        super(txt);
    }
}
