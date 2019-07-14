package mpi.op;

import mpi.datatype.Datatype;

/**
 * MPI_Op
 */
public class Op{
    private long handler;
    private Object operation;
    private boolean isCommute;

    // constructors
    public Op(){}
    public Op(Object operation,boolean isCommute){
        this.operation = operation;
        this.isCommute = isCommute;
    }

    public long getHandler() {  
        return handler;
    }
    // MPI_Op_create
    public void create(Datatype type){
        if(this.operation != null)
            this.handler = _create(this.operation,this.isCommute,type.getHandler());

    }
    private static native long _create(Object operation,boolean isCommute,long datatype);
    // MPI_Op_free
    public void free(){
        if(this.operation != null)
            _free(this.handler);
    }
    private static native void _free(long handler);

}