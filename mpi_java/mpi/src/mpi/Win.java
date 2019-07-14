package mpi;


import java.lang.reflect.Field;
import java.nio.Buffer;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import mpi.datatype.Datatype;
import mpi.op.Op;

/**
 * This is mpi object brought to live with the help of 
 * {@link java.nio.ByteBuffer}.
 */
public class Win {

    private long handler;
    private long address;
    private int capacity;

    private ByteBuffer buffer;

    private static Field _address;
    private static Field _capacity;

    static {
        try{
            _address = Buffer.class.getDeclaredField("address");
            _address.setAccessible(true);
            _capacity = Buffer.class.getDeclaredField("capacity");
            _capacity.setAccessible(true);
        }
        catch(NoSuchFieldException ex){
            ex.printStackTrace();
        }
    }

    public static class Win_allocate_ret {
        public long win;
        public long address;
        public int size;
    }

    public Win(long handler,ByteBuffer buffer){
        this.handler = handler;
        this.address = 0;
        this.capacity = 0;
        this.buffer = buffer;

        // this._prepare_fields();
    }

    public Win(Win_allocate_ret in,int capacity){
        this.handler = in.win;
        this.address = in.address;
        this.capacity = capacity;
        this.buffer = null;

        // this._prepare_fields();
    }

    public ByteBuffer getByteBuffer(ByteOrder order){
        ByteBuffer buffer = null;
        // if allocate form the MPI
        if(this.address != 0 && this.capacity != 0){
            // allocate empty bytebuffer
            buffer = _byteBuffer(this.address, this.capacity,order);
        }
        // if allocate from a user
        else if(this.buffer != null){
            buffer = this.buffer;
        }

        return buffer;
    }

    private static ByteBuffer _byteBuffer(long address,int capacity,ByteOrder order){
        // allocate empty bytebuffer
        ByteBuffer buffer = ByteBuffer.allocateDirect(0).order(order);
        // set address&capacity
        try{
            _address.setLong(buffer, address);
            _capacity.setInt(buffer, capacity);

            buffer.position(0);
            buffer.limit(capacity);
        }
        catch(IllegalAccessException ex){
            ex.printStackTrace();
            return null;
        }

        return buffer;
    }

    // MPI_Win_fence
    public void fence(int _assert){
        _fence(_assert, this.handler);
    }
    private static native void _fence(int _assert,long win);
    // MPI_Accumulate
    public void accumulate(Object origin,int origin_offset,int origin_count,Datatype origin_datatype,
        int target_rank,int target_dips,int target_count,Datatype target_datatype,Op op
    ){
        // TODO: accumulate
    }
    private static native void _accumulate();
    // MPI_Get
    public void get(Object base,int origin_offset,int origin_count,Datatype origin_type,
        int target_rank,long target_disp,int target_count,Datatype target_type
    ){
        _get(base,origin_offset, origin_count, origin_type.getHandler(), 
            target_rank, target_disp, target_count, target_type.getHandler(), this.handler);
    }
    private static native void _get(Object base,int origin_offset,int origin_count,long origin_type,
    int target_rank,long target_disp,int target_count,long target_type,long win);
    // MPI_Put
    public void put(Object base,int origin_offset,int origin_count,Datatype origin_type,
        int target_rank,long target_disp,int target_count,Datatype target_type
    ){
        _put(base,origin_offset, origin_count, origin_type.getHandler(), 
            target_rank, target_disp, target_count, target_type.getHandler(), this.handler);
    }
    private static native void _put(Object base,int origin_offset,int origin_count,long origin_type,
    int target_rank,long target_disp,int target_count,long target_type,long win);
    // MPI_Win_flush
    public void flush(int rank){
        _flush(rank,this.handler);
    }
    private static native void _flush(int rank,long win);
    // MPI_Win_flush_all
    private void flush_all(){
        _flush_all(this.handler);
    }
    private static native void _flush_all(long win);
     // MPI_Win_flush_local
     public void flush_local(int rank){
        _flush_local(rank,this.handler);
    }
    private static native void _flush_local(int rank,long win);
    // MPI_Win_flush_local_all
    public void flush_local_all(){
        _flush_local_all(this.handler);
    }
    private static native void _flush_local_all(long win);
    // MPI_Win_get_info
    public Info info(){
        long info = _get_info(this.handler);

        return new Info(info);
    }
    private static native long _get_info(long win);
    // MPI_Win_set_info
    public void info(Info info){
        _set_info(info.getHandler(), this.handler);
    }
    private static native void _set_info(long info,long win);
    public Group group(){
        long group = _get_group(this.handler);

        return new Group(group);
    }
    private static native long _get_group(long win);
    // MPI_Win_get_name
    public String name(){
        return _get_name(this.handler);
    }
    private static native String _get_name(long win);
    // MPI_Win_set_name
    public void name(String name){
        _set_name(name,this.handler);
    }
    private static native void _set_name(String name,long win);
    // MPI_Win_lock
    public void lock(int lock_type, int rank, int _assert){
        _lock(lock_type, rank, _assert, this.handler);
    }
    private static native void _lock(int lock_type, int rank, int _assert,long win);
    // MPI_Win_lock_all
    public void lock_all(int _assert){
        _lock_all(_assert, this.handler);
    }
    private static native void _lock_all(int _assert,long win);
    // MPI_Win_unlock
    public void unlock(int rank){
        _unlock(rank, this.handler);
    }
    private static native void _unlock(int rank,long win);
    // MPI_Win_unlock_all
    public void unlock_all(){
        _unlock_all(this.handler);
    }
    private static native void _unlock_all(long win);
    // MPI_Win_sunc
    public void sync(){
        _sync(this.handler);
    }
    private static native void _sync(long win);
    // MPI_Win_free
    public void free(){
        this.address = 0;
        this.capacity = 0;
        this.buffer = null;
        this.handler = _free(this.handler);
    }
    private static native long _free(long win);

    // MPI_Win_shared_query
    public ByteBuffer shared_query(int rank,ByteOrder order){
        ByteBuffer buff = null;
        Win_allocate_ret ret = new Win_allocate_ret();

        _shared_query(this.handler, rank, ret);

        buff = _byteBuffer(ret.address, ret.size,order);

        return buff;
    }
    private static native void _shared_query(long win, int rank, Win_allocate_ret objwinret);

}