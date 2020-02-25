package mpi;

import java.nio.ByteBuffer;

import mpi.datatype.Datatype;
import mpi.exception.BuffArrayException;
import mpi.op.Op;

/**
 * Implementation for a MPI communicator.
 * @author nikolay
 *
 */

 /**
  * TODO: set broadcast here
  */
public class Comm implements IFree {
	protected long handler;

	// null handler
	public static final long null_handler = 0x04000000;

	public Comm() {
	}
	
	public Comm(long handler) {
		this.handler = handler;
	}
	
	public long getHandler(){
		return this.handler;
	}

	public boolean isNull(){
		// TODO: remove the hard coded value
		if(this.handler == null_handler){
			return true;
		}

		return false;
	}
	
	public int rank() {
		MPI.checkInitialization();
		return _rank(this.handler);
	}
	private static native int _rank(long handler);

	public int size() {
		return _size(this.handler);
	}
	private static native int _size(long handler);

	// MPI_Comm_free
	@Override
	public void free(){
		if(!this.isNull())
			_free(this.handler);
	}
	private static native void _free(long comm);

	// MPI_Comm_group
	public Group group(){
		long group_handler = _group(this.handler);

		return new Group(group_handler);
	}
	private static native long _group(long comm);

	// MPI_Abort
	public void abort(int errorcode){
		_abort(this.handler, errorcode);
	}
	private static native void _abort(long comm,int errorcode);

	// MPI_Comm_compare
	public int compare(Comm comm){
		int result = _compare(this.handler, comm.handler);

		return result;
	}
	private static native int _compare(long comm1,long comm2);

    // TODO: to see if this is for here or Comm object
    // MPI_Comm_dup
    public Comm dup(){
        long new_handler = _dup(this.handler);

        return new Comm(new_handler);
    }
    protected static native long _dup(long comm);
	// TODO: MPI_Comm_idup
	
	/**
	 * TODO: caching attributes
	 */

	/**
	 * Point-to-point communication
	 * 
	 * @Note: All point-to-point communication are implemented around
	 * accessing array, so passing single objects want work.
	 */
	protected static void sendRecvInit(Object buff){
		MPI.checkInitialization();
		if(buff == null){
			throw new NullPointerException();
		}
	}
	public static void fillBuffer(Object buff,int offset,int count,
		Datatype datatype, ByteBuffer objBuff
	){
		Object[] objArr = (Object[])buff;
		for(int i = offset;i < (offset+count);i++){
			datatype.setToByteBuffer(objArr[i], objBuff);
		}

	}
	// MPI_SEND
	public void send(Object buff,int offset,int count,
		Datatype datatype,int dest,int tag,ByteBuffer objBuff
	){
		sendRecvInit(buff);
		// TODO: To think of something to prevent that allocation 
		// on buffer when it comes to a Object communication
		if(!datatype.isPrimitive()){
			if(objBuff == null){
				int cap = count*datatype.size();
				objBuff = ByteBuffer.allocateDirect(cap);
			}
			else{
				// completely reset the buffer
				objBuff.limit(objBuff.capacity());
				objBuff.rewind();
			}
			fillBuffer(buff, offset, count,datatype,objBuff);
			_send(objBuff, 0, count, 
					datatype.getHandler(), dest, tag, handler);
		}
		else{
			_send(buff, offset, count, 
				datatype.getHandler(), dest, tag, handler);
		}
	}
	private static native void _send(Object buff,int offset,int count,
		long datatype,int source,int tag,long comm);
	// MPI_BSEND
	public void bsend(Object buff,int offset, int count,
		Datatype datatype, int dest, int tag,ByteBuffer objBuff
	){
		sendRecvInit(buff);
		// TODO: To think of something to prevent that allocation 
		// on buffer when it comes to a Object communication
		if(!datatype.isPrimitive()){
			if(objBuff == null){
				int cap = count*datatype.size();
				objBuff = ByteBuffer.allocateDirect(cap);
			}
			else{
				// completely reset the buffer
				objBuff.limit(objBuff.capacity());
				objBuff.rewind();
			}
			fillBuffer(buff, offset, count,datatype,objBuff);
			_bsend(objBuff, 0, count, 
					datatype.getHandler(), dest, tag, handler);
		}
		else{
			_bsend(buff, offset, count, 
				datatype.getHandler(), dest, tag, handler);
		}
	}
	private static native void _bsend(Object buff,int offset,int count,
		long datatype,int source,int tag,long comm);	
	// MPI_SSEND
	public void ssend(Object buff,int offset, int count,
		Datatype datatype, int dest, int tag,ByteBuffer objBuff
	){
		sendRecvInit(buff);
		// TODO: To think of something to prevent that allocation 
		// on buffer when it comes to a Object communication
		if(!datatype.isPrimitive()){
			if(objBuff == null){
				int cap = count*datatype.size();
				objBuff = ByteBuffer.allocateDirect(cap);
			}
			else{
				// completely reset the buffer
				objBuff.limit(objBuff.capacity());
				objBuff.rewind();
			}
			fillBuffer(buff, offset, count,datatype,objBuff);
			_ssend(objBuff, 0, count, 
					datatype.getHandler(), dest, tag, handler);
		}
		else{
			_ssend(buff, offset, count, 
				datatype.getHandler(), dest, tag, handler);
		}
	}
	private static native void _ssend(Object buff,int offset,int count,
		long datatype,int source,int tag,long comm);	
	// MPI_RSEND	
	public void rsend(Object buff,int offset, int count,
		Datatype datatype, int dest, int tag,ByteBuffer objBuff
	){
		sendRecvInit(buff);
		// TODO: To think of something to prevent that allocation 
		// on buffer when it comes to a Object communication
		if(!datatype.isPrimitive()){
			if(objBuff == null){
				int cap = count*datatype.size();
				objBuff = ByteBuffer.allocateDirect(cap);
			}
			else{
				// completely reset the buffer
				objBuff.limit(objBuff.capacity());
				objBuff.rewind();
			}
			fillBuffer(buff, offset, count,datatype,objBuff);
			_rsend(objBuff, 0, count, 
					datatype.getHandler(), dest, tag, handler);
		}
		else{
			_rsend(buff, offset, count, 
				datatype.getHandler(), dest, tag, handler);
		}
	}
	private static native void _rsend(Object buff,int offset,int count,
		long datatype,int source,int tag,long comm);	
// TODO: remove a object return argument
	// MPI_RECV
	public Status recv(Object buff,int offset,int count,
		Datatype datatype,int source,int tag,ByteBuffer objBuff
	){
		sendRecvInit(buff);
		Status stat = null;
		// TODO: To think of something to prevent that allocation 
		// on buffer when it comes to a Object communication
		if(!datatype.isPrimitive()){
			int cap = count*datatype.size();
			if(objBuff == null){
				objBuff = ByteBuffer.allocateDirect(cap);
			}
			else{
				// completely reset the buffer
				objBuff.limit(objBuff.capacity());
				objBuff.rewind();
			}
			Object[] objArr = (Object[])buff;
			stat = _recv(objBuff, 0, count, 
				datatype.getHandler(), source, tag, handler);
			for(int i = offset;i < (offset+count);i++){
				objArr[i] = datatype.constructFromByteByffer(objBuff);
			}
		}
		else{
			stat = _recv(buff, offset, count, 
				datatype.getHandler(), source, tag, handler);

		} 

		return stat;
	}
	private static native Status _recv(Object buff,int offset,int count,
		long datatype,int source,int tag,long comm);

