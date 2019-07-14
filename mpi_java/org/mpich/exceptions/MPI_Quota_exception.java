
package org.mpich.exceptions;

public class MPI_Quota_exception extends Exception {
    public static final long serialVersionUID = 1; 
    public MPI_Quota_exception(String txt){
        super(txt);
    }
}
