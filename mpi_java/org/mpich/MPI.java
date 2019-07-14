package org.mpich;

import java.io.Serializable;
import java.nio.ByteBuffer;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

import org.mpich.MPI_Integer_ref;
import org.mpich.MPI_Message;
import org.mpich.MPI_Request;
import org.mpich.MPI_Status;
import org.mpich.MPI_Utils;
import org.mpich.MPI_Win_buffer;

/**
 * This is gooing to be the main point for the java
 * part of the binding code.
 */

public class MPI {
    
	private static Map<Integer,byte[]> ObjectBuffer;
    static{
		ObjectBuffer = Collections.synchronizedMap(new HashMap<>());
        System.loadLibrary("MpiJava");
    }

    // null objects
    public static final int MPI_COMM_NULL = 0x04000000;
    // public static final int MPI_OP_NULL = 0x18000000;
    // public static final int MPI_GROUP_NULL = 0x08000000;
    // public static final int MPI_DATATYPE_NULL = 0x0c000000;
    // public static final int MPI_REQUEST_NULL = 0x2c000000;
    // public static final int MPI_ERRHANDLER_NULL =0x14000000;
    // public static final int MPI_MESSAGE_NULL = 0x2c000000;
    // public static final int MPI_MESSAGE_NO_PROC = 0x6c000000;
    // TODO: String object!
    // public static java types
    // TODO: set them from mpi
    public static final int BYTE = 0x4c00010d;
    public static final int SHORT = 0x4c000203;
    public static final int INT = 0x4c000439;
    public static final int LONG = 0x4c00083a;
    public static final int FLOAT = 0x4c00040a;
    public static final int DOUBLE = 0x4c00080b;
    public static final int BOOLЕАN = 0x4c000102;
		public static final int CHAR = 0x4c000204;
		public static final int BYTE_BUFFER = 8;
		public static final int SHORT_BUFFER = 7;
		public static final int INT_BUFFER = 6;
		public static final int LONG_BUFFER = 5;
		public static final int FLOAT_BUFFER = 4;
		public static final int DOUBLE_BUFFER = 3;
		public static final int BOOLEAN_BUFFER = 2;
		public static final int CHAR_BUFFER = 1;
	public static final int OBJECT = 9;
	// predefined operations
	public static final int  MPI_MAX =      0x58000001;
	public static final int  MPI_MIN =      0x58000002;
	public static final int  MPI_SUM =      0x58000003;
	public static final int  MPI_PROD =     0x58000004;
	public static final int  MPI_LAND =     0x58000005;
	public static final int  MPI_BAND =     0x58000006;
	public static final int  MPI_LOR =      0x58000007;
	public static final int  MPI_BOR =      0x58000008;
	public static final int  MPI_LXOR =     0x58000009;
	public static final int  MPI_BXOR =     0x5800000a;
	public static final int  MPI_MINLOC =   0x5800000b;
	public static final int  MPI_MAXLOC =   0x5800000c;
	public static final int  MPI_REPLACE =  0x5800000d;
	public static final int  MPI_NO_OP =    0x5800000e;
	// MPI IO
	public static final int MPI_MODE_RDONLY =               2;  /* ADIO_RDONLY */
	public static final int MPI_MODE_RDWR =                 8;  /* ADIO_RDWR  */
	public static final int MPI_MODE_WRONLY =               4;  /* ADIO_WRONLY  */
	public static final int MPI_MODE_CREATE =               1;  /* ADIO_CREATE */ 
	public static final int MPI_MODE_EXCL =                64;  /* ADIO_EXCL */
	public static final int MPI_MODE_DELETE_ON_CLOSE =     16;  /* ADIO_DELETE_ON_CLOSE */
	public static final int MPI_MODE_UNIQUE_OPEN =         32;  /* ADIO_UNIQUE_OPEN */
	public static final int MPI_MODE_APPEND =             128;  /* ADIO_APPEND */
	public static final int MPI_MODE_SEQUENTIAL =         256;  /* ADIO_SEQUENTIAL */

		public static final int MPI_UNDEFINED = -32766;
		public static final int MPI_INFO_NULL = 0x1c000000;

    public static final int MPI_COMM_WORLD = 0x44000000;
    // init function
    public static native int MPI_Init(String[] argv);
    // finalize function
    public static native int MPI_Finalize();

    /**
     * Point to Point Communication
     */

