package mpi;

public class Cart extends Intracomm {
    
    private int ndims;

    public Cart(long handler,int ndims){
        super(handler);
        this.ndims = ndims;
    }

    // MPI_Cart_coords
	public void coords(int rank,int offset,int maxdims,int[] coords){
		_cart_coords(this.handler, rank, offset, maxdims, coords);
	}
	private static native void _cart_coords(long comm,int rank,int offset,int maxdims,int[] coords);
	// MPI_Cart_rank
	public int rank(int offset,int ndims,int[] coords){
		return _cart_rank(this.handler,offset,ndims,coords);
	}
	private static native int _cart_rank(long comm,int offset,int ndims,int[] coords);
	// TODO: MPI_Cart_shift
	// MPI_Cart_get
	public void get(int offsetdims,int maxdims,int[] dims,
		int offsetperiods,int[] periods,int offsetcoords,int[] coords){
		_cart_get(this.handler, offsetdims, maxdims, dims, 
			offsetperiods, periods, offsetcoords, coords);
	}
	private static native void _cart_get(long comm,int offsetdims,int maxdims,int[] dims,
        int offsetperiods,int[] periods,int offsetcoords,int[] coords);
    // MPI_Cart_shift
    public int source(int direction,int disp){
        return _shift(this.handler, direction, disp, true);
    }
    public int dest(int direction,int disp){
        return _shift(this.handler, direction, disp, false);
    }
    private static native int _shift(long comm,int direction,int disp,boolean isSource);
    // MPI_Cart_sub
    public Cart sub(int offset,int[] remain_dims){
        long comm = _sub(this.handler,offset,this.ndims,remain_dims);
        int remdims = 0;
        for(int i = offset;i < (offset+this.ndims);i++){
            if(remain_dims[i] == 1)
                remdims++;
        }

        return new Cart(comm,remdims);
    }
    private static native long _sub(long comm,int offset,int size,int[] remain_dims);
    // MPI_Cartdims_get
    public int dims(){
        return ndims;
        // // only for test
        // int ndims = _dims(this.handler);

        // if(this.ndims != ndims){
        //     new Exception("different dimensions");
        // }

        // return ndims;
    }
    private static native int _dims(long comm);
    // MPI_Comm_dup
    public Cart dup(){
        long handler = _dup(this.handler);

        return new Cart(handler,this.ndims);
    }
}