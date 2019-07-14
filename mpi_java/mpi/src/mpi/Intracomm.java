package mpi;

import java.nio.ByteBuffer;

import mpi.datatype.Datatype;
import mpi.op.Op;

public class Intracomm extends Comm{

    public Intracomm(){
    }
    
    public  Intracomm(long handler){
		super(handler);
    }

    // MPI_Comm_create_group
    public Intracomm create(Group group,int tag){
        long new_handler = _create_group(this.handler,group.getHandler(),tag);

        return new Intracomm(new_handler);
    }
    private static native long _create_group(long comm,long group,int tag);
    // MPI_Comm_create
    public Intracomm create(Group group){
        long new_handler = _create(this.handler,group.getHandler());

        return new Intracomm(new_handler);
    }
    private static native long _create(long comm,long group);
    // MPI_Comm_split
    public Intracomm split(int color,int key){
        long handler = _split(this.handler,color,key);

        return new Intracomm(handler);
    }
	private static native long _split(long comm,int color,int key);
	// MPI_Comm_split_type
	public Intracomm split_type(int split_type, int key, Info info){
		long handler = _split_type(this.handler, split_type, key, info.getHandler());

		return new Intracomm(handler);
	}
	private static native long _split_type(long comm, int split_type, int key, long info);

	public Intracomm dup(){
		long handler = _dup(this.handler);

		return new Intracomm(handler);
	}
	// MPI_Comm_spawn
	public Intercomm spawn(String command,String[] argv,int maxproc,Info info,int root,
		int offset,int[] error_codes){
		long comm = _spawn(command,argv,maxproc,info.getHandler(),root,this.handler,
			offset,maxproc,error_codes);

		return new Intercomm(comm);
	}
	private static native long _spawn(String command,String[] argv,int mpxproc,long info,
		int root,long comm,int offset,int len, int[] error_code);
	// MPI_Comm_accept
	public Intercomm accept(String portname,Info info,int root){
		long comm = _accept(portname, info.getHandler(), root, this.handler);
		
		return new Intercomm(comm);
	}
	private static native long _accept(String portname,long info,int root, long comm);
	// MPI_Comm_connect
	public Intercomm connect(String portname,Info info,int root){
		long comm = _connect(portname, info.getHandler(), root, this.handler);
		
		return new Intercomm(comm);
	}
	private static native long _connect(String portname,long info,int root,long comm);
	/**
	 * Process Topologies
	 */
	//Cartesian
	// MPI_Cart_create
	public Cart cart_create(int dims_offset,int ndims,int[] dims,int per_offset,
		int[] periods,boolean reorder){
		long cart_comm = _cart_create(this.handler, dims_offset, ndims, dims,per_offset,
			periods, reorder);

		return new Cart(cart_comm,ndims);
	}
	private static native long _cart_create(long comm_old,int dims_offset,int ndims,
		int[] dims,int per_offset,int[] periods,boolean reorder);
	// Graph
	// MPI_Graph_create
	public Graph graph_create(int offset_nodes,int nnodes,int[] indexes,
		int offset_edges,int[] edges,boolean reorder)
	{
		long handler = _graph_create(this.handler, offset_nodes, nnodes, indexes, 
			offset_edges, edges, reorder);

		return new Graph(handler);
	}
	private static native long _graph_create(long comm_old,int offset_nodes,int nnodes,int[] indexes,
		int offset_edges,int[] edges,boolean reorder);
	
	// MPI_Topo_test
	public int topo_test(){
		return _topo_test(this.handler);
	}
	private static native int _topo_test(long comm);
	// distributed graph
	public Intracomm dist_graph_create(int offsetsources, int n, int[] sources,
		int offsetdegrees,int[] degrees, int offsetdestinations, int[] destinations,
		int offsetweights, int[] weights,Info info, boolean reordered
	){
		long dist_graph_comm = _dist_graph_create(this.handler, offsetsources, n, sources, 
			offsetdegrees, degrees, offsetdestinations, destinations, offsetweights, 
			weights, info.getHandler(), reordered);

		return new Intracomm(dist_graph_comm);
	}
	private static native long _dist_graph_create(long comm,int offsetsources, int n, int[] sources,
	int offsetdegrees,int[] degrees, int offsetdestinations, int[] destinations,
	int offsetweights, int[] weights,long info, boolean reordered);
	
