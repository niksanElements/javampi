
package org.mpich.exceptions;

public class MPI_Info_nokey_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Info_nokey_exception(String txt){
        super(txt);
    }
}
