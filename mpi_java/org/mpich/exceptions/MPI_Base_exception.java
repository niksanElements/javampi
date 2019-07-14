
package org.mpich.exceptions;

public class MPI_Base_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Base_exception(String txt){
        super(txt);
    }
}
