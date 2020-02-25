package test;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import mpi.Info;
import mpi.Intracomm;
import mpi.MPI;
import mpi.Win;

class WinAllocateShared {
    public static void main(String[] args) {
        MPI.Init(args);
        int wrank = MPI.COMM_WORLD.rank();
        int wsize = MPI.COMM_WORLD.size();
        Intracomm comm_node = MPI.COMM_WORLD.split_type(MPI.COMM_TYPE_SHARED, 0, MPI.INFO_NULL);
        int sm_rank = comm_node.rank();
        int sm_size = comm_node.size();
        Info win_info = new Info();
        win_info.create();
        win_info.set("alloc_shared_noncontig", "true");
        Win sm_win = comm_node.win_allocate_shared(4, 4, win_info);
        win_info.free();
        sm_win.lock_all(0);
        sm_win.sync();
        comm_node.barrier();

        ByteBuffer[] buf = new ByteBuffer[sm_size];

        if(sm_rank!=0){
            for (int i=0; i<sm_size; i++) {
                buf[i] = sm_win.shared_query(i);
                if(i==sm_rank) {
                    buf[i].putInt(0, sm_rank+100);
                    System.out.printf("rank=%d modified *buf[%d]=%d\n",sm_rank, i, buf[i].getInt(0));
                }
            }
        }
        else{
            System.out.printf("rank=%d Master just watches it:)\n",sm_rank);
        }
        sm_win.unlock_all();
        if(sm_rank!=0){
            for (int i=0; i<sm_size; i++) {
                if(buf[i]!=null)
                    System.out.printf("rank=%d target=%d buf=%d b_size=%d \n", 
                        sm_rank, i, buf[i].getInt(0),buf[i].capacity());
            }
        }
        sm_win.free();
        comm_node.free();
        MPI.Finalize();
    }
}