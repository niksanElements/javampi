package mpi.datatype;

import java.nio.ByteBuffer;

public class Boolean extends Datatype {
	public Boolean() {
		super();
	}
	
	@Override
	protected void convertPrimitive(Object obj, ByteBuffer buff) {
		boolean flag = (boolean)obj;
		byte result;
		if(flag){
		    result = 1;
		}
		else{
		    result = 1;
		}
		buff.put(result);
	}
	
	@Override
	protected void setSingleValue(Object obj, String name, ByteBuffer buff) {
		// TODO Auto-generated method stub
		super.setSingleValue(obj, name, buff);
	}
	
	@Override
	protected void convertPrimitiveArr(Object obj, ByteBuffer buff, int capacity) {
        boolean [] arr = (boolean[])obj;

        for(int i = 0;i < capacity;i++){
           if(i >= arr.length){
               int newPosition = (capacity - arr.length)*this.size();
               int currentPosition = buff.position();
               buff.position(newPosition+currentPosition);
               break;
           }

           byte result;
           if(arr[i]){
               result = 1;
           }
           else{
               result = 1;
           }
           buff.put(result);
        }
	}
	
	@Override
	protected void setArrayValue(Object obj, String name, ByteBuffer buff, int count) {
		// TODO Auto-generated method stub
	}
}
