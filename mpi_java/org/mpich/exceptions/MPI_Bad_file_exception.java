
package org.mpich.exceptions;

public class MPI_Bad_file_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Bad_file_exception(String txt){
        super(txt);
    }
}