    // blocking point to point functions
    public static native <T> int MPI_Send(
            T buff, int type, int dest, int tag, int comm);
    public static native <T> int MPI_Bsend(
            T buff,int type,int dest,int tag,int comm);
    public static native <T> int MPI_Ssend(
            T buff,int type,int dest,int tag,int comm);
    public static native <T> int MPI_Rsend(
            T buff,int type,int dest,int tag,int comm);
    public static native <T> int MPI_Recv(
            T buff, int type, int source,int tag,int comm,MPI_Status status);
    // nonblocking point to point functions
    // @note: They all return the MPI_Request hendler!
    public static native <T> int MPI_Isend(
            T buff, int type, int dest, int tag, int comm, MPI_Request request);
    public static native <T> int MPI_Ibsend(
            T buff, int type, int dest, int tag, int comm, MPI_Request request);
    public static native <T> int MPI_Issend(
            T buff, int type, int dest, int tag, int comm, MPI_Request request);
    public static native <T> int MPI_Irsend(
            T buff, int type, int dest, int tag, int comm, MPI_Request request);
    public static native <T> int MPI_Irecv(
            T buff, int type, int source,int tag,int comm, MPI_Request request);
    public static native int MPI_Get_count(MPI_Status status,int datatype);
    public static native int MPI_Buffer_attach(ByteBuffer buffer);
    public static native int MPI_Buffer_detach(ByteBuffer buffer);
    public static native int MPI_Wait(MPI_Request request,MPI_Status status);
    public static native boolean MPI_Test(MPI_Request request,MPI_Status status);
    public static native int MPI_Waitany(MPI_Request[] req,MPI_Status status);
//     public static native int MPI_Waitany(int[] requests,MPI_Status stat);
    public static native int MPI_Testany(MPI_Request[] requests,MPI_Status status);
    public static native int MPI_Waitall(MPI_Request[] requests,MPI_Status[] statuses);
    public static native boolean MPI_Testall(MPI_Request[] requests,MPI_Status[] statuses);
    public static native int MPI_Waitsome(MPI_Request[] requests,int[] indexes,MPI_Status[] statuses);
    public static native int MPI_Testsome(MPI_Request[] requests,int[] indexes,MPI_Status[] statuses);
    public static native boolean MPI_Request_get_status(MPI_Request request,MPI_Status status);
    public static native int MPI_Request_free(MPI_Request request);
    // probe and cancel
    public static native int MPI_Probe(int source,int tag,int comm,MPI_Status status);
    public static native boolean MPI_Iprobe(int source,int tag,int comm,MPI_Status status);
    public static native int MPI_Mprobe(int source,int tag,int comm,MPI_Message msg,MPI_Status status);
    public static native boolean MPI_Improbe(int source,int tag,int comm,MPI_Message msg, MPI_Status status);
    public static native <T> int MPI_Mrecv(
		T buff, int type, MPI_Message message,MPI_Status status);
    public static native <T> int MPI_Imrecv(
        T buff,int type,MPI_Message msg,MPI_Request request);
    public static native int MPI_Cancel(MPI_Request request);
    public static native boolean MPI_Test_cancelled(MPI_Status status);
    // persistent communication
    public static native int MPI_Send_init(
		ByteBuffer buff,int dest,int tag,int comm,MPI_Request request);
    public static native int MPI_Bsend_init(
		ByteBuffer buffer,int dest,int tag,int comm,MPI_Request request);
    public static native int MPI_Ssend_init(
		ByteBuffer buffer,int dest,int tag,int comm,MPI_Request request);
    public static native int MPI_Rsend_init(
		ByteBuffer buffer,int dest,int tag,int comm,MPI_Request request);
    public static native int MPI_Recv_init(
		ByteBuffer buff,int source,int tag,int comm,MPI_Request request);
    public static native int MPI_Start(MPI_Request request);
    public static native int MPI_Startall(MPI_Request[] requests);
    public static native <T,V> int MPI_Sendrecv(
		T sendBuff,int snedType,int dest,int sendTag,
		V recvBuff,int recvType,int source,int recvTag,
		int comm,MPI_Status status);
    public static native <T> int MPI_Sendrecv_replace(
		T buff, int type, int dest,int sendTag,
		int source,int recvTag,int comm,MPI_Status stat);

