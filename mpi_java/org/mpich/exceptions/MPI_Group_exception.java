
package org.mpich.exceptions;

public class MPI_Group_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Group_exception(String txt){
        super(txt);
    }
}
