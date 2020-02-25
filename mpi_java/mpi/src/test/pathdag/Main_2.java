package test.pathdag;

import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.Stack;

import mpi.File;
import mpi.Info;
import mpi.MPI;
import mpi.Win;
import test.Utils;

/**
 * Main
 */
public class Main_2 {

    public static final int MAXN = 2000;
    public static final int INT_MIN = -1;

    // process indemnificator
    public static int rank;
    public static int size;

    // file name/path
    public static String file_path_name;

    // arguments
    public static int from;
    public static int to;
    public static int nodes;
    public static int graph[][] = new int[MAXN][MAXN];
    // {
    //     {0},
    //     {3,3,2,9}, // 1
    //     {2,4,6}, // 2
    //     {2,6,7}, // 3
    //     {2,5,8}, // 4
    //     {1,11}, // 5
    //     {2,5,10}, // 6
    //     {1,10}, // 7
    //     {1,11}, // 8
    //     {1,10}, // 9
    //     {2,5,11}, // 10
    //     {0}, // 11
    // };
    public static int[] ve = new int[2];
    public static int max;
    public static int last_biggest_el;

    // result
    public static int r_len;
    public static int r_i;
    public static int r_path[] = new int[MAXN];
    public static int path[] = new int[MAXN];
    public static int path_len[] = new int[MAXN];
    public static int _used_buffer[] = new int[MAXN];

    // len of the last biggest element
    public static int _curr_last_biggest;
    public static int _last_biggest;

    public static void main(String[] args) {

        MPI.Init(args);
        // take the graph from a input file
        Init(args);

        // solve
        for(int i = 0;i < 1000;i++){
            Solve();
        }

        Finalize();
    }


    public static void Init(String[] args){
        int _file_buffer[] = new int[2];

        file_path_name = args[0];  // only for testing

        rank = MPI.COMM_WORLD.rank();
        size = MPI.COMM_WORLD.size();

        // open a file
        File f = MPI.COMM_WORLD.file_open(file_path_name,MPI.MODE_RDONLY,MPI.INFO_NULL);
        f.view(0, MPI.INT, MPI.INT, "native", MPI.INFO_NULL);
        f.atomicity(true);
        /**
         * ve[0] - vertexes
         * ve[1] - edges
         */
    
        f.read(ve, 0, 2, MPI.INT,null, null);
        // ve[0] = 11; // vertexes
        // ve[1] = 17; // edges
        nodes = ve[0];

        // System.out.println(ve[0]);

        for(int i = 0;i < ve[0];i++){
            graph[i][0] = 0;
        }

        for(int i = 0;i < ve[1];i++){
            f.read(_file_buffer,0,2,MPI.INT,null,null);

            graph[_file_buffer[0]][++graph[_file_buffer[0]][0]] = _file_buffer[1];
        }

        f.close();
    }

    public static void Solve(){
        int add = _take_nodes();


        // topological sort
        for(int i = 1;i <= ve[0];i++){ 
            _used_buffer[i] = 0;
        }
        Stack<Integer> top_stack = new Stack<>();
        for (int i = 1; i <= ve[0];i++){
            
            if (_used_buffer[i] == 0){
                _topological_sort(i,top_stack);
            }
        }

        if(from != 0 && to != 0){
        
            for(int i = from;i <= to;i++){
                _max_path(i,(Stack<Integer>)top_stack.clone());
            }
    
            if(add != 0){
                _max_path(add,(Stack<Integer>)top_stack.clone());
            }
        }

        // get the result
        int send_len[] = new int[1];
        int recv_len[] = new int[1];
        send_len[0] = r_len;
        MPI.COMM_WORLD.allreduce(send_len, recv_len, 0, 0, 1, MPI.INT, 
            MPI.MAX, null, null);
        
        Utils.sleepRand(500);
        if(recv_len[0] == r_len){
            _print_result_path(r_i);
            System.out.println();
            System.out.flush();
            System.out.printf("rank %d, len: %d\n",rank,r_len);
            System.out.flush();
        }

    }

    public static void _print_result_path(int i){

        if(r_path[i] != 0){
            _print_result_path(r_path[i]);
        }
    
        System.out.printf("%d ",i);
        System.out.flush();
    }

    private static void _max_path(int node,Stack<Integer> stack)
    {
        int local_max = 0;
        int ii = 0;

        //dfs
        BFS(node,stack);

        ii = last_biggest_el;
        local_max = path_len[last_biggest_el];

        // System.out.println(local_max);

        if(local_max > max){
            max = local_max;
            r_len = max;

            // memcpy(&result.path,&path,(1+nodes)*sizeof(int));
            // System.arraycopy(r_path, 0, path, 0, 1+nodes);
            System.arraycopy(path, 0, r_path, 0, 1+nodes);

            r_i = ii;
        }
    }

    private static void BFS(int node,Stack<Integer> stack)
    {
        _all_resume();
        path_len[node] = 0;

        while(stack.size() != 0){
            int u = stack.pop();
            if(path_len[u] != INT_MIN){
                for(int i = 1;i <= graph[u][0];i++){
                    int v = graph[u][i];

                    if(path_len[v] < path_len[u] + 1){
                        path_len[v] = path_len[u] + 1;  
                        path[v] = u;

                        _curr_last_biggest = path_len[v];
                        if(_last_biggest < _curr_last_biggest){
                            _last_biggest = _curr_last_biggest;
                            last_biggest_el = v;
                        }         
                    }
                }
            }
        }
        stack.clear();
    }

    public static void _topological_sort(int v, Stack<Integer> stack)
    {
        // Mark the current node as visited
        _used_buffer[v] = 1;


        for(int i = 1; i <= graph[v][0];i++){
            int node = graph[v][i];

            if(_used_buffer[node] == 0){
                _topological_sort(node,stack);
            }
        }

        stack.push(v);
    }

    private static void _all_resume(){
        _last_biggest = 0;
        last_biggest_el = 0;
        _curr_last_biggest = 0;
    
        for(int i = 1;i <= ve[0];i++){ 
            path_len[i] =  INT_MIN; 
            // _used_buffer[i] = 0;
            path[i] = 0;
        }
    }

    public static void Finalize(){
        MPI.Finalize();
    }

    private static int _take_nodes(){
        float avrg_nodes = (float)nodes/(float)size;

        if(avrg_nodes > 0 && avrg_nodes < 1){
            if(rank < nodes){
                from = rank+1;
                to = rank+1;
            }
            else{
                from = 0;
                to = 0;
            }
        }
        else if(avrg_nodes > 1){
            int avrg = (int)avrg_nodes;
            // System.out.printf("%d %d\n",nodes, rank);
            int rest = nodes%size;

            from = (rank*avrg)+1;
            to=(from - 1)+avrg;

            if(rank < rest){
                return nodes-(rest-(rank + 1));
            }

            return 0;
        }
        else if(avrg_nodes == 1){
            from = rank+1;
            to = rank+1;
        }
        return 0;
    }
}