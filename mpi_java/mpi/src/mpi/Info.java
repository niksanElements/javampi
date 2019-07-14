package mpi;

// MPI_Infor
public class Info{
    private long handler;

    public static final long null_handler = 0x1c000000;

    public Info(){
        this.handler = null_handler;
    }

    public Info(long handler){
        this.handler = handler;
    }

    // handler access
    public long getHandler(){
        return this.handler;
    }

    // MPI_Info_create
    public void create(){
        this.handler = _create();
    }
    private static native long _create();
    // MPI_Info_delete
    public void delete(String key){
        _delete(this.handler,key);
    }
    private static native void _delete(long info, String key);
    // MPI_Info_dup
    public Info dup(){
        long handler = _dup(this.handler);

        return new Info(handler);
    }
    private static native long _dup(long info);
    // MPI_Info_free
    public void free(){
        _free(this.handler);
    }
    private static native void _free(long info);
    // MPI_Info_get
    public String get(String key){
        return _get(this.handler,key);
    }
    private static native String _get(long info,String key);
    // MPI_Info_nkeys
    public int nkeys(){
        return _nkeys(this.handler);
    }
    private static native int _nkeys(long info);
    // MPI_Info_get_nthkey
    public String get_nthkey(int n){
        return _get_nthkey(this.handler, n);
    }
    private static native String _get_nthkey(long info,int n);
    // MPI_Info_set
    public void set(String key,String value){
        _set(this.handler,key,value);
    }
    private static native void _set(long info,String key,String value);
}