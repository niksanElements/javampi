package mpi;

import java.nio.ByteBuffer;

import mpi.datatype.Datatype;

public class File {
    private long handler;

    public File(long handler){
        this.handler = handler;
	}
	
	// MPI_File_get_amode
	public int amode(){
		return _amode(this.handler);
	}
	private static native int _amode(long fh);
	// MPI_File_set_atomicity
	public void atomicity(boolean flag){
		_atomicity(this.handler, flag);
	}
	private static native void _atomicity(long file,boolean flag);
	// MPI_File_get_atomicity
	public boolean atomicity(){
		return _atomicity(this.handler);
	}
	private static native boolean _atomicity(long file);
	// MPI_File_get_group
	public Group group(){
		long handler = _get_group(this.handler);

		return new Group(handler);
	}
	private static native long _get_group(long file);
	// MPI_File_get_info
	public Info info(){
		long handler = _info(this.handler);

		return new Info(handler);
	}
	private static native long _info(long file);
	// MPI_File_get_position
	public long position(){
		return _get_position(this.handler);
	}
	private static native long _get_position(long file);
	// MPI_File_get_position_shared
	public long position_shared(){
		return _get_position_shared(this.handler);
	}
	private static native long _get_position_shared(long file);
	// MPI_File_set_size
	public void size(long size){
		_set_size(this.handler, size);
	}
	private static native void _set_size(long file,long size);
	// MPI_File_get_size
	public long size(){
		return _get_size(this.handler);
	}
	private static native long _get_size(long file);
	// MPI_File_set_view
	public void view(long disp,Datatype etype,Datatype filetype,String datarep,Info info){
		_set_view(this.handler, disp, etype.getHandler(), filetype.getHandler(),
			datarep, info.getHandler());
	}
	private static native void _set_view(
		long file,long disp,long etype,long filetype,String datarep,long info);
	// MPI_File_preallocate
	public void preallocate(long size){
		_preallocate(this.handler,size);
	}
	private static native void _preallocate(long file,long size);
	// MPI_File_seek
	public void seek(long offset,int whance){
		_seek(this.handler,offset,whance);
	}
	private static native void _seek(long file,long offset,int whance);
	// MPI_File_seek_shared
	public void seek_shared(long offset,int whance){
		_seek_shared(this.handler, offset, whance);
	}
	private static native void _seek_shared(long file,long offset,int whance);
	// MPI_File_close
    public void close(){
        _close(this.handler);
    }
	private static native void _close(long file);
/** access operations */
    // MPI_File_write
    public void write(Object buff,int offset,int count,Datatype datatype,Status stat,ByteBuffer objBuff){
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
			Comm.fillBuffer(buff, offset, count,datatype,objBuff);
			_write(this.handler,objBuff, 0, count, 
					datatype.getHandler(),stat);
		}
		else{
			_write(this.handler,buff, offset, count, 
				datatype.getHandler(),stat);
		}
    }
    private static native void _write(
        long fh, Object buf,int offset,int count,
		long datatype, Status status);
	// MPI_file_write_at
	public void write_at(long offset_file,Object buff,int offset,int count,Datatype datatype,Status stat,ByteBuffer objBuff){
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
			Comm.fillBuffer(buff, offset, count,datatype,objBuff);
			_write_at(this.handler,offset_file,objBuff, 0, count, 
					datatype.getHandler(),stat);
		}
		else{
			_write_at(this.handler,offset_file,buff, offset, count, 
				datatype.getHandler(),stat);
		}
    }
    private static native void _write_at(
        long fh,long offset_file, Object buf,int offset,int count,
		long datatype, Status status);
	// MPI_File_read
	public void read(Object buff,int offset,int count,Datatype datatype,Status stat,ByteBuffer objBuff){
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
			_read(this.handler,objBuff, 0, count, 
				datatype.getHandler(),stat);
			for(int i = offset;i < (offset+count);i++){
				objArr[i] = datatype.constructFromByteByffer(objBuff);
			}
		}
		else{
			_read(this.handler,buff, offset, count, 
				datatype.getHandler(), stat);

		} 
	}
	private static native void _read(
		long fh,Object buff,int offset,int count,long datatype,Status stat);
	// MPI_File_read_at
	public void read_at(long offset_file,Object buff,int offset,int count,
		Datatype datatype,Status stat,ByteBuffer objBuff){
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
			_read_at(this.handler,offset_file,objBuff, 0, count, 
				datatype.getHandler(),stat);
			for(int i = offset;i < (offset+count);i++){
				objArr[i] = datatype.constructFromByteByffer(objBuff);
			}
		}
		else{
			_read_at(this.handler,offset_file,buff, offset, count, 
				datatype.getHandler(), stat);
		} 
	}
	private static native void _read_at(
		long fh,long offset_file,Object buff,int offset,
		int count,long datatype,Status stat);
	// MPI_File_write_shared
	public void write_shared(Object buff,int offset,int count,
		Datatype datatype,Status stat,ByteBuffer objBuff){
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
			Comm.fillBuffer(buff, offset, count,datatype,objBuff);
			_write_shared(this.handler,objBuff, 0, count, 
					datatype.getHandler(),stat);
		}
		else{
			_write_shared(this.handler,buff, offset, count, 
				datatype.getHandler(),stat);
		}
    }
    private static native void _write_shared(
        long fh, Object buf,int offset,int count,
		long datatype, Status status);
	// MPI_File_read_shared
	public void read_shared(Object buff,int offset,int count,Datatype datatype,Status stat,ByteBuffer objBuff){
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
			_read_shared(this.handler,objBuff, 0, count, 
				datatype.getHandler(),stat);
			for(int i = offset;i < (offset+count);i++){
				objArr[i] = datatype.constructFromByteByffer(objBuff);
			}
		}
		else{
			_read_shared(this.handler,buff, offset, count, 
				datatype.getHandler(), stat);

		} 
	}
	private static native void _read_shared(
		long fh,Object buff,int offset,int count,long datatype,Status stat);
	// MPI_File_write_all
    public void write_all(Object buff,int offset,int count,Datatype datatype,Status stat,ByteBuffer objBuff){
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
			Comm.fillBuffer(buff, offset, count,datatype,objBuff);
			_write_all(this.handler,objBuff, 0, count, 
					datatype.getHandler(),stat);
		}
		else{
			_write_all(this.handler,buff, offset, count, 
				datatype.getHandler(),stat);
		}
    }
    private static native void _write_all(
        long fh, Object buf,int offset,int count,
		long datatype, Status status);
	// MPI_File_read_all
	public void read_all(Object buff,int offset,int count,Datatype datatype,
		Status stat,ByteBuffer objBuff){
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
			_read_all(this.handler,objBuff, 0, count, 
				datatype.getHandler(),stat);
			for(int i = offset;i < (offset+count);i++){
				objArr[i] = datatype.constructFromByteByffer(objBuff);
			}
		}
		else{
			_read_all(this.handler,buff, offset, count, 
				datatype.getHandler(), stat);

		} 
	}
	private static native void _read_all(
		long fh,Object buff,int offset,int count,long datatype,Status stat);
	// MPI_File_iwrite
	public 	Request iwrite(Object buff,int offset,int count,
		Datatype datatype,ByteBuffer objBuff
	){
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
			Comm.fillBuffer(buff, offset, count,datatype,objBuff);
			return _iwrite(this.handler,objBuff, offset, count, datatype.getHandler());
		}
		else{
			return _iwrite(this.handler,buff, offset, count, datatype.getHandler());
		}		
	}
	private static native Request _iwrite(long handler,Object buff,int offset,int count,long datatype);
	// MPI_File_iread_shared
	public Request iread(Object buff,int offset,int count,Datatype datatype){
		return _iread(this.handler,buff, offset, count, datatype.getHandler());
	}
	private static native Request _iread(long file,Object buff,int offset,int count,long datatype);
	// MPI_File_iwrite_shared
	public 	Request iwrite_shared(Object buff,int offset,int count,
		Datatype datatype,ByteBuffer objBuff
	){
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
			Comm.fillBuffer(buff, offset, count,datatype,objBuff);
			return _iwrite_shared(this.handler,objBuff, offset, count, datatype.getHandler());
		}
		else{
			return _iwrite_shared(this.handler,buff, offset, count, datatype.getHandler());
		}		
	}
	private static native Request _iwrite_shared(long handler,Object buff,int offset,int count,long datatype);
	// MPI_File_iread_shared
	public Request iread_shared(Object buff,int offset,int count,Datatype datatype){
		return _iread_shared(this.handler,buff, offset, count, datatype.getHandler());
	}
	private static native Request _iread_shared(long file,Object buff,int offset,int count,long datatype);
	// MPI_File_iwrite_at
	public 	Request iwrite_at(int offset_file,Object buff,int offset,int count,
		Datatype datatype,ByteBuffer objBuff
	){
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
			Comm.fillBuffer(buff, offset, count,datatype,objBuff);
			return _iwrite_at(this.handler,offset_file,objBuff, offset, count, datatype.getHandler());
		}
		else{
			return _iwrite_at(this.handler,offset_file,buff, offset, count, datatype.getHandler());
		}		
	}
	private static native Request _iwrite_at(long handler,long offset_file,Object buff,int offset,int count,long datatype);
	// MPI_File_iread_at
	public Request iread_at(long offset_file,Object buff,int offset,int count,Datatype datatype){
		return _iread_at(this.handler,offset_file,buff, offset, count, datatype.getHandler());
	}
	private static native Request _iread_at(long file,long offset_file,Object buff,int offset,int count,long datatype);
	// TODO: all write/read operations
}