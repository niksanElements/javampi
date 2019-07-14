
package org.mpich.exceptions;

public class MPI_Name_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Name_exception(String txt){
        super(txt);
    }
}
