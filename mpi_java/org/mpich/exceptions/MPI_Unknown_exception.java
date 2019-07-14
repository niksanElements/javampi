
package org.mpich.exceptions;

public class MPI_Unknown_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Unknown_exception(String txt){
        super(txt);
    }
}
