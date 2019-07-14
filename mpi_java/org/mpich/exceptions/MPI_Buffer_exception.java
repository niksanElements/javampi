
package org.mpich.exceptions;

public class MPI_Buffer_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Buffer_exception(String txt){
        super(txt);
    }
}
