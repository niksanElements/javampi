package mpi.datatype;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.nio.ByteBuffer;

public class Short extends Datatype {
	
	public Short() {
		super();
	}

	@Override
	protected void convertPrimitive(Object obj, ByteBuffer buff) {
      buff.putShort((short)obj);
	}
	
	@Override
	protected void setSingleValue(Object obj, String name, ByteBuffer buff) {
		short value = buff.getShort();
        Class<?> args[] = new Class[1];
        args[0] = short.class;
        Method method;
        try {
            method = obj.getClass().getMethod(name, args);
            method.invoke(obj, value);
        } catch (NoSuchMethodException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (SecurityException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IllegalArgumentException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
	}
	
	@Override
	protected void convertPrimitiveArr(Object obj, ByteBuffer buff, int capacity) {
		short[] arr = (short[])obj;
        buff.asShortBuffer().put(arr);
        for(int i = 0;i < capacity;i++){
            if(i >= arr.length){
                int newPosition = (capacity - arr.length)*this.size();
                int currentPosition = buff.position();
                buff.position(newPosition+currentPosition);
                break;
            }
            buff.putShort(arr[i]);
         }
	}
	
	@Override
	protected void setArrayValue(Object obj, String name, ByteBuffer buff, int count) {
		// get the value
        short[] array = new short[count];
        for(int i = 0;i < count;i++){
            array[i] = buff.getShort();
        }
        // set the value
        Class<?> args[] = new Class[1];
        args[0] = short[].class;
        Method method;
        try {
            method = obj.getClass().getMethod(name, args);
            method.invoke(obj, array);
        } catch (NoSuchMethodException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (SecurityException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IllegalAccessException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IllegalArgumentException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
	}
}
