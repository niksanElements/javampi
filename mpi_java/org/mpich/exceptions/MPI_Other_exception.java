
package org.mpich.exceptions;

public class MPI_Other_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Other_exception(String txt){
        super(txt);
    }
}
