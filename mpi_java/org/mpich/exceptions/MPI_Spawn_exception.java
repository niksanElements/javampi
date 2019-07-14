
package org.mpich.exceptions;

public class MPI_Spawn_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Spawn_exception(String txt){
        super(txt);
    }
}