	// non-blocking send/recv
	// MPI_Isend
	// TODO: send objects with all non-blocking functions
	public 	Request isend(Object buff,int offset,int count,
		Datatype datatype,int dest,int tag,ByteBuffer objBuff
	){
		sendRecvInit(buff);
		// TODO: To think of something to prevent that allocation 
		// on buffer when it comes to a Object communication
		if(!datatype.isPrimitive()){
			if(objBuff == null){
				int cap = count*datatype.size();
				objBuff = ByteBuffer.allocateDirect(cap);
			}
			else{
				// completely reset the buffer
				objBuff.limit(objBuff.capacity());
				objBuff.rewind();
			}
			fillBuffer(buff, offset, count,datatype,objBuff);
			return _isend(objBuff, offset, count, datatype.getHandler(), 
				dest, tag, this.handler);
		}
		else{
			return _isend(buff, offset, count, datatype.getHandler(), 
				dest, tag, this.handler);
		}		
	}
	private static native Request _isend(Object buff,int offset,int count,
		long datatype,int dest,int tag,long comm);
	// MPI_Ibsend
	public 	Request ibsend(Object buff,int offset,int count,
		Datatype datatype,int dest,int tag,ByteBuffer objBuff
	){
		sendRecvInit(buff);
		// TODO: To think of something to prevent that allocation 
		// on buffer when it comes to a Object communication
		if(!datatype.isPrimitive()){
			if(objBuff == null){
				int cap = count*datatype.size();
				objBuff = ByteBuffer.allocateDirect(cap);
			}
			else{
				// completely reset the buffer
				objBuff.limit(objBuff.capacity());
				objBuff.rewind();
			}
			fillBuffer(buff, offset, count,datatype,objBuff);
			return _ibsend(objBuff, offset, count, datatype.getHandler(), 
				dest, tag, this.handler);
		}
		else{
			return _ibsend(buff, offset, count, datatype.getHandler(), 
				dest, tag, this.handler);
		}
	}
	private static native Request _ibsend(Object buff,int offset,int count,
		long datatype,int dest,int tag,long comm);
	// MPI_Issend
	public 	Request issend(Object buff,int offset,int count,
		Datatype datatype,int dest,int tag,ByteBuffer objBuff
	){
		sendRecvInit(buff);
		// TODO: To think of something to prevent that allocation 
		// on buffer when it comes to a Object communication
		if(!datatype.isPrimitive()){
			if(objBuff == null){
				int cap = count*datatype.size();
				objBuff = ByteBuffer.allocateDirect(cap);
			}
			else{
				// completely reset the buffer
				objBuff.limit(objBuff.capacity());
				objBuff.rewind();
			}
			fillBuffer(buff, offset, count,datatype,objBuff);
			return _issend(objBuff, offset, count, datatype.getHandler(), 
				dest, tag, this.handler);
		}
		else{
			return _issend(buff, offset, count, datatype.getHandler(), 
				dest, tag, this.handler);
		}
	}
	private static native Request _issend(Object buff,int offset,int count,
		long datatype,int dest,int tag,long comm);
	// MPI_Irsend
	public 	Request irsend(Object buff,int offset,int count,
		Datatype datatype,int dest,int tag,ByteBuffer objBuff
	){
		sendRecvInit(buff);
		// TODO: To think of something to prevent that allocation 
		// on buffer when it comes to a Object communication
		if(!datatype.isPrimitive()){
			if(objBuff == null){
				int cap = count*datatype.size();
				objBuff = ByteBuffer.allocateDirect(cap);
			}
			else{
				// completely reset the buffer
				objBuff.limit(objBuff.capacity());
				objBuff.rewind();
			}
			fillBuffer(buff, offset, count,datatype,objBuff);
			return _irsend(objBuff, offset, count, datatype.getHandler(), 
				dest, tag, this.handler);
		}
		else{
			return _irsend(buff, offset, count, datatype.getHandler(), 
				dest, tag, this.handler);
		}
	}
	private static native Request _irsend(Object buff,int offset,int count,
		long datatype,int dest,int tag,long comm);
	// MPI_Irecv
	public Request irecv(Object buff,int offset,int count,
		Datatype datatype,int source,int tag
	){
		sendRecvInit(buff);
		return _irecv(buff, offset, count, datatype.getHandler(), 
			source, tag, this.handler);
	}
	private static native Request _irecv(Object buff,int offset,int count,
		long datatype,int source,int tag,long comm);
	// MPI_Probe
	public Status probe(int source,int tag){
		MPI.checkInitialization();
		return _probe(source,tag,handler);
	}
	private static native Status _probe(int source, int tag,long comm);
	// MPI_Iprobe
	public Status iprobe(int source,int tag){
		MPI.checkInitialization();
		return _iprobe(source,tag,handler);
	}
	public static native Status _iprobe(int source,int rag,long comm);
	// TODO: MPI_Mprobe

