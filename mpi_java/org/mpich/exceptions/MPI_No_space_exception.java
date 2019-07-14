
package org.mpich.exceptions;

public class MPI_No_space_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_No_space_exception(String txt){
        super(txt);
    }
}
