
package org.mpich.exceptions;

public class MPI_Service_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Service_exception(String txt){
        super(txt);
    }
}