	// persistent communication
	// MPI_Send_init
	// Note: The function accepts only Direct Buffers!
	public Request send_init(Object buff,int offset,int count, Datatype type,
		int dest,int tag
	){
		sendRecvInit(buff);
		return _send_init(buff,offset,count,type.getHandler(), 
			dest, tag, this.handler);
	}
	private static native Request _send_init(
		Object buff,int offset,int count,long datatype,int dest,int tag,long comm);
	private static native Request _bsend_init(
		Object buff,int offset,int count,long datatype,int dest,int tag,long comm);
	private static native Request _ssend_init(
		Object buff,int offset,int count,long datatype,int dest,int tag,long comm);
	private static native Request _rsend_init(
		Object buff,int offset,int count,long datatype,int dest,int tag,long comm);
	// MPI_Recv_init
	// Note: The function accepts only Direct Buffers!
	public Request recv_init(
		Object buff,int offset,int count, Datatype type,
		int source,int tag)
	{
		sendRecvInit(buff);
		return _recv_init(buff, offset, count, type.getHandler(), 
			source, tag, this.handler);
	}
	private static native Request _recv_init(
		Object buff,int offset,int count,long datatype,int source,int tag,long comm);

	// matching probe
	// MPI_Mprobe
	public Message mprobe(int source,int tag){
		MPI.checkInitialization();
		return _mprobe(source, tag, this.handler);
	}
	private static native Message _mprobe(int source, int tag, long comm);
	// MPI_Improbe
	public Message improbe(int source,int tag){
		MPI.checkInitialization();
		return _improbe(source, tag, this.handler);
	}
	private static native Message _improbe(int source, int tag, long comm);
	// MPI_Sendrecv
	/**
	 * int MPI_Sendrecv(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
                int dest, int sendtag,
                void *recvbuf, int recvcount, MPI_Datatype recvtype,
                int source, int recvtag,
                MPI_Comm comm, MPI_Status *status)
	 * @return
	 */
	public Status sendrecv(
		Object sendbuff,int sendoffset,int sendcount,Datatype  sendtype,
		int dest,int sendtag, ByteBuffer sendObjBuff,
		Object recvbuff,int recvoffset,int recvcount,Datatype recvtype,
		int source,int recvtag, ByteBuffer recvObjBuff
	){
		Status stat = null;
		MPI.checkInitialization();
		Object _sendbuff = sendbuff;
		Object _recvbuff = recvbuff;
		// send preparations
		if(sendbuff != null){
			if(!sendtype.isPrimitive()){
				if(sendObjBuff == null){
					int cap = recvcount*sendtype.size();
					sendObjBuff = ByteBuffer.allocateDirect(cap);
				}
				else{
					// completely reset the buffer
					sendObjBuff.limit(sendObjBuff.capacity());
					sendObjBuff.rewind();
				}
				fillBuffer(sendbuff, sendoffset, sendcount,sendtype,sendObjBuff);
				_sendbuff = sendObjBuff;
			}
		}
		// receive preparations
		if(recvbuff != null){
			if(!recvtype.isPrimitive()){
				int cap = recvcount*recvtype.size();
				if(recvObjBuff == null){
					recvObjBuff = ByteBuffer.allocateDirect(cap);
				}
				else{
					// completely reset the buffer
					recvObjBuff.limit(recvObjBuff.capacity());
					recvObjBuff.rewind();
				}
				_recvbuff = recvObjBuff;
			}
		}

		stat = _sendrecv(_sendbuff, sendoffset, sendcount, sendtype.getHandler(), 
			dest, sendtag, 
			_recvbuff, recvoffset, recvcount, recvtype.getHandler(), 
			source, recvtag, 
			this.handler);
		if(recvbuff != null){
			if(!recvtype.isPrimitive()){
				Object[] objArr = (Object[])recvbuff;
				for(int i = recvoffset;i < (recvoffset+recvcount);i++){
					objArr[i] = recvtype.constructFromByteByffer(recvObjBuff);
				}
			}
		}

		return stat;
	}
	private static native Status _sendrecv(
		Object sendbuff,int sendoffset,int sendcount,long sendtype,
		int dest,int sendtag,
		Object recvbuff,int recvoffset,int recvcount,long recvtype,
		int source,int recvtag,long comm);
	