	/**
	 * Collective Communications
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
	// TODO: MPI_Reduce_scatter
	// public static native <T> int MPI_Reduce_scatter(
	// 	T sendbuff,T recvbuff,int[] counts,int type,
	// 	int op,int comm);
	// public static native <T> int MPI_Ireduce_scatter(
	// 	T sendbuff,T recvbuff,int[] counts,int type,
	// 	int op,int comm,MPI_Request req);
	// public static native <T> int MPI_Reduce_scatter_block(
	// 	T sendbuff,T recvbuff,int count,int type,
	// 	int op,int comm);
	// public static native <T> int MPI_Ireduce_scatter_block(
	// 	T sendbuff,T recvbuff,int count,int type,
	// 	int op,int comm,MPI_Request req);
	// MPI_Scan
	public void scan (Object sendbuff,Object recvbuff,int sendoffset,int recvoffset,
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

		_scan(_sendbuff, _recvbuff, recvoffset, sendoffset, count,
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
	private native void _scan(Object sendbuff,Object recvbuff,int sendoffset,int recvoffset,
		int count,long datatype,long op,long comm);
	// MPI_Iscan
	public  Request iscan(Object sendbuff,Object recvbuff,
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

		req = _iscan(_sendbuff, _recvbuff, sendoffset, recvoffset, count,
			type.getHandler(), op.getHandler(),this.handler);

		return req;
	}
	private static native Request _iscan(Object sendBuff,Object recvBuff,
		int sendoffset,int recvoffset,int sendcount,long datatype,long op,long comm);
	// MPI_Exscan
	public void exscan (Object sendbuff,Object recvbuff,int sendoffset,int recvoffset,
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

		_exscan(_sendbuff, _recvbuff, recvoffset, sendoffset, count,
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
	private native void _exscan(Object sendbuff,Object recvbuff,int sendoffset,int recvoffset,
		int count,long datatype,long op,long comm);
	// MPI_Iexscan
	public  Request iexscan(Object sendbuff,Object recvbuff,
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

		req = _iexscan(_sendbuff, _recvbuff, sendoffset, recvoffset, count,
			type.getHandler(), op.getHandler(),this.handler);

		return req;
	}
	private static native Request _iexscan(Object sendBuff,Object recvBuff,
		int sendoffset,int recvoffset,int sendcount,long datatype,long op,long comm);
	// TODO: What to do with vector functios!
		// public static native <T,V> int MPI_Scatterv(
	// 	T sendbuff,int[] sendcounts,int[] dips,int sendtype,
	// 	V recvbuff,int recvcount,int recvtype,
	// 	int root,int comm);
	// public static native <T,V> int MPI_Gatherv(
	// 	T sendbuff,int sendcount,int sendtype,
	// 	V recvbuff, int[] recvcounts,int[] disp,int recvtype,
	// 	int root,int comm);
	// public static native <T,V> int MPI_Iscatterv(
	// 	T sendbuff,int[] sendcounts,int[] dips,int sendtype,
	// 	V recvbuff,int recvcount,int recvtype,
	// 	int root,int comm,MPI_Request req);
	// public static native <T,V> int MPI_Igatherv(
	// 	T sendbuff,int sendcount,int sendtype,
	// 	V recvbuff, int[] recvcounts,int[] disp,int recvtype,
	// 	int root,int comm,MPI_Request req);
	// public static native <T,V> int MPI_2DScatter(
	// 	T sendbuff,int sendcount,int sendtype,
	// 	V recvbuff,int recvcount,int recvtype,
	// 	int root,int comm);    
	// public static native <T,V> int MPI_2DGather(
	// 	T sendbuff,int sendcount,int sendtype,
	// 	V recvbuff,int recvcount,int recvtype,
	// 	int root,int comm);
	// public static native <T,V> int MPI_I2DScatter(
	// 	T sendbuff,int sendcount,int sendtype,
	// 	V recvbuff,int recvcount,int recvtype,
	// 	int root,int comm);    
	// public static native <T,V> int MPI_I2DGather(
	// 	T sendbuff,int sendcount,int sendtype,
	// 	V recvbuff,int recvcount,int recvtype,
	// 	int root,int comm);
	// public static native <T,V> int MPI_Allgatherv(
	// 	T sendbuff,int sendcount,int sendtype,
	// 	V recvbuff,int[] recvcounts,int[] disp,int recvtype,
	// 	int comm);
	// public static native <T,V> int MPI_Iallgatherv(
	// 	T sendbuff,int sendcount,int sendtype,
	// 	V recvbuff,int[] recvcounts,int[] disp,int recvtype,
	// 	int comm,MPI_Request req);
	// public static native <T,V> int MPI_Iallgather(
	// 	T sendbuff,int sendcount,int sendtype,
	// 	V recvbuff,int recvcount,int recvtype,
	// 	int comm,MPI_Request req);
	// public static native <T,V> int MPI_Alltoallv(
	// 	T sendbuff,int[] sendcounts, int[] senddisp,int sendtype,
	// 	V recvbuff,int[] recvcounts, int[] recvdisp,int recbtype,
	// 	int comm);
	// public static native <T,V> int MPI_Ialltoallv(
	// 	T sendbuff,int[] sendcounts, int[] senddisp,int sendtype,
	// 	V recvbuff,int[] recvcounts, int[] recvdisp,int recbtype,
	// 	int comm,MPI_Request req);

	/**
	 * Window creation
	 */
	// MPI_Win_create
	public Win win_create(ByteBuffer base,int unit_dips,Info info){
		long win = _win_create(base, unit_dips, info.getHandler(), this.handler);
		
		return new Win(win,base);
	}
	private static native long _win_create(ByteBuffer base,int unit_dips,long info,long comm);
	// MPI_Win_allocate
	public Win win_allocate(int size,int dist_unit,Info info){
		Win win = null;
		Win.Win_allocate_ret win_ret = new Win.Win_allocate_ret();

		_allocate(size, dist_unit, info.getHandler(),this.handler, win_ret);

		win = new Win(win_ret,size);

		return win;
	}
	private static native void _allocate(long size,int disp_unit,long info,long comm,Win.Win_allocate_ret win);
	// MPI_Win_allocate_shared
	public Win win_allocate_shared(int size,int disp_unit,Info info){
		Win win = null;
		Win.Win_allocate_ret win_ret = new Win.Win_allocate_ret();

		_allocate_shared(size, disp_unit, info.getHandler(), this.handler, win_ret);

		win = new Win(win_ret,size);

		return win;
	}
	private static native void _allocate_shared(long size,int disp_unit,long info,long comm,Win.Win_allocate_ret win);
	/**
	 * File oprations
	 */
	// MPI_File_open
	public File file_open(String fname,int amode,Info info){
		long handler = _file_open(this.handler, fname, amode, info.getHandler());

		return new File(handler);
	}
	private static native long _file_open(long comm,String name,int amode,long info);
}
