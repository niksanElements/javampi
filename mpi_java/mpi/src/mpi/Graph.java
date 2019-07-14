package mpi;

public class Graph extends Intracomm 
{
    public Graph(long handler){
        this.handler = handler;
    }

    // MPI_Graph_get
	public void get(int offsetindx,int maxindex, int offsetedges,int maxedges, 
    int indx[], int edges[]){
        _graph_get(this.handler, offsetindx, maxindex, offsetedges, maxedges, indx, edges);
    }
    private static native void _graph_get(long comm,int offsetindx,int maxindex,
        int offsetedges,int maxedges, int indx[], int edges[]);
    // MPMI_Graphdims_get
	public int nedges(){
		return _get_graphdims(this.handler, true);
	}
	public int nnodes(){
		return _get_graphdims(this.handler, false);
	}
    private static native int _get_graphdims(long comm,boolean isnedges);
    // MPI_Graph_neighbors
    public void neighbors(int rank,int offset,int maxxneighbors,int[] neighbors){
        _neighbors(this.handler, rank, offset, maxxneighbors, neighbors);   
    }
    private static native void _neighbors(long comm, int rank,int offset,int maxxneighbors,int[] neighbors);
    public int neighbors_count(int rank){
        return _neighbors_count(this.handler,rank);
    }
    private static native int _neighbors_count(long comm,int rank);
    // MPI_Comm_dup
    public Graph dup(){
        long handler = _dup(this.handler);

        return new Graph(handler);
    }
}