	public Status sendrecv_replace(Object buff,int offset,int count,Datatype datatype,
		int dest,int sendtag,int source,int recvtag,ByteBuffer objBuff
	){
		Status stat = null;
		MPI.checkInitialization();
		Object _buff = buff;
		// send preparations
		if(!datatype.isPrimitive()){
			if(objBuff == null){
				int cap = count*datatype.size();
				objBuff = ByteBuffer.allocateDirect(cap);
			}
			else{
				// completely reset the buffer
				objBuff.limit(objBuff.capacity());
				objBuff.rewind();
			}
			fillBuffer(buff, offset, count,datatype,objBuff);
			_buff = objBuff;
		}
		
		stat = _sendrecv_replace(_buff, offset, count, datatype.getHandler(), 
			dest, sendtag, source, recvtag, this.handler);
		if(!datatype.isPrimitive()){
			Object[] objArr = (Object[])buff;
			for(int i = offset;i < (offset+count);i++){
				objArr[i] = datatype.constructFromByteByffer(objBuff);
			}
		}

		return stat;
	}
	private static native Status _sendrecv_replace(
		Object buff,int offset,int count,long datatype,
		int dest,int sendtag,int source,int recvtag,long comm
	);

	// MPI_Barrier
	public void barrier(){
		MPI.checkInitialization();
		_barrier(this.handler);
	}
	private static native void _barrier(long comm);
	// MPI_Ibarrier
	public Request ibarrier(){
		MPI.checkInitialization();
		return _ibarrier(this.handler);
	}
	private static native Request _ibarrier(long comm);
	
