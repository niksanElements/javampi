
package org.mpich.exceptions;

public class MPI_Access_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Access_exception(String txt){
        super(txt);
    }
}
