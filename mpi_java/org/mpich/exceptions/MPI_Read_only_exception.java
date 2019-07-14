
package org.mpich.exceptions;

public class MPI_Read_only_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Read_only_exception(String txt){
        super(txt);
    }
}