	/**
	 * collective communications
	 */
	// MPI_Bcast
	public void bcast(Object buff,int offset,int count,Datatype datatype,
		int root,ByteBuffer objBuff
	){
		MPI.checkInitialization();
		Object _buff = buff;
		// send preparations
		if(!datatype.isPrimitive()){
			if(objBuff == null){
				int cap = count*datatype.size();
				objBuff = ByteBuffer.allocateDirect(cap);
			}
			else{
				// completely reset the buffer
				objBuff.limit(objBuff.capacity());
				objBuff.rewind();
			}
			if(((Object[])buff)[offset] != null){
				// if we are ine receive process then
				// we don't fill the buffer
				fillBuffer(buff, offset, count,datatype,objBuff);
			}
			_buff = objBuff;
		}
		
		_bcast(_buff, offset, count, datatype.getHandler(), 
			root, this.handler);

		if(!datatype.isPrimitive()){
			Object[] objArr = (Object[])buff;
			if(((Object[])buff)[offset] == null){
				// if we are in the receive process, we are going to
				// fill the object array
				for(int i = offset;i < (offset+count);i++){
					objArr[i] = datatype.constructFromByteByffer(objBuff);
				}
			}
		}
	}
	private static native void _bcast(Object buff,int offset,int count,
		long datatype,int root,long comm);
	// MPI_Ibcast
	public Request ibcast(Object buff,int offset, int count,Datatype datatype,int root,
		ByteBuffer objBuff){
		sendRecvInit(buff);
		// TODO: implement object conversation
		if(!datatype.isPrimitive()){
			if(objBuff == null){
				throw new NullPointerException();
			}
			else{
				// completely reset the buffer
				objBuff.limit(objBuff.capacity());
				objBuff.rewind();
			}
			if(((Object[])buff)[offset] != null){
				// if we are ine receive process then
				// we don't fill the buffer
				fillBuffer(buff, offset, count,datatype,objBuff);
			}

			return _ibcast(objBuff, offset, count, datatype.getHandler(), 
				root, this.handler);
		}
		else{
			return _ibcast(buff, offset, count, datatype.getHandler(), 
				root, this.handler);
		}
	}
	private static native Request _ibcast(Object buff,int offset,int count,long datatype,
		int root,long comm);
	// MPI_Scatter
	public void scatter(Object sendbuff, int sendoffset,int sendcount,Datatype sendtype,
		Object recvbuff,int recvoffset,int recvcount,Datatype recvtype,
		int root, ByteBuffer sendObjBuff,ByteBuffer recvObjBuff
	){
		MPI.checkInitialization();
		Object _sendbuff = sendbuff;
		Object _recvbuff = recvbuff;
		// send preparations
		if(sendbuff != null){
			if(rank() == root){
				if(!sendtype.isPrimitive()){
					int _size = size();
					if(sendObjBuff == null){
						int cap = recvcount*sendtype.size()*_size;
						sendObjBuff = ByteBuffer.allocateDirect(cap);
					}
					else{
						// completely reset the buffer
						sendObjBuff.limit(sendObjBuff.capacity());
						sendObjBuff.rewind();
					}
					if(((Object[])sendbuff)[sendoffset] != null){
						// if we are ine receive process then
						// we don't fill the buffer
						fillBuffer(sendbuff, sendoffset, sendcount*_size,sendtype,sendObjBuff);
					}
					_sendbuff = sendObjBuff;
				}
			}
			else{
				_sendbuff = null;
			}
		}
		// receive preparations
		if(recvbuff != null){
			if(!recvtype.isPrimitive()){
				int cap = recvcount*recvtype.size();
				if(recvObjBuff == null){
					recvObjBuff = ByteBuffer.allocateDirect(cap);
				}
				else{
					// completely reset the buffer
					recvObjBuff.limit(recvObjBuff.capacity());
					recvObjBuff.rewind();
				}
				_recvbuff = recvObjBuff;
			}
		}

		_scatter(_sendbuff, sendoffset, sendcount, sendtype.getHandler(),  
			_recvbuff, recvoffset, recvcount, recvtype.getHandler(), 
			root,this.handler);

		if(recvbuff != null){
			if(!recvtype.isPrimitive()){
				Object[] objArr = (Object[])recvbuff;
				for(int i = recvoffset;i < (recvoffset+recvcount);i++){
					objArr[i] = recvtype.constructFromByteByffer(recvObjBuff);
				}
			}
		}
	}
	private static native void _scatter(Object sendbuff,int sendoffset,int sendcount,long sendtype,
		Object recvbuff,int recvoffset,int recvcount,long recvtype,
		int root, long comm);
	// MPI_Iscatter
	public Request iscatter(Object sendbuff, int sendoffset,int sendcount,Datatype sendtype,
		Object recvbuff,int recvoffset,int recvcount,Datatype recvtype,
		int root, ByteBuffer sendObjBuff,ByteBuffer recvObjBuff
	){
		Request req = null;

		MPI.checkInitialization();
		Object _sendbuff = sendbuff;
		Object _recvbuff = recvbuff;
		// send preparations
		if(sendbuff != null){
			if(rank() == root){
				if(!sendtype.isPrimitive()){
					int _size = size();
					if(sendObjBuff == null){
						int cap = recvcount*sendtype.size()*_size;
						sendObjBuff = ByteBuffer.allocateDirect(cap);
					}
					else{
						// completely reset the buffer
						sendObjBuff.limit(sendObjBuff.capacity());
						sendObjBuff.rewind();
					}
					if(((Object[])sendbuff)[sendoffset] != null){
						// if we are ine receive process then
						// we don't fill the buffer
						fillBuffer(sendbuff, sendoffset, sendcount*_size,sendtype,sendObjBuff);
					}
					_sendbuff = sendObjBuff;
				}
			}
			else{
				_sendbuff = null;
			}
		}
		// receive preparations
		if(recvbuff != null){
			if(!recvtype.isPrimitive()){
				int cap = recvcount*recvtype.size();
				if(recvObjBuff == null){
					throw new NullPointerException("recvObjBuff is null!");
				}
				else{
					// completely reset the buffer
					recvObjBuff.limit(recvObjBuff.capacity());
					recvObjBuff.rewind();
				}
				_recvbuff = recvObjBuff;
			}
		}

		req = _iscatter(_sendbuff, sendoffset, sendcount, sendtype.getHandler(),  
			_recvbuff, recvoffset, recvcount, recvtype.getHandler(), 
			root,this.handler);

		return req;
	}
	private static native Request _iscatter(
		Object sendbuff,int sendoffset, int sendcount, long sendtype,
		Object recvbuff,int recvoffset,int recvcount,long recvtype,
		int root, long comm);
	// MPI_Gather
	public void gather(
		Object sendbuff,int sendoffset,int sendcount,Datatype sendtype,
		Object recvbuff,int recvoffset,int recvcount,Datatype recvtype,
		int root,ByteBuffer sendObjBuff,ByteBuffer recvObjBuff
	){
		MPI.checkInitialization();
		Object _sendbuff = sendbuff;
		Object _recvbuff = recvbuff;
		int _size = size();

		// send preparations
		if(sendbuff != null){
			if(!sendtype.isPrimitive()){
				if(sendObjBuff == null){
					int cap = recvcount*sendtype.size();
					sendObjBuff = ByteBuffer.allocateDirect(cap);
				}
				else{
					// completely reset the buffer
					sendObjBuff.limit(sendObjBuff.capacity());
					sendObjBuff.rewind();
				}
				if(((Object[])sendbuff)[sendoffset] != null){
					// if we are ine receive process then
					// we don't fill the buffer
					fillBuffer(sendbuff, sendoffset, sendcount,sendtype,sendObjBuff);
				}
				_sendbuff = sendObjBuff;
			}
		}
		// receive preparations
		if(recvbuff != null){
			if(!recvtype.isPrimitive()){
				int cap = recvcount*recvtype.size()*_size;
				if(recvObjBuff == null){
					recvObjBuff = ByteBuffer.allocateDirect(cap);
				}
				else{
					// completely reset the buffer
					recvObjBuff.limit(recvObjBuff.capacity());
					recvObjBuff.rewind();
				}
				_recvbuff = recvObjBuff;
			}
		}

		_gather(_sendbuff, sendoffset, sendcount, sendtype.getHandler(),  
			_recvbuff, recvoffset, recvcount, recvtype.getHandler(), 
			root,this.handler);

		if(recvbuff != null){
			if(!recvtype.isPrimitive()){
				if(rank() == root){
					Object[] objArr = (Object[])recvbuff;
					for(int i = recvoffset;i < (recvoffset+recvcount*_size);i++){
						objArr[i] = recvtype.constructFromByteByffer(recvObjBuff);
					}
				}
			}
		}
	}
	private static native void _gather(
		Object sendbuff,int sendoffset,int sendcount,long sendtype,
		Object recvbuff,int recvoffset,int recvcount,long recvtype,
		int root,long comm);
	// MPI_IGather
	public Request igather(
		Object sendbuff,int sendoffset,int sendcount,Datatype sendtype,
		Object recvbuff,int recvoffset,int recvcount,Datatype recvtype,
		int root,ByteBuffer sendObjBuff,ByteBuffer recvObjBuff
	){
		Request req = null;
		
		MPI.checkInitialization();
		Object _sendbuff = sendbuff;
		Object _recvbuff = recvbuff;
		int _size = size();

		// send preparations
		if(sendbuff != null){
			if(!sendtype.isPrimitive()){
				if(sendObjBuff == null){
					int cap = recvcount*sendtype.size();
					sendObjBuff = ByteBuffer.allocateDirect(cap);
				}
				else{
					// completely reset the buffer
					sendObjBuff.limit(sendObjBuff.capacity());
					sendObjBuff.rewind();
				}
				if(((Object[])sendbuff)[sendoffset] != null){
					// if we are ine receive process then
					// we don't fill the buffer
					fillBuffer(sendbuff, sendoffset, sendcount,sendtype,sendObjBuff);
				}
				_sendbuff = sendObjBuff;
			}
		}
		// receive preparations
		if(recvbuff != null){
			if(rank() == root){
				if(!recvtype.isPrimitive()){
					if(recvObjBuff == null){
						throw new NullPointerException("recvObjBuff is null!");
					}
					else{
						// completely reset the buffer
						recvObjBuff.limit(recvObjBuff.capacity());
						recvObjBuff.rewind();
					}
					_recvbuff = recvObjBuff;
				}
			}
			else{
				_recvbuff = null;
			}
		}

		req = _igather(_sendbuff, sendoffset, sendcount, sendtype.getHandler(),  
			_recvbuff, recvoffset, recvcount, recvtype.getHandler(), 
			root,this.handler);

		return req;
	}
	private static native Request _igather(
		Object sendbuff,int sendoffset,int sendcount,long sendtype,
		Object recvbuff,int recvoffset,int recvcount,long recvtype,
		int root,long comm);
	// MPI_Allgather
	public void allgather(
		Object sendbuff,int sendoffset,int sendcount,Datatype sendtype,
		Object recvbuff,int recvoffset,int recvcount,Datatype recvtype,
		ByteBuffer sendObjBuff,ByteBuffer recvObjBuff
	){
		MPI.checkInitialization();
		Object _sendbuff = sendbuff;
		Object _recvbuff = recvbuff;
		int _size = size();

		// send preparations
		if(sendbuff != null){
			if(!sendtype.isPrimitive()){
				if(sendObjBuff == null){
					int cap = recvcount*sendtype.size();
					sendObjBuff = ByteBuffer.allocateDirect(cap);
				}
				else{
					// completely reset the buffer
					sendObjBuff.limit(sendObjBuff.capacity());
					sendObjBuff.rewind();
				}
				if(((Object[])sendbuff)[sendoffset] != null){
					// if we are ine receive process then
					// we don't fill the buffer
					fillBuffer(sendbuff, sendoffset, sendcount,sendtype,sendObjBuff);
				}
				_sendbuff = sendObjBuff;
			}
		}
		// receive preparations
		if(recvbuff != null){
			if(!recvtype.isPrimitive()){
				int cap = recvcount*recvtype.size()*_size;
				if(recvObjBuff == null){
					recvObjBuff = ByteBuffer.allocateDirect(cap);
				}
				else{
					// completely reset the buffer
					recvObjBuff.limit(recvObjBuff.capacity());
					recvObjBuff.rewind();
				}
				_recvbuff = recvObjBuff;
			}
		}

		_allgather(_sendbuff, sendoffset, sendcount, sendtype.getHandler(),  
			_recvbuff, recvoffset, recvcount, recvtype.getHandler(), 
			this.handler);

		if(recvbuff != null){
			if(!recvtype.isPrimitive()){
				Object[] objArr = (Object[])recvbuff;
				for(int i = recvoffset;i < (recvoffset+recvcount*_size);i++){
					objArr[i] = recvtype.constructFromByteByffer(recvObjBuff);
				}	
			}
		}
	}
	private static native void _allgather(
		Object sendbuff, int sendoffset,int sendcount,long sendtype,
		Object recvbuff, int recvoffset,int recvcount,long recvtype,
		long comm
	);
	// MPI_Iallgather
	public Request iallgather(
		Object sendbuff,int sendoffset,int sendcount,Datatype sendtype,
		Object recvbuff,int recvoffset,int recvcount,Datatype recvtype,
		ByteBuffer sendObjBuff,ByteBuffer recvObjBuff
	){
		Request req = null;

		MPI.checkInitialization();
		Object _sendbuff = sendbuff;
		Object _recvbuff = recvbuff;

		// send preparations
		if(sendbuff != null){
			if(!sendtype.isPrimitive()){
				if(sendObjBuff == null){
					int cap = recvcount*sendtype.size();
					sendObjBuff = ByteBuffer.allocateDirect(cap);
				}
				else{
					// completely reset the buffer
					sendObjBuff.limit(sendObjBuff.capacity());
					sendObjBuff.rewind();
				}
				if(((Object[])sendbuff)[sendoffset] != null){
					// if we are ine receive process then
					// we don't fill the buffer
					fillBuffer(sendbuff, sendoffset, sendcount,sendtype,sendObjBuff);
				}
				_sendbuff = sendObjBuff;
			}
		}
		// receive preparations
		if(recvbuff != null){
			if(!recvtype.isPrimitive()){
				if(recvObjBuff == null){
					throw new NullPointerException("recvObjBuff is null!");
				}
				else{
					// completely reset the buffer
					recvObjBuff.limit(recvObjBuff.capacity());
					recvObjBuff.rewind();
				}
				_recvbuff = recvObjBuff;
			}
		}

		req = _iallgather(_sendbuff, sendoffset, sendcount, sendtype.getHandler(),  
			_recvbuff, recvoffset, recvcount, recvtype.getHandler(), 
			this.handler);

		return req;
	}
	private static native Request _iallgather(
		Object sendbuff, int sendoffset,int sendcount,long sendtype,
		Object recvbuff, int recvoffset,int recvcount,long recvtype,
		long comm);
	// MPI_Alltoall
	public void alltoall(
		Object sendbuff,int sendoffset,int sendcount,Datatype sendtype,
		Object recvbuff,int recvoffset,int recvcount,Datatype recvtype,
		ByteBuffer sendObjBuff,ByteBuffer recvObjBuff
	){
		MPI.checkInitialization();
		Object _sendbuff = sendbuff;
		Object _recvbuff = recvbuff;
		int _size = size();

		// send preparations
		if(sendbuff != null){
			if(!sendtype.isPrimitive()){
				if(sendObjBuff == null){
					int cap = recvcount*sendtype.size()*_size;
					sendObjBuff = ByteBuffer.allocateDirect(cap);
				}
				else{
					// completely reset the buffer
					sendObjBuff.limit(sendObjBuff.capacity());
					sendObjBuff.rewind();
				}
				if(((Object[])sendbuff)[sendoffset] != null){
					// if we are ine receive process then
					// we don't fill the buffer
					fillBuffer(sendbuff, sendoffset, sendcount*_size,sendtype,sendObjBuff);
				}
				_sendbuff = sendObjBuff;
			}
		}
		// receive preparations
		if(recvbuff != null){
			if(!recvtype.isPrimitive()){
				int cap = recvcount*recvtype.size()*_size;
				if(recvObjBuff == null){
					recvObjBuff = ByteBuffer.allocateDirect(cap);
				}
				else{
					// completely reset the buffer
					recvObjBuff.limit(recvObjBuff.capacity());
					recvObjBuff.rewind();
				}
				_recvbuff = recvObjBuff;
			}
		}

		_alltoall(_sendbuff, sendoffset, sendcount, sendtype.getHandler(),  
			_recvbuff, recvoffset, recvcount, recvtype.getHandler(), 
			this.handler);

		if(recvbuff != null){
			if(!recvtype.isPrimitive()){
				Object[] objArr = (Object[])recvbuff;
				for(int i = recvoffset;i < (recvoffset+recvcount*_size);i++){
					objArr[i] = recvtype.constructFromByteByffer(recvObjBuff);
				}	
			}
		}
	}
	private static native void _alltoall(
		Object sendbuff, int sendoffset,int sendcount,long sendtype,
		Object recvbuff, int recvoffset,int recvcount,long recvtype,
		long comm);
	// MPI_Ialltoall
	public Request ialltoall(
		Object sendbuff,int sendoffset,int sendcount,Datatype sendtype,
		Object recvbuff,int recvoffset,int recvcount,Datatype recvtype,
		ByteBuffer sendObjBuff,ByteBuffer recvObjBuff
	){
		Request req = null;
		Object _sendbuff = sendbuff;
		Object _recvbuff = recvbuff;
		int _size = size();
		MPI.checkInitialization();

		// send preparations
		if(sendbuff != null){
			if(!sendtype.isPrimitive()){
				if(sendObjBuff == null){
					int cap = recvcount*sendtype.size()*_size;
					sendObjBuff = ByteBuffer.allocateDirect(cap);
				}
				else{
					// completely reset the buffer
					sendObjBuff.limit(sendObjBuff.capacity());
					sendObjBuff.rewind();
				}
				if(((Object[])sendbuff)[sendoffset] != null){
					// if we are ine receive process then
					// we don't fill the buffer
					fillBuffer(sendbuff, sendoffset, sendcount*_size,sendtype,sendObjBuff);
				}
				_sendbuff = sendObjBuff;
			}
		}
		// receive preparations
		if(recvbuff != null){
			if(!recvtype.isPrimitive()){
				if(recvObjBuff == null){
					throw new NullPointerException("recvObjBuff is null!");
				}
				else{
					// completely reset the buffer
					recvObjBuff.limit(recvObjBuff.capacity());
					recvObjBuff.rewind();
				}
				_recvbuff = recvObjBuff;
			}
		}

		req = _ialltoall(_sendbuff, sendoffset, sendcount, sendtype.getHandler(),  
			_recvbuff, recvoffset, recvcount, recvtype.getHandler(), 
			this.handler);

		return req;
	}
	private static native Request _ialltoall(
		Object sendbuff, int sendoffset,int sendcount,long sendtype,
		Object recvbuff, int recvoffset,int recvcount,long recvtype,
		long comm);
	// MPI_Reduce
	public void reduce(Object sendbuff,Object recvbuff,
		int sendoffset,int recvoffset,int count,Datatype datatype,Op op,int root,
		ByteBuffer sendObjBuff,ByteBuffer recvObjBuff
	){
		Object _sendbuff = sendbuff;
		Object _recvbuff = recvbuff;
		MPI.checkInitialization();

		// send preparations
		if(sendbuff != null){
			if(!datatype.isPrimitive()){
				if(sendObjBuff == null){
					int cap = count*datatype.size();
					sendObjBuff = ByteBuffer.allocateDirect(cap);
				}
				else{
					// completely reset the buffer
					sendObjBuff.limit(sendObjBuff.capacity());
					sendObjBuff.rewind();
				}
				if(((Object[])sendbuff)[sendoffset] != null){
					// if we are ine receive process then
					// we don't fill the buffer
					fillBuffer(sendbuff, sendoffset, count,datatype,sendObjBuff);
				}
				_sendbuff = sendObjBuff;
			}
		}
		// receive preparations
		if(recvbuff != null){
			if(!datatype.isPrimitive()){
				int cap = count*datatype.size();
				if(recvObjBuff == null){
					recvObjBuff = ByteBuffer.allocateDirect(cap);
				}
				else{
					// completely reset the buffer
					recvObjBuff.limit(recvObjBuff.capacity());
					recvObjBuff.rewind();
				}
				_recvbuff = recvObjBuff;
			}
		}

		_reduce(_sendbuff, _recvbuff, recvoffset, sendoffset, count,
			datatype.getHandler(), op.getHandler(), root, this.handler);
		
		if(recvbuff != null){
			if(!datatype.isPrimitive()){
				Object[] objArr = (Object[])recvbuff;
				for(int i = recvoffset;i < (recvoffset+count);i++){
					objArr[i] = datatype.constructFromByteByffer(recvObjBuff);
				}	
			}
		}
	}
	private static native void _reduce(Object sendbuff,Object recvbuff,
		int recvoffset,int sendoffset,int sendcount,long datatype,long op,int root,long comm);
	public  Request ireduce(Object sendbuff,Object recvbuff,
		int sendoffset,int recvoffset,int count,Datatype type,Op op,int root,
		ByteBuffer sendObjBuff,ByteBuffer recvObjBuff
	){
		Request req = null;
		Object _sendbuff = sendbuff;
		Object _recvbuff = recvbuff;
		MPI.checkInitialization();

		// send preparations
		if(sendbuff != null){
			if(!type.isPrimitive()){
				if(sendObjBuff == null){
					int cap = count*type.size();
					sendObjBuff = ByteBuffer.allocateDirect(cap);
				}
				else{
					// completely reset the buffer
					sendObjBuff.limit(sendObjBuff.capacity());
					sendObjBuff.rewind();
				}
				if(((Object[])sendbuff)[sendoffset] != null){
					// if we are ine receive process then
					// we don't fill the buffer
					fillBuffer(sendbuff, sendoffset, count,type,sendObjBuff);
				}
				_sendbuff = sendObjBuff;
			}
		}
		// receive preparations
		if(recvbuff != null){
			if(!type.isPrimitive()){
				int cap = count*type.size();
				if(recvObjBuff == null){
					recvObjBuff = ByteBuffer.allocateDirect(cap);
				}
				else{
					// completely reset the buffer
					recvObjBuff.limit(recvObjBuff.capacity());
					recvObjBuff.rewind();
				}
				_recvbuff = recvObjBuff;
			}
		}

		req = _ireduce(_sendbuff, _recvbuff, sendoffset, recvoffset, count,
			type.getHandler(), op.getHandler(), root,this.handler);

		return req;
	}
	private static native Request _ireduce(Object sendBuff,Object recvBuff,
		int sendoffset,int recvoffset,int sendcount,long datatype,long op,int root,long comm);
	public void allreduce(Object sendbuff,Object recvbuff,int sendoffset,int recvoffset,
		int count,Datatype datatype,Op op,ByteBuffer sendObjBuff,ByteBuffer recvObjBuff
	){
		Object _sendbuff = sendbuff;
		Object _recvbuff = recvbuff;
		MPI.checkInitialization();

		// send preparations
		if(sendbuff != null){
			if(!datatype.isPrimitive()){
				if(sendObjBuff == null){
					int cap = count*datatype.size();
					sendObjBuff = ByteBuffer.allocateDirect(cap);
				}
				else{
					// completely reset the buffer
					sendObjBuff.limit(sendObjBuff.capacity());
					sendObjBuff.rewind();
				}
				if(((Object[])sendbuff)[sendoffset] != null){
					// if we are ine receive process then
					// we don't fill the buffer
					fillBuffer(sendbuff, sendoffset, count,datatype,sendObjBuff);
				}
				_sendbuff = sendObjBuff;
			}
		}
		// receive preparations
		if(recvbuff != null){
			if(!datatype.isPrimitive()){
				int cap = count*datatype.size();
				if(recvObjBuff == null){
					recvObjBuff = ByteBuffer.allocateDirect(cap);
				}
				else{
					// completely reset the buffer
					recvObjBuff.limit(recvObjBuff.capacity());
					recvObjBuff.rewind();
				}
				_recvbuff = recvObjBuff;
			}
		}

		_allreduce(_sendbuff, _recvbuff, recvoffset, sendoffset, count,
			datatype.getHandler(), op.getHandler(), this.handler);
		
		if(recvbuff != null){
			if(!datatype.isPrimitive()){
				Object[] objArr = (Object[])recvbuff;
				for(int i = recvoffset;i < (recvoffset+count);i++){
					objArr[i] = datatype.constructFromByteByffer(recvObjBuff);
				}	
			}
		}
	}
	private static native void _allreduce(Object sendbuff,Object recbuff,int sendoffset,int recvoffset,
		int count,long type,long op,long comm);
	public  Request iallreduce(Object sendbuff,Object recvbuff,
		int sendoffset,int recvoffset,int count,Datatype type,Op op,
		ByteBuffer sendObjBuff,ByteBuffer recvObjBuff
	){
		Request req = null;
		Object _sendbuff = sendbuff;
		Object _recvbuff = recvbuff;
		MPI.checkInitialization();

		// send preparations
		if(sendbuff != null){
			if(!type.isPrimitive()){
				if(sendObjBuff == null){
					int cap = count*type.size();
					sendObjBuff = ByteBuffer.allocateDirect(cap);
				}
				else{
					// completely reset the buffer
					sendObjBuff.limit(sendObjBuff.capacity());
					sendObjBuff.rewind();
				}
				if(((Object[])sendbuff)[sendoffset] != null){
					// if we are ine receive process then
					// we don't fill the buffer
					fillBuffer(sendbuff, sendoffset, count,type,sendObjBuff);
				}
				_sendbuff = sendObjBuff;
			}
		}
		// receive preparations
		if(recvbuff != null){
			if(!type.isPrimitive()){
				int cap = count*type.size();
				if(recvObjBuff == null){
					recvObjBuff = ByteBuffer.allocateDirect(cap);
				}
				else{
					// completely reset the buffer
					recvObjBuff.limit(recvObjBuff.capacity());
					recvObjBuff.rewind();
				}
				_recvbuff = recvObjBuff;
			}
		}

		req = _iallreduce(_sendbuff, _recvbuff, sendoffset, recvoffset, count,
			type.getHandler(), op.getHandler(),this.handler);

		return req;
	}
	private static native Request _iallreduce(Object sendBuff,Object recvBuff,
		int sendoffset,int recvoffset,int sendcount,long datatype,long op,long comm);
}
