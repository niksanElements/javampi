package mpi;

import java.nio.ByteBuffer;

import mpi.datatype.Datatype;
import mpi.exception.NotInitializedException;
import mpi.op.Op;

/**
 * MPI class!
 * @author nikolay
 *
 */
public class MPI {

	// TODO: MPI tool part!
	
	// primitive types
	public static final Datatype BYTE;
	public static final Datatype SHORT;
	public static final Datatype INT;
	public static final Datatype LONG;
	public static final Datatype FLOAT;
	public static final Datatype DOUBLE;
	public static final Datatype CHAR;
	public static final Datatype BOOLEAN;
	/**
	 * Those are primitive types too, but they 
	 * use ByteBuffer to transfer the data between 
	 * java and native code. This dosen't require
	 * data to be copied.
	 */
	public static final Datatype BYTE_BUFFER;
	public static final Datatype SHORT_BUFFER;
	public static final Datatype INT_BUFFER;
	public static final Datatype LONG_BUFFER;
	public static final Datatype FLOAT_BUFFER;
	public static final Datatype DOUBLE_BUFFER;
	public static final Datatype CHAR_BUFFER;
	public static final Datatype BOOLEAN_BUFFER;
	// TODO: String datatype

	/**
	 * MPI Collective operations
	 */
	public static final Op MAX;
	public static final Op MIN;
	public static final Op SUM;
	public static final Op PROD;
	public static final Op LAND;
	public static final Op BAND;
	public static final Op LOR;
	public static final Op BOR;
	public static final Op LXOR;
	public static final Op BXOR;
	public static final Op MINLOC;
	public static final Op MAXLOC;
	public static final Op REPLACE;
	
	// a global intracommunicator
	public static final Intracomm COMM_WORLD;
	// self communicator 
	public static final Intracomm COMM_SELF;

	// a empty group
	public static final Group GROUP_EMPTY;

	// compare results
	public static final int  IDENT =      0;
	public static final int  CONGRUENT =  1;
	public static final int  SIMILAR =    2;
	public static final int  UNEQUAL =    3;

	// undefined
	public static final int UNDEFINED = -32766;

	// mpi key values
	public static final int TAG_UB =            0x64400001;
	public static final int HOST =              0x64400003;
	public static final int IO =                0x64400005;
	public static final int WTIME_IS_GLOBAL =   0x64400007;
	public static final int UNIVERSE_SIZE =     0x64400009;
	public static final int LASTUSEDCODE =      0x6440000b;
	public static final int APPNUM =            0x6440000d;

	/* In addition, there are 5 predefined window attributes that are
	defined for every window */
	public static final int WIN_BASE =           0x66000001;
	public static final int WIN_SIZE =           0x66000003;
	public static final int WIN_DISP_UNIT =      0x66000005;
	public static final int WIN_CREATE_FLAVOR =  0x66000007;
	public static final int WIN_MODEL =          0x66000009;

	/* for subarray and darray constructors */
	public static final int ORDER_C =               56;
	public static final int ORDER_FORTRAN =         57;
	public static final int DISTRIBUTE_BLOCK =     121;
	public static final int DISTRIBUTE_CYCLIC =    122;
	public static final int DISTRIBUTE_NONE =      123;
	public static final int DISTRIBUTE_DFLT_DARG =  -49767;

	// topologies
	public static final int GRAPH = 1;
	public static final int CART = 2;
	public static final int DIST_GRAPH = 3;

	// info
	public static final Info INFO_NULL;

	// constants
	public static final int PROC_NULL =     -1;
	public static final int ANY_SOURCE =   	-2;
	public static final int ROOT =          -3;
	public static final int ANY_TAG =       -1;

	// MPI library version
	// TODO: determine in compile time
	public static final int LIB_VERSION = 3;
	public static final int LIB_SUBVERSION = 1;
	// for the future
	public static final	String LIB_NAME = "mpich"; 
	// version of java-mpi
	public static final int VERSION = 0;
	public static final int SUBVERSION = 1;

	/* asserts for one-sided communication */
	public static final int MODE_NOCHECK =       1024;
	public static final int MODE_NOSTORE =       2048;
	public static final int MODE_NOPUT =         4096;
	public static final int MODE_NOPRECEDE =     8192;
	public static final int MODE_NOSUCCEED =    16384;
	
	// lock types
	public static final int LOCK_EXCLUSIVE =  234;
	public static final int LOCK_SHARED =     235;

	/* predefined types for MPI_Comm_split_type */
	public static final int  COMM_TYPE_SHARED =   1;
	
	/** file flag modes */
	public static final int MODE_RDONLY =               2;  /* ADIO_RDONLY */
	public static final int MODE_RDWR =                 8;  /* ADIO_RDWR  */
	public static final int MODE_WRONLY =               4;  /* ADIO_WRONLY  */
	public static final int MODE_CREATE =               1;  /* ADIO_CREATE */ 
	public static final int MODE_EXCL =                64;  /* ADIO_EXCL */
	public static final int MODE_DELETE_ON_CLOSE =     16;  /* ADIO_DELETE_ON_CLOSE */
	public static final int MODE_UNIQUE_OPEN =         32;  /* ADIO_UNIQUE_OPEN */
	public static final int MODE_APPEND =             128;  /* ADIO_APPEND */
	public static final int MODE_SEQUENTIAL =         256;  /* ADIO_SEQUENTIAL */

