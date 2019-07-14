
package org.mpich.exceptions;

public class MPI_Conversion_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Conversion_exception(String txt){
        super(txt);
    }
}
