
package org.mpich.exceptions;

public class MPI_Type_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Type_exception(String txt){
        super(txt);
    }
}
