package mpi.datatype;

import java.nio.ByteBuffer;

/**
 * Subarray
 * 
 * MPI_Type_create_subarray
 * 
 * TODO: See if there is place for this besides file view!
 */
public class Subarray extends Datatype {

    private int[] sizes;
    private int[] sub_sizes;
    private int[] starts;
    private int ndims;

    public Subarray(int ndims,int[] sizes, int[] sub_sizes, int[] starts) {
        this.sizes = sizes;
        this.sub_sizes = sub_sizes;
        this.starts = starts;
        this.ndims = ndims;
    }

    public void create(Datatype old_type,int order){
        this.handler = _create_subarray(ndims, sizes, sub_sizes, starts, 
            order, old_type.getHandler());
    }
    private static native long _create_subarray(
        int ndims,int[] sizes,int[] sub_sizes,int[] starts,int order,long old_type
    );

    @Override
	protected void convertPrimitive(Object obj, ByteBuffer buff) {
        // TODO: Subarray.convertPrimitive
	}
	
	@Override
	protected void setSingleValue(Object obj, String name, ByteBuffer buff) {
		// TODO: Subarray.setSingleValue
	}
	
	@Override
	protected void convertPrimitiveArr(Object obj, ByteBuffer buff, int capacity) {
		// TODO: Subarray.convertPrimiriveArr
	}
	
	@Override
	protected void setArrayValue(Object obj, String name, ByteBuffer buff, int count) {
        // TODO: Subarray.setArrayValue
	}
}