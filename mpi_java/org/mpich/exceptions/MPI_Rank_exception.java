
package org.mpich.exceptions;

public class MPI_Rank_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Rank_exception(String txt){
        super(txt);
    }
}
