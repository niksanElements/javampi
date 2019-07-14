package mpi;

// MPI_Group
public class Group {
    private long handler;

    public Group(){
        // TODO: set this in the native initialization function
        this.handler = 0x48000000;
    }

    public Group(long handler){
        this.handler = handler;
    }

    public long getHandler(){
        return this.handler;
    }

    // MPI_Group_size
    public int size(){
        return _size(this.handler);
    }
    private static native int _size(long group);

    // MPI_Group_rank
    public int rank(){
        return _rank(this.handler);
    }
    private static native int _rank(long group);

    // MPI_Group_compare
    public int compare(Group group){
        return _compare(this.handler, group.handler);
    }
    private static native int _compare(long group1,long group2);

    // MPI_Group_free
    public void free(){
        _free(this.handler);
    }
    private static native void _free(long handler);
    // MPI_Group_incl
    public Group incl(int offset,int n,int[] ranks){
        long handler = _incl(this.handler, offset, n, ranks);

        return new Group(handler);
    }
    private static native long _incl(long group,int offset,int n,int[] ranks);
    // MPI_Group_excl
    public Group excl(int offset,int n,int[] ranks){
        long handler = _excl(this.handler, offset, n, ranks);

        return new Group(handler);
    }
    private static native long _excl(long group,int offset,int n,int[] ranks);
    // TODO: MPI_Group_range_excl
    // MPI_Group_difference
    public Group difference(Group group){
        long new_handler = _difference(this.handler, group.handler);

        return new Group(new_handler);
    }
    private static native long _difference(long group1,long group);
    // MPI_Group_intersection
    public Group intersection(Group group){
        long new_handler = _intersection(this.handler, group.handler);

        return new Group(new_handler);
    }
    private static native long _intersection(long group1,long group2);
    // MPI_Group_union
    public Group union(Group group){
        long new_handler = _union(this.handler, group.handler);

        return new Group(new_handler);
    }
    private static native long _union(long group1,long group2);
    // MPI_Group_translate_ranks
    public void translate_ranks(int offset_rank1,int n,
        int[] ranks1,Group group,int offset_rank2,int[] ranks2
    ){
        _translate_ranks(this.handler, offset_rank1, n, ranks1, 
            group.handler, offset_rank2, ranks2);
    }
    private static native void _translate_ranks(long group1,int offset_rank1,int n,
        int[] ranks1,long group2,int offset_rank2,int[] ranks2);
}