package mpi;

import java.nio.ByteBuffer;

import mpi.datatype.Datatype;

public class Request {
	private long handler;
	
	public Request(long handler) {
		this.handler = handler;
	}

	public long getHandler() {
		return handler;
	}

	// TODO: All wait&test functions!
	// MPI_Wait
	public Status Wait(){
		MPI.checkInitialization();
		return _wait(this.handler);
	}
	private static native Status _wait(long handler);
	// MPI_Wait for objects
	public Status wait(Object[] objArr,int offset,int count,Datatype type,ByteBuffer buff){
		Status stat = _wait(this.handler);

		// convert the received data into objects
		if(objArr != null && type != null && buff != null && !type.isPrimitive()){
			for(int i = offset;i < (offset+count);i++){
				objArr[i] = type.constructFromByteByffer(buff);
			}
		}

		return stat;
	}
	/**
	 * MPI_Test
	 * 
	 * @return null if the message is not received
	 */
	public Status test(){
		MPI.checkInitialization();
		return _test(this.handler);
	}
	private static native Status _test(long handler);
	// MPI_Test for objects
	public Status test(Object[] objArr,int offset,int count,Datatype type,ByteBuffer buff){
		Status stat = _test(this.handler);

		// convert the received data into objects
		if(objArr != null && type != null && buff != null && !type.isPrimitive()){
			for(int i = offset;i < (offset+count);i++){
				objArr[i] = type.constructFromByteByffer(buff);
			}
		}

		return stat;
	}
	// MPI_Request_get_status
	public Status get_status(){
		MPI.checkInitialization();
		return _get_status(handler);
	}
	private static native Status _get_status(long handler);

	// MPI_Request_free
	public void free(){
		MPI.checkInitialization();
		_free(handler);
	}
	private static native void _free(long handler);

	// MPI_Cancel
	public void Cancel(){
		MPI.checkInitialization();
		_cancel(this.handler);
	}
	private static native void _cancel(long handler);

	// MPI_Start
	public void start(){
		MPI.checkInitialization();
		_start(this.handler);
	}
	private static native void _start(long handler);


	// TODO: testany,testsome,waitany,waitall etc.
}
