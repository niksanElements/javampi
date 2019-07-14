
package org.mpich.exceptions;

public class MPI_File_exists_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_File_exists_exception(String txt){
        super(txt);
    }
}