	/**     
	 * Collective Communication
	 */
	public static native int MPI_Barrier(int comm);
	public static native int MPI_Ibarrier(int comm,MPI_Request req);
	
	// Bcast functions
	public static native <T> int MPI_Bcast(T buff,int datatype,int root,int comm);
	public static native <T> int MPI_Ibcast(T buff,int datatype,int root,int comm,MPI_Request req);
	// gather&scatter functions
	// TODO: Gather$Scatter objects
	public static native <T,V> int MPI_Scatter(
		T sendbuff,int sendtype,int sendcount,
		V recvbuff,int recvcount,int recvtype,
		int root,int comm);    
	public static native <T,V> int MPI_Gather(
		T sendbuff,int sendcount,int sendtype,
		V recvbuff,int recvcount,int recvtype,
		int root,int comm);
	public static native <T,V> int MPI_Scatterv(
		T sendbuff,int[] sendcounts,int[] dips,int sendtype,
		V recvbuff,int recvcount,int recvtype,
		int root,int comm);
	public static native <T,V> int MPI_Gatherv(
		T sendbuff,int sendcount,int sendtype,
		V recvbuff, int[] recvcounts,int[] disp,int recvtype,
		int root,int comm);
	public static native <T,V> int MPI_Iscatterv(
		T sendbuff,int[] sendcounts,int[] dips,int sendtype,
		V recvbuff,int recvcount,int recvtype,
		int root,int comm,MPI_Request req);
	public static native <T,V> int MPI_Igatherv(
		T sendbuff,int sendcount,int sendtype,
		V recvbuff, int[] recvcounts,int[] disp,int recvtype,
		int root,int comm,MPI_Request req);
	public static native <T,V> int MPI_2DScatter(
		T sendbuff,int sendcount,int sendtype,
		V recvbuff,int recvcount,int recvtype,
		int root,int comm);    
	public static native <T,V> int MPI_2DGather(
		T sendbuff,int sendcount,int sendtype,
		V recvbuff,int recvcount,int recvtype,
		int root,int comm);
	public static native <T,V> int MPI_Iscatter(
		T sendbuff,int sendtype,int sendcount,
		V recvbuff,int recvcount,int recvtype,
		int root,int comm,MPI_Request req);    
	public static native <T,V> int MPI_Igather(
		T sendbuff,int sendcount,int sendtype,
		V recvbuff,int recvcount,int recvtype,
		int root,int comm,MPI_Request req);
	public static native <T,V> int MPI_I2DScatter(
		T sendbuff,int sendcount,int sendtype,
		V recvbuff,int recvcount,int recvtype,
		int root,int comm);    
	public static native <T,V> int MPI_I2DGather(
		T sendbuff,int sendcount,int sendtype,
		V recvbuff,int recvcount,int recvtype,
		int root,int comm);
	public static native <T,V> int MPI_Allgather(
		T sendbuff,int sendcount,int sendtype,
		V recvbuff,int recvcount,
		int recvtype,int comm);
	public static native <T,V> int MPI_Allgatherv(
		T sendbuff,int sendcount,int sendtype,
		V recvbuff,int[] recvcounts,int[] disp,int recvtype,
		int comm);
	public static native <T,V> int MPI_Iallgatherv(
		T sendbuff,int sendcount,int sendtype,
		V recvbuff,int[] recvcounts,int[] disp,int recvtype,
		int comm,MPI_Request req);
	public static native <T,V> int MPI_Iallgather(
		T sendbuff,int sendcount,int sendtype,
		V recvbuff,int recvcount,int recvtype,
		int comm,MPI_Request req);
	public static native <T,V> int MPI_Alltoall(
		T sendbuff,int sendcount,int sendtype,
		V recvbuff,int recvcount,int recvtype,
		int comm);
	public static native <T,V> int MPI_Ialltoall(
		T sendbuff,int sendcount,int sendtype,
		V recvbuff,int recvcount,int recvtype,
		int comm,MPI_Request req);
	public static native <T,V> int MPI_Alltoallv(
		T sendbuff,int[] sendcounts, int[] senddisp,int sendtype,
		V recvbuff,int[] recvcounts, int[] recvdisp,int recbtype,
		int comm);
	public static native <T,V> int MPI_Ialltoallv(
		T sendbuff,int[] sendcounts, int[] senddisp,int sendtype,
		V recvbuff,int[] recvcounts, int[] recvdisp,int recbtype,
		int comm,MPI_Request req);
	public static native <T> int MPI_Reduce(
		T sendBuff,T recvBuff,int count,int datatype,
		int op,int root,int comm);
	public static native <T> int MPI_Ireduce(
		T sendBuff,T recvBuff,int count,int datatype,
		int op,int root,int comm,MPI_Request req);
	public static native <T> int MPI_Allreduce(
		T sendBuff,T recvBuff,int count,int datatype,
		int op,int comm);
	public static native <T> int MPI_Iallreduce(
		T sendBuff,T recvBuff,int count,int datatype,
		int op,int comm,MPI_Request req);
	public static native <T> int MPI_Reduce_scatter(
		T sendbuff,T recvbuff,int[] counts,int type,
		int op,int comm);
	public static native <T> int MPI_Ireduce_scatter(
		T sendbuff,T recvbuff,int[] counts,int type,
		int op,int comm,MPI_Request req);
	public static native <T> int MPI_Reduce_scatter_block(
		T sendbuff,T recvbuff,int count,int type,
		int op,int comm);
	public static native <T> int MPI_Ireduce_scatter_block(
		T sendbuff,T recvbuff,int count,int type,
		int op,int comm,MPI_Request req);
	public static native <T> int MPI_Scan(
		T sendbuff,T recvbuff,int count,int type,
		int op,int comm);
	public static native <T> int MPI_Iscan(
		T sendbuff,T recvbuff,int count,int type,
		int op,int comm,MPI_Request req);
	public static native <T> int MPI_Exscan(
		T sendbuff,T recvbuff,int count,int type,
		int op,int comm);
	public static native <T> int MPI_Iexscan(
		T sendbuff,T recvbuff,int count,int type,
		int op,int comm,MPI_Request req);

