package mpi.datatype;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.nio.ByteBuffer;

import mpi.exception.DatatypeArgException;
import mpi.exception.TypeException;


/**
 * TODO: vector types
 * TODO: rework the whole datatype concept
 */
public class Datatype {
	
	protected long handler;
	// data specification
	private String[] names;
    private Datatype[] types;
    private int[] counts;
    private int size;

    // class type if have any
    Class<?> cls;

    private boolean isPrimitive;
	
	public Datatype() {
        this.handler = 0;
        this.isPrimitive = true;
        this.cls = null;
	}

    public Datatype(String[] names,Datatype[] types,int[] counts,
        Class<?> cls){
        this.names = names;
        this.types = types;
        this.isPrimitive = false;
        this.counts = counts;
        int num_fields = names.length;
        if(num_fields != types.length){
            throw new DatatypeArgException("Wrong description!");
        }
        int size = 0;
        for(int i = 0;i < num_fields;i++){
            size += (types[i].size()*counts[i]);
		}
		
        this.size = size;
        this.cls = cls;
        this.handler = 0;
    }

    /**
     * @return the isPrimitive
     */
    public boolean isPrimitive() {
        return isPrimitive;
    }

    public void setToByteBuffer(Object obj,ByteBuffer buff){
        if(obj == null){
            throw new NullPointerException("The object can't be a null!");
        }
        
        if((buff.capacity() - buff.position()) < this.size){
            throw new OutOfMemoryError("To small buffer!");
        }
        Class<? extends Object> cls = obj.getClass();
        for(int i = 0;i < names.length;i++){
            String methodName = "get".concat(names[i]);
            try{
                Method method = cls.getMethod(methodName);
            	Object data = method.invoke(obj);
        	   if(!data.getClass().isArray()){
                   types[i].convertPrimitive(data, buff);
                }
                else{
                    types[i].convertPrimitiveArr(data, buff, counts[i]);
                }
            }
            catch(NoSuchMethodException e){
                e.printStackTrace();
            }
            catch(IllegalAccessException e){
                e.printStackTrace();
            }
            catch(InvocationTargetException e){
                e.printStackTrace();
            }
        }
    }
    
    public Object constructFromByteByffer(ByteBuffer buff){
        Constructor<?> cons;
        Object obj = null;
		try {
			cons = this.cls.getConstructor();
			obj = cons.newInstance();
		} catch (NoSuchMethodException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InstantiationException e) {
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

        for(int i = 0;i < this.names.length;i++){
            String funcName = "set".concat(names[i]);

            if(this.counts[i] == 1){
                // we have single
                this.types[i].setSingleValue(obj,funcName,buff);
            }
            else{
                // we have array
                this.types[i].setArrayValue(obj,funcName,buff,counts[i]);
            }
        }

        return obj;
    }

	/**
	 * @return the handler
	 */
	public long getHandler() {
        if(this.handler == 0){
            throw new TypeException("Not committed type!");
        }
		return handler;
	}

	public static ByteBuffer allocBuff(int capacity){
		return ByteBuffer.allocateDirect(capacity);
	}

	public static void commit(Datatype type){
		// For now the inner MPI handler will be a byte vector.
		type.handler = _commit(type.size);
	}
    private static native long _commit(int size);
    
    // MPI_Type_commit
    public void commit(){
        _commit(this.handler);
    }
    private static native void _commit(long handler);

	public int size(){
		return this.size;
    }
    public void free(){
        _type_free(this.handler);
    }
    private static native void _type_free(long datatype);

    // primitive converters
    protected void convertPrimitive(Object obj,ByteBuffer buff){
    	this.setToByteBuffer(obj, buff);
    }

    protected void setSingleValue(Object obj,String name,ByteBuffer buff){
    	Object result = this.constructFromByteByffer(buff);
        Class<?> args[] = new Class[1];
        args[0] = result.getClass();
        Method method;
        try {
            method = obj.getClass().getMethod(name, args);
            method.invoke(obj, result);
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
    
    protected void convertPrimitiveArr(Object obj,ByteBuffer buff,int capacity){
    	Object[] arr = (Object[])obj;
        for(int i = 0;i < capacity;i++){
           if(i >= arr.length){
               int newPosition = (capacity - arr.length)*this.size();
               int currentPosition = buff.position();
               buff.position(newPosition+currentPosition);
               break;
           }
           this.setToByteBuffer(arr[i], buff);
        }
    }

    protected void setArrayValue(Object obj,String name,ByteBuffer buff,int count){
    	// get the value
        Object[] array = new Object[count];
        for(int i = 0;i < count;i++){
            array[i] = this.constructFromByteByffer(buff);
        }
        try {
            // set the value
            Class<?> args[] = new Class[1];
            args[0] = Object[].class;
            Method method = obj.getClass().getMethod(name, args);
            method.invoke(obj, new Object[] {array});
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
