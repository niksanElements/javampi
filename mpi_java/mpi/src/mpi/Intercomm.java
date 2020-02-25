package mpi;

public class Intercomm extends Comm {

    public Intercomm(){
        this.handler = Comm.null_handler;
    }
 
    public Intercomm(long handler){
        this.handler = handler;
    }

    // MPI_Comm_test_inter
    // TODO: change to Comm
    public boolean test(){
        return _test(this.handler);
    }
    private static native boolean _test(long handler);
    // MPI_Comm_remote_size
    public int size(){
        return _remote_size(this.handler);
    }
    private static native int _remote_size(long handler);
    // MPI_Comm_remote_group
    public Group remote_group(){
        long new_handler = _remote_group(this.handler);

        return new Group(new_handler);
    }
    private static native long _remote_group(long comm);
    // MPI_Intercomm_create
    public void create(Intracomm local_comm,int local_leader,
        Intracomm peer_comm,int remote_leader,int tag
    ){
        long handler = _intercomm_create(local_comm.handler, local_leader, peer_comm.handler, 
            remote_leader, tag);

        this.handler = handler;
    }
    private static native long _intercomm_create(long local_comm,int local_leader,
        long peer_comm,int remote_leader,int tag);
    // MPI_Intercomm_merge
    public Intracomm merge(boolean high){
        long handler = _merge(this.handler, high);

        return new Intracomm(handler);
    }
    private static native long _merge(long intercomm,boolean high);

    // MPI_Comm_disconnect
    public void disconnect(){
        this.handler = _disconnect(this.handler);
    }
    private static native long _disconnect(long comm);
}
