
package org.mpich.exceptions;

public class MPI_Size_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Size_exception(String txt){
        super(txt);
    }
}
