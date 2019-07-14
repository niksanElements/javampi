
package org.mpich.exceptions;

public class MPI_Arg_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Arg_exception(String txt){
        super(txt);
    }
}
