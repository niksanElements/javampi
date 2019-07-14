
package org.mpich.exceptions;

public class MPI_Request_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Request_exception(String txt){
        super(txt);
    }
}
