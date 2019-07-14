
package org.mpich.exceptions;

public class MPI_Port_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Port_exception(String txt){
        super(txt);
    }
}
