
package org.mpich.exceptions;

public class MPI_File_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_File_exception(String txt){
        super(txt);
    }
}
