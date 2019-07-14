package mpi.datatype;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.nio.ByteBuffer;

public class Long extends Datatype {
	public Long() {
		super();
	}
	
	@Override
	protected void convertPrimitive(Object obj, ByteBuffer buff) {
		buff.putLong((long)obj);
	}
	
	@Override
	protected void setSingleValue(Object obj, String name, ByteBuffer buff) {
		long value = buff.getLong();
        Class<?> args[] = new Class[1];
        args[0] = long.class;
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
		long[] arr = (long[])obj;
        for(int i = 0;i < capacity;i++){
           if(i >= arr.length){
               int newPosition = (capacity - arr.length)*this.size();
               int currentPosition = buff.position();
               buff.position(newPosition+currentPosition);
               break;
           }
           buff.putLong(arr[i]);
        }
	}
	
	@Override
	protected void setArrayValue(Object obj, String name, ByteBuffer buff, int count) {
		// get the value
        long[] array = new long[count];
        for(int i = 0;i < count;i++){
            array[i] = buff.getLong();
        }
        // set the value
        Class<?> args[] = new Class[1];
        args[0] = long[].class;
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