	/** seek update modes */
	public static final int SEEK_SET =             600;
	public static final int SEEK_CUR =             602;
	public static final int SEEK_END =             604;

	/* For supported thread levels */
	public static final int  THREAD_SINGLE = 0;
	public static final int  THREAD_FUNNELED = 1;
	public static final int  THREAD_SERIALIZED = 2;
	public static final int  THREAD_MULTIPLE = 3;

	static {
		System.loadLibrary("mpi");
		System.loadLibrary("javampi");
		
		// basic types
		BYTE = new mpi.datatype.Byte();
		SHORT = new mpi.datatype.Short();
		INT = new mpi.datatype.Int();;
		LONG = new mpi.datatype.Long();
		FLOAT = new mpi.datatype.Float();
		DOUBLE = new mpi.datatype.Double();
		CHAR = new mpi.datatype.Char();
		BOOLEAN = new mpi.datatype.Boolean();
		BYTE_BUFFER = new Datatype();
		SHORT_BUFFER = new Datatype();
		INT_BUFFER = new Datatype();
		LONG_BUFFER = new Datatype();
		FLOAT_BUFFER = new Datatype();
		DOUBLE_BUFFER = new Datatype();
		CHAR_BUFFER = new Datatype();
		BOOLEAN_BUFFER = new Datatype();
		
		// communicators
		COMM_WORLD = new Intracomm();
		// TODO: set COMM_SELF inside the native code
		COMM_SELF = new Intracomm(0x44000001);

		// collective operation
		MAX = new Op();
		MIN = new Op();
		SUM = new Op();
		PROD = new Op();
		LAND = new Op();
		BAND = new Op();
		LOR = new Op();
		BOR = new Op();
		LXOR = new Op();
		BXOR = new Op();
		MINLOC = new Op();
		MAXLOC = new Op();
		REPLACE = new Op();

		// GROUPS
		GROUP_EMPTY = new Group();

		// info
		INFO_NULL = new Info(0x1c000000); // TODO: set initialize the handler form native code

		initNative();
	}
	
	private static boolean isInitialized;
	private static boolean isFinalized;
	
	/**
	 * Initialize all handlers!
	 */
	private static native void initNative();
	
	public static void Init(String[] args) {
		isInitialized = true;
		_init(args);
	}
	public static int Init_thread(String[] args,int required){
		isInitialized = true;

		return _init_thread(args, required);
	}
	public static void Finalize() {
		isInitialized = false;
		isFinalized = true;
		_finalize();
	}

	/**
	 * JAVA_MPI
	 * version 0.0.1
	 * @return
	 */
	public int jni_interface_version(){
		return 0x000001;
	}
	
	private static native void _init(String[] args);
	private static native int _init_thread(String[] args,int required);
	private static native void _finalize();
	
	/**
	 * This function is used by Comm.bsend (MPI_BSend)
	 * @param buff
	 */
	public static void buffer_attach(ByteBuffer buff) {
			_buffer_attach(buff);
	}
	/**
	 * This function is used by Comm.bsend (MPI_BSend)
	 * @param buff
	 */
	public static void buffer_detach(ByteBuffer buff) {
		_buffer_detach(buff);
	}
	private static native void _buffer_attach(ByteBuffer buff);
	private static native void _buffer_detach(ByteBuffer buff);
	
	public static void checkInitialization(){
		if(!isInitialized) {
			throw new NotInitializedException(
				"Attempting to use an MPI routine before initializing MPICH");
		}
	}

	// MPI_Dims_create
	public static void dims_create(int nnodes,int offset_dims,int ndims,int[] dims){
		_dims_create(nnodes, offset_dims, ndims, dims);
	}
	private static native void _dims_create(int nnodes,int offset_dims,int ndims,int[] dims);
	// MPI_Get_processor_name
	public static String processor_name(){
		return _processor_name();
	}
	private static native String _processor_name();
	// MPI_Wtime
	public static double wtime(){
		return _wtime();
	}
	private static native double _wtime();
	// MPI_Wtick
	public static double wtick(){
		return _wtick();
	}
	private static native double _wtick();
	// MPI_Initialized
	public static boolean isInitialized(){
		return _isInitialized();
	}
	private static native boolean _isInitialized();
	// MPI_Comm_get_parent
	public static Intercomm parent(){
		long comm = _parent();

		return new Intercomm(comm);
	}
	private static native long _parent();

	/** enspablish communication */
	// server
	// MPI_Open_port
	public static String open_port(Info info){
		return _open_port(info.getHandler());
	}
	private static native String _open_port(long info);
	// MPI_Close_port
	public static void close_port(String portname){
		_close_port(portname);
	}
	private static native void _close_port(String portname);
	// MPI_Publish_name
	public static void publish_name(String servicename,Info info,String portname){
		_publish_name(servicename, info.getHandler(), portname);
	}
	private static native void _publish_name(String servicename,long info,String portname);
	// MPI_Ubpublish_name
	public static void unpublish_name(String servicename,Info info,String portname){
		_unpublish_name(servicename, info.getHandler(), portname);
	}
	private static native void _unpublish_name(String servicename,long info,String portname);
	// MPI_Lookup_name
	public static String lookup_name(String servicename,Info info){
		return _lookup_name(servicename, info.getHandler());
	}
	private static native String _lookup_name(String servicename,long info);
	// TODO: MPI_Comm_join
	// MPI_File_delete
	public static void file_delete(String name,Info info){
		_file_delete(name, info.getHandler());
	}
	private static native void _file_delete(String name,long info);
}