		// group management
		public static native int MPI_Group_size(int group);
		public static native int MPI_Group_rank(int group);
		public static native int MPI_Group_translate_ranks(
			int group1,int n,int[] ranks1,int group2,int[] ranks2);
		public static native int MPI_Group_compare(int group1,int group2);
		public static native int MPI_Group_union(int group1,int group2);
		public static native int MPI_Group_intersection(int group1, int group2);
		public static native int MPI_Group_difference(int group1, int group2);
		public static native int MPI_Group_incl(int group,int n,int[] ranks);
		public static native int MPI_Group_excl(int group,int n,int[] ranks);
		public static native int MPI_Group_range_incl(int group,int n,
			int[] first,int[] last,int[] stride);
		public static native int MPI_Group_range_excl(int group,int n,
		int[] first,int[] last,int[] stride);
		public static native int MPI_Group_free(int group);
		// communicator management
		// local
		public static native int MPI_Comm_rank(int comm);
		public static native int MPI_Comm_size(int comm);
		public static native int MPI_Comm_compare(int group1, int group2);
		// collective
		public static native int MPI_Comm_dup(int comm);
		public static native int MPI_Comm_dup_with_info(int comm,int info);
		public static native int MPI_Comm_idup(int comm,MPI_Request req);
		public static native int MPI_Comm_create(int comm,int group);
		public static native int MPI_Comm_create_group(int comm,int group,int tag);
		public static native int MPI_Comm_split(int comm,int color,int key);
		public static native int MPI_Comm_split_type(int comm,int split_type,int key,int info);
		public static native int MPI_Comm_free(int comm);
		public static native int MPI_Comm_set_info(int comm,int info);
		public static native int MPI_Comm_get_info(int comm);
		public static native int MPI_Comm_group(int comm);
		// intercomm functions
		public static native int MPI_Comm_test_inter(int comm);
		public static native int MPI_Comm_remote_size(int comm);
		public static native int MPI_Comm_remote_group(int comm);
		public static native int MPI_Intercomm_create(int local_comm,int local_leader,
			int peer_comm,int remote_leader,int tag);
		public static native int MPI_Intercomm_merge(int intercomm,int high);
		public static native int MPI_Comm_set_name(int comm,String str);
		public static native String MPI_Com_get_name(int comm);
		// process toplologies 
		public static native int MPI_Cart_create(int comm_old,int ndims,int[] dims,
			int[] periods,int reorder);
		public static native int MPI_Dims_create(int nnodes,int ndims,int[] dims);
		public static native int MPI_Graph_create(
			int comm_old,int nnodes,int[] indx,
			int[] endges,int reorder);
		public static native int MPI_Dist_graph_create_adjacent(
			int  comm_old,int indegree,int[] sources,int[] sourceweights,
			int outdegree,int[] destinations,int[] destweights,int info,
			int reorder);
		public static native int MPI_Dist_graph_create(
			int comm_old, int n, int[] sources,
			int[] degrees, int[] destinations,
			int[] weights, int info, int reorder);
		public static native int MPI_Test_info(int comm);
		public static native int MPI_Graphdims_get(int comm,
			MPI_Integer_ref nnodes,MPI_Integer_ref nedges);
		public static native int MPI_Graph_get(int comm,int maxindex,int maxedges,
			int[] index,int[] edges);
		public static native int MPI_Cartdim_get(int comm);
		public static native int MPI_Cart_get(int comm,int maxdims,
			int[] dims,int[] periods,int[] coords);
		public static native int MPI_Cart_rank(int comm,
			int[] coords);
		public static native int MPI_Cart_coords(
			int comm, int rank, int maxdims, int[] coords);
		public static native int MPI_Graph_neighbors_count(int comm, int rank);
		public static native int MPI_Graph_neighbors(
			int comm, int rank, int maxneighbors,int[] neighbors);
		public static native int MPI_Dist_graph_neighbors_count(int comm, 
			MPI_Integer_ref indegree, MPI_Integer_ref outdegree, 
			MPI_Integer_ref weighted);
		public static native int MPI_Dist_graph_neighbors(
			int comm, int maxindegree, int[] sources,
			int[] sourceweights, int maxoutdegree, int[] destinations,
			int[] destweights);
		public static native int MPI_Cart_shift(
			int comm, int direction, int disp,
			MPI_Integer_ref rank_source, MPI_Integer_ref rank_dest);
		public static native int MPI_Cart_sub(
			int comm, int[] remain_dims);
		public static native int MPI_Cart_map(
			int comm, int ndims, int[] dims,int[] periods);
		public static native int MPI_Graph_map(
			int comm, int nnodes, int[] index,int[] edges);
		// TODO: Neighber Collective Communications
		// MPI Environmental Management
		public static native int MPI_Get_version();
		public static native String MPI_Get_library_version();
		public static native String MPI_Get_process_name();
		public static native double MPI_Wtime();
		public static native double MPI_Wtick();
		public static native int MPI_Initialized();
		public static native int MPI_Abort(int comm,int errcode);
		public static native int MPI_Finalized();
		// info object
		public static native int MPI_Info_create();
		public static native int MPI_Info_set(int info,
			String key,String value);
		public static native int MPI_Info_delete(int info,String key);
		public static native String MPI_Info_get(int info, String key);
		public static native int MPI_Info_get_valuelen(int info, String key);
		public static native String MPI_Info_get_nthkey(int info, int n);
		public static native int MPI_Info_dup(int info);
		public static native int MPI_Info_free(int info);
		// process managment
		public static native int MPI_Comm_spawn(String command,
			String[] args,int maxprocs,int info,int root,int comm,
			int[] array_of_errcodes);
		public static native int MPI_Comm_get_parent();
		public static native int MPI_Comm_spawn_multiple(
			String[] array_of_commands,String[][] array_of_argv, 
			int[] array_of_maxprocs,int[] array_of_info, 
			int root, int comm, int[] array_of_errcodes);
		public static native int MPI_Comm_disconnect(int comm);
		public static native int MPI_Comm_join(int fd);
		// server toutines
		public static native String MPI_Open_port(int info);
		public static native int MPI_Close_port(String port_name);
		public static native int MPI_Comm_accept(
			String port_name,int info,int root,int comm);
		public static native int MPI_Comm_connect(
			String port_name,int info,int root,int comm);
		// name publising
		public static native int MPI_Publish_name(
			String service_name,int info,String port_name);
		public static native int MPI_Unpublich_name(
			String service_name,int info,String port_name);
		public static native String MPI_Lookup_name(
			String service_name,int info);
		// win objects
		public static native int MPI_Win_create(
			MPI_Win_buffer base,int disp_unit,int info,int comm);
		public static native int MPI_Win_allocate(
			int disp_unit,int info,int comm,MPI_Win_buffer base);
		public static native int MPI_Win_allocate_shared(
			int disp_unit,int info,int comm,MPI_Win_buffer base);
		public static native int MPI_Win_shared_query(
			int win,int rank,MPI_Win_buffer base);
		public static native int MPI_Win_create_dynamic(
			int info,int comm);
		public static native int MPI_Win_attach(
			int win,MPI_Win_buffer base);
		public static native int MPI_Win_detach(
			int win,MPI_Win_buffer base);
		public static native int MPI_Win_free(int win);
		public static native int MPI_Win_get_attr(int win,int win_keyval);
		public static native int MPI_Win_get_group(int win);
		public static native int MPI_Win_set_info(int win,int info);
		public static native int MPI_Win_get_info(int win);
		public static native int MPI_Win_fence(int ass,int win);
		public static native int MPI_Win_start(int group,int ass,int win);
		public static native int MPI_Win_complete(int win);
		public static native int MPI_Win_post(int group,int ass,int win);
		public static native int MPI_Win_wait(int win);
		public static native boolean MPI_Win_test(int win);
		public static native int MPI_Win_lock(
			int lock_type,int rank,int ass,int win);
		public static native int MPI_Win_lock_all(int ass,int win);
		public static native int MPI_Win_unlock(int rank,int win);
		public static native int MPI_Win_unlock_all(int win);
		public static native int MPI_Win_flush(int rank,int win);
		public static native int MPI_Win_flush_all(int win);
		public static native int MPI_Win_flush_local(int rank,int win);
		public static native int MPI_Win_fluch_local_all(int win);
		public static native int MPI_Win_sync(int win);
		// TODO: Address access functions.
		// window communication calls
		public static native int MPI_Put(
			MPI_Win_buffer base,int origin_count,int origin_datatype,
			int target_rank,long target_disp,int target_count,
			int target_datatype,int comm);
		public static native int MPI_Get(
			MPI_Win_buffer base, int origin_count,int origin_datatype,
			int target_rank,long target_disp,int target_count,
			int target_datatype,int win);
		public static native int MPI_Accumulate(
			MPI_Win_buffer base, int origin_count,
			int origin_datatype, int target_rank,
			long target_disp, int target_count,
			int target_datatype, int op, int win);
		public static native <T> int MPI_Get_accumulate(
			MPI_Win_buffer origin_addr, int origin_count,
			int origin_datatype, T result_addr,
			int result_count, int result_datatype,
			int target_rank, long target_disp, int target_count,
			int target_datatype, int op, int win);
		public static native <T> int MPI_Fetch_and_op(
			MPI_Win_buffer origin_addr, T result_addr,
			int datatype, int target_rank, long target_disp,
			int op, int win);
		// TODO: MPI_Compare_and_swap
		// TODO: MPI_Rput
		// TODO: MPI_Rget
		// TODO: MPI_Raccumulate
		// TODO: MPI_Rget_accumulate
		// TODO: external interfaces
		// TODO: Associating Information with Status
		// TODO: MPI and Threads
		// I/O
			// configuration
		public static native long MPI_File_open(
			int comm,String filename,int amode,int info);
		public static native int MPI_File_close(long fh);
		public static native int MPI_File_delete(String filename,int info);
		public static native int MPI_File_set_size(long fh,long size);
		public static native int MPI_File_preallocate(long fh,long size);
		public static native int MPI_File_get_group(long fh);
		public static native int MPI_File_get_amode(long fh);
		public static native int MPI_File_set_info(long fh,int info);
		public static native int MPI_File_get_info(long fh);
		public static native int MPI_File_set_view(
			long fh,long disp,int etype,int filetype,String datarep,int info);
		public static native long MPI_File_get_view_disp(long fh);
		public static native int MPI_File_get_view_etyp(long fh);
		public static native int MPI_File_get_view_filetype(long fh);
		public static native String MPI_File_get_view_datarep(long fh);
		public static native int MPI_File_set_atomicity(
			long fh, boolean flag);
			// access
		public static native <T> int MPI_File_read_at(
			long fh,long offset,T buff,int count,int datatype,
			MPI_Status stat);
		public static native <T> int MPI_File_read_at_all(
			long fh, long offset,T buff,int count,int datatype,
			MPI_Status stat);
		public static native <T> int MPI_File_write_at(
			long fh,long offset,T buff,int datatype,int count,
			MPI_Status stat);
		public static native <T> int MPI_File_write_at_all(
			long fh,long offset,T buff,int count,int datatype,
			MPI_Status stat);
}