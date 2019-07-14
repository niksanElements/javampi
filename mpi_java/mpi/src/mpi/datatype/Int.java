package mpi.datatype;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.nio.ByteBuffer;

public class Int extends Datatype {
	
	public Int() {
		super();
	}
	
	@Override
	protected void convertPrimitive(Object obj, ByteBuffer buff) {
		  buff.putInt((int)obj);
	}
	
	@Override
	protected void setSingleValue(Object obj, String name, ByteBuffer buff) {
		int value = buff.getInt();
        Class<?> args[] = new Class[1];
        args[0] = int.class;
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
		int[] arr = (int[])obj;
        for(int i = 0;i < capacity;i++){
           if(i >= arr.length){
               int newPosition = (capacity - arr.length)*this.size();
               int currentPosition = buff.position();
               buff.position(newPosition+currentPosition);
               break;
           }
           buff.putInt(arr[i]);
        }
	}
	
	@Override
	protected void setArrayValue(Object obj, String name, ByteBuffer buff, int count) {
        // get the value
        int[] array = new int[count];
        for(int i = 0;i < count;i++){
            array[i] = buff.getInt();
        }
        // set the value
        Class<?> args[] = new Class[1];
        args[0] = int[].class;
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
