package org.mpich;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;

import org.mpich.MPI;

public class Main {

    public static void test_Ssend(String[] args){
        MPI.MPI_Init(args);
        MPI_Status s = new MPI_Status();
        int rank =  MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);

        // System.out.println(MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD));
        // MPI.MPI_Send("niki".toCharArray(),1,2,3);

        if(rank == 1){
            System.out.printf("Rank: %d Size: %d \n",
                rank,
            MPI.MPI_Comm_size(MPI.MPI_COMM_WORLD));

            MPI.MPI_Ssend(new byte[]{0x11,0x22,0x33,0x44},MPI.BYTE,0,0,MPI.MPI_COMM_WORLD);
        }
        else if(rank == 0){
            byte[] buff = new byte[20];
            int result = MPI.MPI_Recv(buff,MPI.BYTE,1,0,MPI.MPI_COMM_WORLD,s);
            // System.out.printf("result: %d\n",result);
            for(int i = 0;i < 4;i++){
                System.out.printf("0x%02X ",buff[i]);
            }
            System.out.println();
            System.out.printf("%d %d %d %d %d\n",
                s.count_lo,s.count_hi_and_cancelled,s.MPI_SOURCE,s.MPI_TAG,s.MPI_ERROR);
            int count = MPI.MPI_Get_count(s,MPI.BYTE);
            System.out.println(String.valueOf(count));
        }

        MPI.MPI_Finalize();
    }

    public static void test_Rsend(String[] args){
        MPI.MPI_Init(args);
        MPI_Status s = new MPI_Status();
        int rank =  MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);

        // System.out.println(MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD));
        // MPI.MPI_Send("niki".toCharArray(),1,2,3);

        if(rank == 1){
            System.out.printf("Rank: %d Size: %d \n",
                rank,
            MPI.MPI_Comm_size(MPI.MPI_COMM_WORLD));
            MPI_Request req = new MPI_Request();
            int[] arr = new int[5];
            arr[0] = 100;
            arr[2] = 40;
            arr[3] = 50;
            arr[1] = 25;
            for(int i = 0;i < 40;i++){
                arr[4] = (byte)i;
                MPI.MPI_Irsend(arr,MPI.INT,0,0,MPI.MPI_COMM_WORLD,req);
                MPI.MPI_Wait(req,s);
            }
        }
        else if(rank == 0){
            int[] buff = new int[5];
            MPI_Request req = new MPI_Request();
            for(int j = 0;j < 40;j++){
                int result = MPI.MPI_Irecv(buff,MPI.INT,1,0,MPI.MPI_COMM_WORLD,req);
                while(true){
                    MPI.MPI_Test(req,null);
                    System.out.printf(".");
                    if(req.isOpComplete == true){
                        System.out.println();
                        break;
                    }
                }
                // System.out.printf("result: %d\n",result);
                for(int i = 0;i < 5;i++){
                    System.out.printf("%d ",buff[i]);
                }
                System.out.println();
                System.out.printf("%d %d %d %d %d\n",
                    s.count_lo,s.count_hi_and_cancelled,s.MPI_SOURCE,s.MPI_TAG,s.MPI_ERROR);
                int count = MPI.MPI_Get_count(s,MPI.INT);
                System.out.println(String.valueOf(count));
            }
        }

        MPI.MPI_Finalize();
    }

    public static void test_irecv(String[] args){

    }

    public static void test_waitany(String[] args){
        MPI.MPI_Init(args);

        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        if(rank == 0){
            MPI_Request[] requests = new MPI_Request[9];
            List<int[]> buff = new ArrayList<int[]>(10);
            
            for(int i = 1;i < 10;i++){
                // System.out.println("*****************");
                buff.add(new int[7]);
                requests[i-1] = new MPI_Request();
                MPI.MPI_Irecv(buff.get(i-1),MPI.INT,i,0,MPI.MPI_COMM_WORLD,requests[i-1]);
            }
            for(int i = 0;i < 9;i++){
                int index = MPI.MPI_Waitany(requests,null);
                int[] arr = buff.get(index);
                System.out.println(Arrays.toString(arr));
            }
        }
        else{
            MPI_Request req = new MPI_Request();
            MPI_Status stat = new MPI_Status();
            // if(rank == 1){
                Random rand = new Random();
                try{ Thread.sleep(Math.abs(rand.nextInt())%400); }
                catch(InterruptedException e){ e.printStackTrace(); }
            // }
            Random random = new Random();
            MPI.MPI_Isend(new int[]{random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),rank},MPI.INT,0,0,MPI.MPI_COMM_WORLD,req);
            MPI.MPI_Wait(req,null);
        }

        MPI.MPI_Finalize();
    }

    public static void test_testany(String[] args){
        MPI.MPI_Init(args);

        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        if(rank == 0){
            MPI_Request[] requests = new MPI_Request[9];
            List<int[]> buff = new ArrayList<int[]>(10);
            
            for(int i = 1;i < 10;i++){
                // System.out.println("*****************");
                buff.add(new int[7]);
                requests[i-1] = new MPI_Request();
                MPI.MPI_Irecv(buff.get(i-1),MPI.INT,i,0,MPI.MPI_COMM_WORLD,requests[i-1]);
            }
            for(int i = 0;i < 9;i++){
                int index = MPI.MPI_UNDEFINED;
                while(index == MPI.MPI_UNDEFINED){
                    index = MPI.MPI_Testany(requests,null);
                }
                int[] arr = buff.get(index);
                System.out.println(Arrays.toString(arr));
            }
        }
        else{
            MPI_Request req = new MPI_Request();
            MPI_Status stat = new MPI_Status();
            // if(rank == 1){
                Random rand = new Random();
                try{ Thread.sleep(Math.abs(rand.nextInt())%400); }
                catch(InterruptedException e){ e.printStackTrace(); }
            // }
            Random random = new Random();
            MPI.MPI_Isend(new int[]{random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),rank},MPI.INT,0,0,MPI.MPI_COMM_WORLD,req);
            MPI.MPI_Wait(req,null);
        }

        MPI.MPI_Finalize();
    }

    public static void test_waitall(String[] args){
        MPI.MPI_Init(args);

        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        if(rank == 0){
            MPI_Request[] requests = new MPI_Request[9];
            List<int[]> buff = new ArrayList<int[]>(10);
            
            for(int i = 1;i < 10;i++){
                // System.out.println("*****************");
                buff.add(new int[7]);
                requests[i-1] = new MPI_Request();
                MPI.MPI_Irecv(buff.get(i-1),MPI.INT,i,0,MPI.MPI_COMM_WORLD,requests[i-1]);
            }
            
            MPI.MPI_Waitall(requests,null);
            for(int i = 0;i < 9;i++){
                int[] temp_buff = buff.get(i);
                System.out.println(Arrays.toString(temp_buff));
            }
        }
        else{
            MPI_Request req = new MPI_Request();
            MPI_Status stat = new MPI_Status();
            // if(rank == 1){
                Random rand = new Random();
                try{ Thread.sleep(Math.abs(rand.nextInt())%400); }
                catch(InterruptedException e){ e.printStackTrace(); }
            // }
            Random random = new Random();
            MPI.MPI_Isend(new int[]{random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),rank},MPI.INT,0,0,MPI.MPI_COMM_WORLD,req);
            MPI.MPI_Wait(req,null);
        }

        MPI.MPI_Finalize();
    }

    public static void test_testall(String[] args){
        MPI.MPI_Init(args);

        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        if(rank == 0){
            MPI_Request[] requests = new MPI_Request[9];
            List<int[]> buff = new ArrayList<int[]>(10);
            
            for(int i = 1;i < 10;i++){
                // System.out.println("*****************");
                buff.add(new int[7]);
                requests[i-1] = new MPI_Request();
                MPI.MPI_Irecv(buff.get(i-1),MPI.INT,i,0,MPI.MPI_COMM_WORLD,requests[i-1]);
            }
            
            while(!MPI.MPI_Testall(requests,null)){}
            for(int i = 0;i < 9;i++){
                int[] temp_buff = buff.get(i);
                System.out.println(Arrays.toString(temp_buff));
            }
        }
        else{
            MPI_Request req = new MPI_Request();
            MPI_Status stat = new MPI_Status();
            // if(rank == 1){
                Random rand = new Random();
                try{ Thread.sleep(Math.abs(rand.nextInt())%400); }
                catch(InterruptedException e){ e.printStackTrace(); }
            // }
            Random random = new Random();
            MPI.MPI_Isend(new int[]{random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),rank},MPI.INT,0,0,MPI.MPI_COMM_WORLD,req);
            MPI.MPI_Wait(req,null);
        }

        MPI.MPI_Finalize();
    }

    public static void test_waitsome(String[] args){
        MPI.MPI_Init(args);

        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        if(rank == 0){
            MPI_Request[] requests = new MPI_Request[9];
            List<int[]> buff = new ArrayList<int[]>(10);
            
            for(int i = 1;i < 10;i++){
                // System.out.println("*****************");
                buff.add(new int[7]);
                requests[i-1] = new MPI_Request();
                MPI.MPI_Irecv(buff.get(i-1),MPI.INT,i,0,MPI.MPI_COMM_WORLD,requests[i-1]);
            }
            int _count = 0;
            while(_count != 9){
                int[] ready_operations = new int[9];
                int count = MPI.MPI_Waitsome(requests,ready_operations,null);
                System.out.printf("%d ",count);
                _count += count;
                for(int i = 0;i < count;i++){
                    int[] temp_buff = buff.get(ready_operations[i]);
                    System.out.println(Arrays.toString(temp_buff));
                }
            }
        }
        else{
            MPI_Request req = new MPI_Request();
            MPI_Status stat = new MPI_Status();
            // if(rank == 1){
                // Random rand = new Random();
                // try{ Thread.sleep(Math.abs(rand.nextInt())%400); }
                // catch(InterruptedException e){ e.printStackTrace(); }
            // }
            Random random = new Random();
            MPI.MPI_Isend(new int[]{random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),rank},MPI.INT,0,0,MPI.MPI_COMM_WORLD,req);
            MPI.MPI_Wait(req,null);
        }

        MPI.MPI_Finalize();
    }

    public static void test_testsome(String[] args){
        MPI.MPI_Init(args);

        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        if(rank == 0){
            MPI_Request[] requests = new MPI_Request[9];
            List<int[]> buff = new ArrayList<int[]>(10);
            
            for(int i = 1;i < 10;i++){
                // System.out.println("*****************");
                buff.add(new int[7]);
                requests[i-1] = new MPI_Request();
                MPI.MPI_Irecv(buff.get(i-1),MPI.INT,i,0,MPI.MPI_COMM_WORLD,requests[i-1]);
            }
            int _count = 0;
            while(_count != 9){
                int[] ready_operations = new int[9];
                int count = MPI.MPI_Testsome(requests,ready_operations,null);
                System.out.printf("%d ",count);
                _count += count;
                for(int i = 0;i < count;i++){
                    int[] temp_buff = buff.get(ready_operations[i]);
                    System.out.println(Arrays.toString(temp_buff));
                }
            }
        }
        else{
            MPI_Request req = new MPI_Request();
            MPI_Status stat = new MPI_Status();
            // if(rank == 1){
                // Random rand = new Random();
                // try{ Thread.sleep(Math.abs(rand.nextInt())%400); }
                // catch(InterruptedException e){ e.printStackTrace(); }
            // }
            Random random = new Random();
            MPI.MPI_Isend(new int[]{random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),rank},MPI.INT,0,0,MPI.MPI_COMM_WORLD,req);
            MPI.MPI_Wait(req,null);
        }

        MPI.MPI_Finalize();
    }

    public static void test_request(String[] args){
        MPI.MPI_Init(args);

        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        if(rank == 0){
            MPI_Request[] requests = new MPI_Request[9];
            List<int[]> buff = new ArrayList<int[]>(10);
            
            for(int i = 1;i < 10;i++){
                // System.out.println("*****************");
                buff.add(new int[7]);
                requests[i-1] = new MPI_Request();
                MPI.MPI_Irecv(buff.get(i-1),MPI.INT,i,0,MPI.MPI_COMM_WORLD,requests[i-1]);
            }
            int _count = 0;
            while(_count != 9){
                int[] ready_operations = new int[9];
                int count = MPI.MPI_Testsome(requests,ready_operations,null);
                // System.out.printf("%d ",count);
                _count += count;
            //     for(int i = 0;i < count;i++){
            //         int[] temp_buff = buff.get(ready_operations[i]);
            //         System.out.println(Arrays.toString(temp_buff));
            //     }
            }
        }
        else{
            MPI_Request req = new MPI_Request();
            MPI_Status stat = new MPI_Status();
            // if(rank == 1){
                // Random rand = new Random();
                // try{ Thread.sleep(Math.abs(rand.nextInt())%400); }
                // catch(InterruptedException e){ e.printStackTrace(); }
            // }
            Random random = new Random();
            MPI.MPI_Isend(new int[]{random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),rank},MPI.INT,0,0,MPI.MPI_COMM_WORLD,req);
            while(!MPI.MPI_Request_get_status(req,stat));
            System.out.printf("%d %d %d %d %d\n",
                    stat.count_lo
                    ,stat.count_hi_and_cancelled
                    ,stat.MPI_SOURCE
                    ,stat.MPI_TAG
                    ,stat.MPI_ERROR
            );
            MPI.MPI_Request_free(req);
        }

        MPI.MPI_Finalize();
    }

    public static void test_probe(String[] args){
        MPI.MPI_Init(args);
        MPI_Status s = new MPI_Status();
        int rank =  MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);

        // System.out.println(MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD));
        // MPI.MPI_Send("niki".toCharArray(),1,2,3);

        if(rank == 1){
            System.out.printf("Rank: %d Size: %d \n",
                rank,
            MPI.MPI_Comm_size(MPI.MPI_COMM_WORLD));

            MPI.MPI_Ssend(new byte[]{0x11,0x22,0x33,0x44},MPI.BYTE,0,0,MPI.MPI_COMM_WORLD);
        }
        else if(rank == 0){
            byte[] buff = new byte[20];
            MPI.MPI_Probe(1,0,MPI.MPI_COMM_WORLD,s);
            int result = MPI.MPI_Recv(buff,MPI.BYTE,1,0,MPI.MPI_COMM_WORLD,null);
            // System.out.printf("result: %d\n",result);
            for(int i = 0;i < 4;i++){
                System.out.printf("0x%02X ",buff[i]);
            }
            System.out.println();
            System.out.printf("%d %d %d %d %d\n",
                s.count_lo,s.count_hi_and_cancelled,s.MPI_SOURCE,s.MPI_TAG,s.MPI_ERROR);
            int count = MPI.MPI_Get_count(s,MPI.BYTE);
            System.out.println(String.valueOf(count));
        }

        MPI.MPI_Finalize();
    }

    public static void test_iprobe(String[] args){
        MPI.MPI_Init(args);
        MPI_Status s = new MPI_Status();
        int rank =  MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);

        // System.out.println(MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD));
        // MPI.MPI_Send("niki".toCharArray(),1,2,3);

        if(rank == 1){
            System.out.printf("Rank: %d Size: %d \n",
                rank,
            MPI.MPI_Comm_size(MPI.MPI_COMM_WORLD));

            MPI.MPI_Ssend(new byte[]{0x11,0x22,0x33,0x44},MPI.BYTE,0,0,MPI.MPI_COMM_WORLD);
        }
        else if(rank == 0){
            byte[] buff = new byte[20];
            while(!MPI.MPI_Iprobe(1,0,MPI.MPI_COMM_WORLD,s)){
                System.out.printf(".");
            }
            System.out.println();
            int result = MPI.MPI_Recv(buff,MPI.BYTE,1,0,MPI.MPI_COMM_WORLD,null);
            // System.out.printf("result: %d\n",result);
            for(int i = 0;i < 4;i++){
                System.out.printf("0x%02X ",buff[i]);
            }
            System.out.println();
            System.out.printf("%d %d %d %d %d\n",
                s.count_lo,s.count_hi_and_cancelled,s.MPI_SOURCE,s.MPI_TAG,s.MPI_ERROR);
            int count = MPI.MPI_Get_count(s,MPI.BYTE);
            System.out.println(String.valueOf(count));
        }

        MPI.MPI_Finalize();
    }

    public static void test_mprobe(String[] args){
        MPI.MPI_Init(args);
        MPI_Status s = new MPI_Status();
        int rank =  MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);

        // System.out.println(MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD));
        // MPI.MPI_Send("niki".toCharArray(),1,2,3);

        if(rank == 1){
            System.out.printf("Rank: %d Size: %d \n",
                rank,
            MPI.MPI_Comm_size(MPI.MPI_COMM_WORLD));

            MPI.MPI_Ssend(new int[]{0x11,0x22,0x33,0x44},MPI.INT,0,0,MPI.MPI_COMM_WORLD);
        }
        else if(rank == 0){
            int[] buff = new int[20];
            MPI_Message msg = new MPI_Message();
            MPI.MPI_Mprobe(1,0,MPI.MPI_COMM_WORLD,msg,s);
            System.out.println(msg.handler);
            int result = MPI.MPI_Mrecv(buff,MPI.INT,msg,s);
            // System.out.printf("result: %d\n",result);
            for(int i = 0;i < 4;i++){
                System.out.printf("0x%02X ",buff[i]);
            }
            System.out.println();
            System.out.printf("%d %d %d %d %d\n",
                s.count_lo,s.count_hi_and_cancelled,s.MPI_SOURCE,s.MPI_TAG,s.MPI_ERROR);
            int count = MPI.MPI_Get_count(s,MPI.BYTE);
            System.out.println(String.valueOf(count));
        }

        MPI.MPI_Finalize();
    }

    public static void test_miprobe(String[] args){
        MPI.MPI_Init(args);
        MPI_Status s = new MPI_Status();
        int rank =  MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);

        // System.out.println(MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD));
        // MPI.MPI_Send("niki".toCharArray(),1,2,3);

        if(rank == 1){
            System.out.printf("Rank: %d Size: %d \n",
                rank,
            MPI.MPI_Comm_size(MPI.MPI_COMM_WORLD));

            MPI.MPI_Ssend(new byte[]{0x11,0x22,0x33,0x44},MPI.BYTE,0,0,MPI.MPI_COMM_WORLD);
        }
        else if(rank == 0){
            byte[] buff = new byte[20];
            MPI_Message msg = new MPI_Message();
            MPI_Request req = new MPI_Request();
            while(!MPI.MPI_Improbe(1,0,MPI.MPI_COMM_WORLD,msg,s)){
                System.out.printf(".");
            }
            System.out.println();
            System.out.println(msg);
            int result = MPI.MPI_Imrecv(buff,MPI.BYTE,msg,req);
            System.out.printf("%d %d %d %d %d\n",
                s.count_lo,s.count_hi_and_cancelled,s.MPI_SOURCE,s.MPI_TAG,s.MPI_ERROR);
            MPI.MPI_Wait(req,s);
            // System.out.printf("result: %d\n",result);
            for(int i = 0;i < 4;i++){
                System.out.printf("0x%02X ",buff[i]);
            }
            System.out.println();
            System.out.printf("%d %d %d %d %d\n",
                s.count_lo,s.count_hi_and_cancelled,s.MPI_SOURCE,s.MPI_TAG,s.MPI_ERROR);
            int count = MPI.MPI_Get_count(s,MPI.BYTE);
            System.out.println(String.valueOf(count));
        }

        MPI.MPI_Finalize();
    }

    public static void test_cancel(String[] args){
        MPI.MPI_Init(args);

        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        if(rank == 0){
            MPI_Request[] requests = new MPI_Request[9];
            List<int[]> buff = new ArrayList<int[]>(10);
            
            for(int i = 1;i < 10;i++){
                // System.out.println("*****************");
                buff.add(new int[7]);
                requests[i-1] = new MPI_Request();
                MPI.MPI_Irecv(buff.get(i-1),MPI.INT,i,0,MPI.MPI_COMM_WORLD,requests[i-1]);
            }
            MPI.MPI_Cancel(requests[0]);
            MPI.MPI_Cancel(requests[4]);
            for(int i = 0;i < 9;i++){
                int index = MPI.MPI_Waitany(requests,null);
                int[] arr = buff.get(index);
                System.out.println(Arrays.toString(arr));
            }
        }
        else{
            MPI_Request req = new MPI_Request();
            MPI_Status stat = new MPI_Status();
            // if(rank == 1){
                Random rand = new Random();
                try{ Thread.sleep(Math.abs(rand.nextInt())%400); }
                catch(InterruptedException e){ e.printStackTrace(); }
            // }
            Random random = new Random();
            MPI.MPI_Isend(new int[]{random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),rank},MPI.INT,0,0,MPI.MPI_COMM_WORLD,req);
            MPI.MPI_Cancel(req);
            MPI.MPI_Wait(req,null);
        }

        MPI.MPI_Finalize();
    }

    public static void test_testcancelled(String[] args){
        MPI.MPI_Init(args);

        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        if(rank == 0){
            MPI_Request[] requests = new MPI_Request[9];
            List<int[]> buff = new ArrayList<int[]>(10);
            
            for(int i = 1;i < 10;i++){
                // System.out.println("*****************");
                buff.add(new int[7]);
                requests[i-1] = new MPI_Request();
                MPI.MPI_Irecv(buff.get(i-1),MPI.INT,i,0,MPI.MPI_COMM_WORLD,requests[i-1]);
            }
            MPI.MPI_Cancel(requests[0]);
            MPI.MPI_Cancel(requests[4]);
            for(int i = 0;i < 9;i++){
                MPI_Status stat = new MPI_Status();           
                int index = MPI.MPI_Waitany(requests,stat);
                System.out.println(MPI.MPI_Test_cancelled(stat));
                int[] arr = buff.get(index);
                System.out.println(Arrays.toString(arr));
            }
        }
        else{
            MPI_Request req = new MPI_Request();
            MPI_Status stat = new MPI_Status();
            // if(rank == 1){
                Random rand = new Random();
                try{ Thread.sleep(Math.abs(rand.nextInt())%400); }
                catch(InterruptedException e){ e.printStackTrace(); }
            // }
            Random random = new Random();
            MPI.MPI_Isend(new int[]{random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),
                    random.nextInt(),rank},MPI.INT,0,0,MPI.MPI_COMM_WORLD,req);
            MPI.MPI_Cancel(req);
            MPI.MPI_Wait(req,null);
        }

        MPI.MPI_Finalize();
    }

    public static void test_pres(String[] args){
        MPI.MPI_Init(args);

        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        MPI_Request send = new MPI_Request();
        MPI_Request recv = new MPI_Request();
        ByteBuffer sendBuffer = ByteBuffer.allocateDirect(1024);
        ByteBuffer recvBuffer = ByteBuffer.allocateDirect(1024);

        MPI.MPI_Rsend_init(sendBuffer,1,0,MPI.MPI_COMM_WORLD,send);
        MPI.MPI_Recv_init(recvBuffer,0,0,MPI.MPI_COMM_WORLD,recv);
        if(rank == 0){
            for(int i = 0;i < 9;i++){
                sendBuffer.position(0);
                sendBuffer.putInt(i);
                sendBuffer.putInt(40);

                MPI.MPI_Start(send);

                MPI.MPI_Wait(send,null);
            }
        }
        else if(rank == 1){
            for(int i = 0;i < 9;i++){
                MPI.MPI_Start(recv);

                MPI.MPI_Wait(recv,null);

                recvBuffer.position(0);
                System.out.printf("%d %d\n",recvBuffer.getInt(),recvBuffer.getInt());
            }
        }

        MPI.MPI_Request_free(send);
        MPI.MPI_Request_free(recv);

        MPI.MPI_Finalize();
    }

    public static void test_sendrecv(String[] args){
        MPI.MPI_Init(args);

        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        int numprocs = MPI.MPI_Comm_size(MPI.MPI_COMM_WORLD);
        MPI_Status stat = new MPI_Status();

        byte[] buff = new byte[10];
        byte[] buff1 = new byte[10];

        int left,right;

        right = (rank + 1) % numprocs;
        left = rank - 1;
        if (left < 0)
            left = numprocs - 1;
 

        buff[0] = 10;
        buff[1] = (byte)rank;
        buff[2] = 11;
        buff[3] = (byte)0xAA;
        buff[4] = (byte)0x55;
        buff[9] = (byte)0x55;
        // if(rank == 0 || rank == 1){
            MPI.MPI_Sendrecv(buff,MPI.BYTE,right,0,
                buff1,MPI.BYTE,left,0,
                MPI.MPI_COMM_WORLD,stat);
        // }
        // if(rank == 1){
            System.out.println(Arrays.toString(buff1));
        // }   
        System.out.printf("%d %d %d %d %d\n",
                stat.count_lo,
                stat.count_hi_and_cancelled,
                stat.MPI_SOURCE,
                stat.MPI_TAG,
                stat.MPI_ERROR);

        MPI.MPI_Finalize();
    }

    public static void test_objsend(String[] args){
        MPI.MPI_Init(args);
        int rank;
        MPI.MPI_Finalize();
    }

    public static void test_iobjsend(String[] args){
        MPI.MPI_Init(args);
        int rank;
        MPI.MPI_Finalize();
    }

    public static void test_bcast(String[] args){
        MPI.MPI_Init(args);

        int[] buffer = new int[10];

        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);

        if(rank == 0){
            buffer[0] = 0xAA;
            buffer[1] = 0x55;
            buffer[2] = 0xAA;
            buffer[3] = 0x55;
            buffer[4] = 0xAA;
            buffer[5] = 0x55;
            buffer[6] = 0xAA;
            buffer[7] = 0x55;
            buffer[8] = 0xBA;
            buffer[9] = 0xCF;
        }

        MPI.MPI_Bcast(buffer,MPI.INT,0,MPI.MPI_COMM_WORLD);
        Random rand = new Random();

        try{ Thread.sleep(Math.abs(rand.nextInt())%100); }
        catch(InterruptedException e){ e.printStackTrace(); }
        buffer[0] = rank;
        System.out.println(Arrays.toString(buffer));

        MPI.MPI_Barrier(MPI.MPI_COMM_WORLD);

        MPI.MPI_Finalize();
    }

    public static void test_ibcast(String[] args){
        MPI.MPI_Init(args);

        int[] buffer = new int[10];

        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);

        if(rank == 0){
            buffer[0] = 0xAA;
            buffer[1] = 0x55;
            buffer[2] = 0xAA;
            buffer[3] = 0x55;
            buffer[4] = 0xAA;
            buffer[5] = 0x55;
            buffer[6] = 0xAA;
            buffer[7] = 0x55;
            buffer[8] = 0xBA;
            buffer[9] = 0xCF;
        }
        MPI_Request req = new MPI_Request();
        MPI.MPI_Ibcast(buffer,MPI.INT,0,MPI.MPI_COMM_WORLD,req);
        Random rand = new Random();
        while(!MPI.MPI_Test(req,null)){
            System.out.printf(".");
        };
        System.out.println();
        try{ Thread.sleep(Math.abs(rand.nextInt())%100); }
        catch(InterruptedException e){ e.printStackTrace(); }
        buffer[0] = rank;
        System.out.println(Arrays.toString(buffer));

        MPI.MPI_Barrier(MPI.MPI_COMM_WORLD);

        MPI.MPI_Finalize();
    }

    public static void test_scatter(String[] args){
        MPI.MPI_Init(args);

        int[] in_buffer = new int[10];
        int[] out_buffer = new int[10];

        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);

        if(rank == 0){
            in_buffer[0] = 0xAA;
            in_buffer[1] = 0x55;
            in_buffer[2] = 0xAA;
            in_buffer[3] = 0x55;
            in_buffer[4] = 0xAA;
            in_buffer[5] = 0x55;
            in_buffer[6] = 0xAA;
            in_buffer[7] = 0x55;
            in_buffer[8] = 0xBA;
            in_buffer[9] = 0xCF;
        }

        MPI.MPI_Scatter(in_buffer,1,MPI.INT,
        out_buffer,1,MPI.INT,0,MPI.MPI_COMM_WORLD);

        Random rand = new Random();

        try{ Thread.sleep(Math.abs(rand.nextInt())%100); }
        catch(InterruptedException e){ e.printStackTrace(); }
        out_buffer[1] = rank;
        System.out.println(Arrays.toString(out_buffer));

        MPI.MPI_Barrier(MPI.MPI_COMM_WORLD);

        MPI.MPI_Finalize();
    }

    public static void test_gather(String[] args){
        MPI.MPI_Init(args);

        int[] in_buffer = new int[10];
        int[] out_buffer = new int[10];

        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        if(rank != 0){
            in_buffer[0] = rank;
        }
        else{
            in_buffer[0] = -1;
        }

        MPI.MPI_Gather(in_buffer,1,MPI.INT,
        out_buffer,1,MPI.INT,0,MPI.MPI_COMM_WORLD);

        Random rand = new Random();

        try{ Thread.sleep(Math.abs(rand.nextInt())%100); }
        catch(InterruptedException e){ e.printStackTrace(); }
        if(rank == 0){
            System.out.println(Arrays.toString(out_buffer));
        }

        MPI.MPI_Barrier(MPI.MPI_COMM_WORLD);

        MPI.MPI_Finalize();
    }

    public static void test_2dscatter(String[] args){
        MPI.MPI_Init(args);

        byte[][] _in = new byte[10][10];
        byte[] _out = new byte[10];

        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        if(rank == 0){
            for(int i = 0;i < 10;i++){
                _in[i][0] = (byte)i;
                _in[i][4] = (byte)0x55; 
            }
        }

        MPI.MPI_2DScatter(_in,5,MPI.BYTE,
            _out,5,MPI.BYTE,0,MPI.MPI_COMM_WORLD);

        Random rand = new Random();

        try{ Thread.sleep(Math.abs(rand.nextInt())%100); }
        catch(InterruptedException e){ e.printStackTrace(); }
        System.out.println(Arrays.toString(_out));

        MPI.MPI_Barrier(MPI.MPI_COMM_WORLD);

        MPI.MPI_Finalize();
    }

    public static void test_2dgather(String[] args){
        MPI.MPI_Init(args);

        int[] in_buffer = new int[10];
        int[][] out_buffer = new int[10][10];

        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        in_buffer[0] = rank;
        in_buffer[4] = 0x55;

        MPI.MPI_2DGather(in_buffer,5,MPI.INT,
        out_buffer,5,MPI.INT,0,MPI.MPI_COMM_WORLD);

        Random rand = new Random();

        try{ Thread.sleep(Math.abs(rand.nextInt())%100); }
        catch(InterruptedException e){ e.printStackTrace(); }
        if(rank == 0){
            for(int i = 0;i < 10;i++){
                System.out.println(Arrays.toString(out_buffer[i]));
            }
        }

        MPI.MPI_Barrier(MPI.MPI_COMM_WORLD);

        MPI.MPI_Finalize();
    }

    public static void test_iscatter(String[] args){
        MPI.MPI_Init(args);

        int[] in_buffer = new int[10];
        int[] out_buffer = new int[10];

        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);

        if(rank == 0){
            in_buffer[0] = 0xAA;
            in_buffer[1] = 0x55;
            in_buffer[2] = 0xAA;
            in_buffer[3] = 0x55;
            in_buffer[4] = 0xAA;
            in_buffer[5] = 0x55;
            in_buffer[6] = 0xAA;
            in_buffer[7] = 0x55;
            in_buffer[8] = 0xBA;
            in_buffer[9] = 0xCF;
        }

        MPI_Request req = new MPI_Request();

        MPI.MPI_Iscatter(in_buffer,1,MPI.INT,
            out_buffer,1,MPI.INT,0,MPI.MPI_COMM_WORLD,req);

        while(!MPI.MPI_Test(req,null)){
            System.out.printf(".");
        }
        System.out.println();

        Random rand = new Random();

        try{ Thread.sleep(Math.abs(rand.nextInt())%100); }
        catch(InterruptedException e){ e.printStackTrace(); }
        out_buffer[1] = rank;
        System.out.println(Arrays.toString(out_buffer));

        MPI.MPI_Barrier(MPI.MPI_COMM_WORLD);

        MPI.MPI_Finalize();
    }

    public static void test_alltoall(String[] args){
        MPI.MPI_Init(args);

        int[] in_buffer = new int[10];
        int[] out_buffer = new int[10];

        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        // if(rank != 0){
            in_buffer[rank] = rank;
        // }

        MPI.MPI_Alltoall(in_buffer,1,MPI.INT,
        out_buffer,1,MPI.INT,MPI.MPI_COMM_WORLD);

        Random rand = new Random();

        try{ Thread.sleep(Math.abs(rand.nextInt())%100); }
        catch(InterruptedException e){ e.printStackTrace(); }
        // if(rank == 0){
            System.out.println(Arrays.toString(out_buffer));
        // }

        MPI.MPI_Barrier(MPI.MPI_COMM_WORLD);

        MPI.MPI_Finalize();
    }

    public static void test_allgather(String[] args){
        MPI.MPI_Init(args);

        int[] in_buffer = new int[10];
        int[] out_buffer = new int[10];

        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        // if(rank != 0){
            in_buffer[0] = rank;
        // }

        MPI.MPI_Allgather(in_buffer,1,MPI.INT,
        out_buffer,1,MPI.INT,MPI.MPI_COMM_WORLD);

        Random rand = new Random();

        try{ Thread.sleep(Math.abs(rand.nextInt())%100); }
        catch(InterruptedException e){ e.printStackTrace(); }
        // if(rank == 0){
            System.out.println(Arrays.toString(out_buffer));
        // }

        MPI.MPI_Barrier(MPI.MPI_COMM_WORLD);

        MPI.MPI_Finalize();
    }

    public static void test_reduce(String[] args){
        MPI.MPI_Init(args);
        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);

        int[] in = new int[]{rank};
        int[] out = new int[5];

        MPI.MPI_Reduce(in,out,1,MPI.INT,MPI.MPI_MAX,0,MPI.MPI_COMM_WORLD);

        if(rank == 0){
            System.out.println(Arrays.toString(out));
        }

        MPI.MPI_Finalize();
    }

    public static void test_ireduce(String[] args){
        MPI.MPI_Init(args);
        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);

        int[] in = new int[]{rank};
        int[] out = new int[5];
        MPI_Request req = new MPI_Request();

        MPI.MPI_Ireduce(in,out,1,MPI.INT,MPI.MPI_MAX,0,MPI.MPI_COMM_WORLD,req);

        while(!MPI.MPI_Test(req,null)){
            System.out.printf(".");
        }
        System.out.println();

        if(rank == 0){
            System.out.println(Arrays.toString(out));
        }

        MPI.MPI_Finalize();
    }

    public static void test_allreduce(String[] args){
        MPI.MPI_Init(args);
        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);

        int[] in = new int[]{rank};
        int[] out = new int[5];
        MPI_Request req = new MPI_Request();

        MPI.MPI_Allreduce(in,out,1,MPI.INT,MPI.MPI_MAX,MPI.MPI_COMM_WORLD);

        System.out.println();

        // if(rank == 0){
            System.out.println(Arrays.toString(out));
        // }

        MPI.MPI_Finalize();
    }

    public static void test_reducescatter(String[] args){

        MPI.MPI_Init(args);
        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        int size = MPI.MPI_Comm_size(MPI.MPI_COMM_WORLD);

        int[] sendbuf = new int[size];
        int[] recvbuf = new int[2];

        for (int i=0; i<size; i++)
            sendbuf[i] = 1 + rank + size*i;

        // System.out.printf("Proc %d: ", rank);
        // for (int i= 0; i<size; i++) 
        //     System.out.printf("%d ", sendbuf[i]);
        // System.out.println();

        int[] recvcounts = new int[size];
        for (int i=0; i<size; i++)
            recvcounts[i] = 1;

        MPI.MPI_Reduce_scatter(sendbuf, recvbuf, recvcounts, 
            MPI.INT, MPI.MPI_MAX, MPI.MPI_COMM_WORLD);
        Random rand = new Random();

        try{ Thread.sleep(Math.abs(rand.nextInt())%100); }
        catch(InterruptedException e){ e.printStackTrace(); }

        System.out.printf("proc %d: %d\n", rank, recvbuf[0]);

        MPI.MPI_Finalize();

    }

    public static void test_ireducescatter(String[] args){

        MPI.MPI_Init(args);
        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        int size = MPI.MPI_Comm_size(MPI.MPI_COMM_WORLD);

        int[] sendbuf = new int[size];
        int[] recvbuf = new int[2];

        for (int i=0; i<size; i++)
            sendbuf[i] = 1 + rank + size*i;

        // System.out.printf("Proc %d: ", rank);
        // for (int i= 0; i<size; i++) 
        //     System.out.printf("%d ", sendbuf[i]);
        // System.out.println();

        int[] recvcounts = new int[size];
        for (int i=0; i<size; i++)
            recvcounts[i] = 1;
        MPI_Request req = new MPI_Request();

        MPI.MPI_Ireduce_scatter(sendbuf, recvbuf, recvcounts, 
            MPI.INT, MPI.MPI_MAX, MPI.MPI_COMM_WORLD,req);
        while(!MPI.MPI_Test(req,null)){
            System.out.printf(".");
        }
        System.out.println();
        Random rand = new Random();

        try{ Thread.sleep(Math.abs(rand.nextInt())%100); }
        catch(InterruptedException e){ e.printStackTrace(); }

        System.out.printf("proc %d: %d\n", rank, recvbuf[0]);

        MPI.MPI_Finalize();

    }

    public static void test_reducescatterblock(String[] args){

        MPI.MPI_Init(args);
        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        int size = MPI.MPI_Comm_size(MPI.MPI_COMM_WORLD);

        int[] sendbuf = new int[size];
        int[] recvbuf = new int[2];

        for (int i=0; i<size; i++)
            sendbuf[i] = 1 + rank + size*i;

        // System.out.printf("Proc %d: ", rank);
        // for (int i= 0; i<size; i++) 
        //     System.out.printf("%d ", sendbuf[i]);
        // System.out.println();


        MPI.MPI_Reduce_scatter_block(sendbuf, recvbuf, 1, 
            MPI.INT, MPI.MPI_MAX, MPI.MPI_COMM_WORLD);
        Random rand = new Random();

        try{ Thread.sleep(Math.abs(rand.nextInt())%100); }
        catch(InterruptedException e){ e.printStackTrace(); }

        System.out.printf("proc %d: %d\n", rank, recvbuf[0]);

        MPI.MPI_Finalize();

    }

    public static void test_ireducescatterblock(String[] args){

        MPI.MPI_Init(args);
        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        int size = MPI.MPI_Comm_size(MPI.MPI_COMM_WORLD);

        int[] sendbuf = new int[size];
        int[] recvbuf = new int[2];

        for (int i=0; i<size; i++)
            sendbuf[i] = 1 + rank + size*i;

        // System.out.printf("Proc %d: ", rank);
        // for (int i= 0; i<size; i++) 
        //     System.out.printf("%d ", sendbuf[i]);
        // System.out.println();

        MPI_Request req = new MPI_Request();

        MPI.MPI_Ireduce_scatter_block(sendbuf, recvbuf, 1, 
            MPI.INT, MPI.MPI_MAX, MPI.MPI_COMM_WORLD,req);
        while(!MPI.MPI_Test(req,null)){
            System.out.printf(".");
        }
        System.out.println();
        Random rand = new Random();

        try{ Thread.sleep(Math.abs(rand.nextInt())%100); }
        catch(InterruptedException e){ e.printStackTrace(); }

        System.out.printf("proc %d: %d\n", rank, recvbuf[0]);

        MPI.MPI_Finalize();

    }

    public static void test_allgatherv(String[] args){
        int MAX_PROCESSES = 10;
        int[] table = new int[100];
        int[] result = new int[20];
        MPI.MPI_Init(args);
        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        int size = MPI.MPI_Comm_size(MPI.MPI_COMM_WORLD);
        int participants = size; 

        int[] counts = new int[10];
        int[] disp = new int[10];
       
        for(int i = 0;i < 10;i++){
            table[i] = rank;
            counts[i] = 1;
            disp[i] = i*2;
        }

        MPI.MPI_Allgatherv(table,1,MPI.INT,
            result,counts,disp,MPI.INT,MPI.MPI_COMM_WORLD);
        Random rand = new Random();

        try{ Thread.sleep(Math.abs(rand.nextInt())%100); }
        catch(InterruptedException e){ e.printStackTrace(); }
        
        System.out.println(Arrays.toString(result));

        MPI.MPI_Finalize();
    }

    public static void test_iallgatherv(String[] args){
        int MAX_PROCESSES = 10;
        int[] table = new int[100];
        int[] result = new int[20];
        MPI.MPI_Init(args);
        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        int size = MPI.MPI_Comm_size(MPI.MPI_COMM_WORLD);
        int participants = size; 

        int[] counts = new int[10];
        int[] disp = new int[10];
       
        for(int i = 0;i < 10;i++){
            table[i] = rank;
            counts[i] = 1;
            disp[i] = i*2;
        }
        MPI_Request req = new MPI_Request();
        MPI.MPI_Iallgatherv(table,1,MPI.INT,
            result,counts,disp,MPI.INT,MPI.MPI_COMM_WORLD,req);
        while(!MPI.MPI_Test(req,null)){
            System.out.printf(".");
        }
        System.out.println();
        Random rand = new Random();

        try{ Thread.sleep(Math.abs(rand.nextInt())%100); }
        catch(InterruptedException e){ e.printStackTrace(); }
        
        System.out.println(Arrays.toString(result));

        MPI.MPI_Finalize();
    }

    public static void test_scan(String[] args){
        MPI.MPI_Init(args);

        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        int[] in = new int[]{rank};
        int[] out = new int[2];

        MPI.MPI_Scan(in,out,1,
            MPI.INT,MPI.MPI_MAX,MPI.MPI_COMM_WORLD);

        Random rand = new Random();

        try{ Thread.sleep(Math.abs(rand.nextInt())%100); }
        catch(InterruptedException e){ e.printStackTrace(); }
        System.out.println(out[0]);


        MPI.MPI_Finalize();
    }

    public static void test_scatterv(String[] args){
        MPI.MPI_Init(args);
        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        int[] sendbuff = new int[100];
        int[] counts = new int[10];
        int[] disp = new int[10];
        int[] recvbuff = new int[10];

        if(rank == 9){
            for(int i = 0;i < 10;i++){
                disp[i] = 10*i;
                counts[i] = 10;
            }
            int c = 0;
            for(int i = 0;i < 100;i++){
                sendbuff[i] = c;
                if(i%10 == 9){
                    c++;
                }
            }
        }

        MPI.MPI_Scatterv(sendbuff,counts,disp,MPI.INT,
            recvbuff,10,MPI.INT,9,MPI.MPI_COMM_WORLD);

        Random rand = new Random();

        try{ Thread.sleep(Math.abs(rand.nextInt())%100); }
        catch(InterruptedException e){ e.printStackTrace(); }

        System.out.println(Arrays.toString(recvbuff));
        
        
        MPI.MPI_Finalize();
    }

    public static void test_gatherv(String[] args){
        MPI.MPI_Init(args);
        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        int[] sendbuff = new int[10];
        int[] counts = new int[10];
        int[] disp = new int[10];
        int[] recvbuff = new int[100];

        if(rank == 9){
            for(int i = 0;i < 10;i++){
                disp[i] = 10*i;
                counts[i] = 10;
            }
        }

        for(int i = 0;i < 10;i++){
            sendbuff[i] = rank;
        }

        MPI.MPI_Gatherv(sendbuff,10,MPI.INT,
            recvbuff,counts,disp,MPI.INT,9,MPI.MPI_COMM_WORLD);

        if(rank == 9){
            System.out.println(Arrays.toString(recvbuff));
        }
        
        
        MPI.MPI_Finalize();
    }

    public static void test_iscatterv(String[] args){
        MPI.MPI_Init(args);
        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        int[] sendbuff = new int[100];
        int[] counts = new int[10];
        int[] disp = new int[10];
        int[] recvbuff = new int[10];

        if(rank == 9){
            for(int i = 0;i < 10;i++){
                disp[i] = 10*i;
                counts[i] = 10;
            }
            int c = 0;
            for(int i = 0;i < 100;i++){
                sendbuff[i] = c;
                if(i%10 == 9){
                    c++;
                }
            }
        }
        MPI_Request req = new MPI_Request();
        MPI.MPI_Iscatterv(sendbuff,counts,disp,MPI.INT,
            recvbuff,10,MPI.INT,9,MPI.MPI_COMM_WORLD,req);
        while(!MPI.MPI_Test(req,null)){
            System.out.printf(".");
        }
            System.out.println();
        Random rand = new Random();

        try{ Thread.sleep(Math.abs(rand.nextInt())%100); }
        catch(InterruptedException e){ e.printStackTrace(); }

        System.out.println(Arrays.toString(recvbuff));
        
        
        MPI.MPI_Finalize();
    }

    public static void test_igatherv(String[] args){
        MPI.MPI_Init(args);
        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        int[] sendbuff = new int[10];
        int[] counts = new int[10];
        int[] disp = new int[10];
        int[] recvbuff = new int[100];

        if(rank == 9){
            for(int i = 0;i < 10;i++){
                disp[i] = 10*i;
                counts[i] = 10;
            }
        }

        for(int i = 0;i < 10;i++){
            sendbuff[i] = rank;
        }

        MPI_Request req = new MPI_Request();

        MPI.MPI_Igatherv(sendbuff,10,MPI.INT,
            recvbuff,counts,disp,MPI.INT,9,MPI.MPI_COMM_WORLD,req);
        while(!MPI.MPI_Test(req,null)){
            System.out.printf(".");
        }
        System.out.println();

        if(rank == 9){
            System.out.println(Arrays.toString(recvbuff));
        }
        
        
        MPI.MPI_Finalize();
    }

    public static void test_libversion(String[] args){
        MPI.MPI_Init(args);
        
        String libversion = MPI.MPI_Get_library_version();

        System.out.println(libversion);
        
        MPI.MPI_Finalize();
    }

    public static void test_spawn(String[] args){
        MPI.MPI_Init(args);
        String command = "java";
        String[] _args = {"org.mpich.Main", null};
        int maxprocs = 4;
        int[] error_codes = new int[4];
        int parentcomm = MPI.MPI_Comm_get_parent();

        if(parentcomm == MPI.MPI_COMM_NULL){
            System.out.println("From parent!");
            int intercomm = MPI.MPI_Comm_spawn(command,_args,maxprocs,
                MPI.MPI_INFO_NULL,0,MPI.MPI_COMM_WORLD,error_codes);
        }
        else{
            System.out.println("From spawn!");
        }
        MPI.MPI_Finalize();
    }

    public static void test_wincreate(String[] args){
        MPI.MPI_Init(args);

        MPI_Win_buffer buff = new MPI_Win_buffer(400);
        int win = MPI.MPI_Win_create(buff,10,MPI.MPI_INFO_NULL,
            MPI.MPI_COMM_WORLD);

        MPI.MPI_Finalize();
    }

    public static void test_winallocate(String[] args){
        MPI.MPI_Init(args);

        MPI_Win_buffer buff = new MPI_Win_buffer(400);
        int win = MPI.MPI_Win_allocate(10,MPI.MPI_INFO_NULL,
            MPI.MPI_COMM_WORLD,buff);

        win = MPI.MPI_Win_free(win);

        MPI.MPI_Finalize();
    }

    public static void test_openclosefile(String[] args){
        MPI.MPI_Init(args);

        long fh = MPI.MPI_File_open(MPI.MPI_COMM_WORLD,"temp",
            MPI.MPI_MODE_RDWR|MPI.MPI_MODE_DELETE_ON_CLOSE|
            MPI.MPI_MODE_CREATE,MPI.MPI_INFO_NULL);

        // MPI.MPI_File_set_size(fh,10);

        System.out.println("done");

        MPI.MPI_File_close(fh);
        MPI.MPI_Finalize();
    }

    public static void test_writereadfile(String[] args)
    {
        int[] buff = new int[10];
        MPI_Status stat = new MPI_Status();

        MPI.MPI_Init(args);

        int rank = MPI.MPI_Comm_rank(MPI.MPI_COMM_WORLD);
        long fh = MPI.MPI_File_open(MPI.MPI_COMM_WORLD,
                "workfile",
            MPI.MPI_MODE_RDWR | MPI.MPI_MODE_CREATE |
            MPI.MPI_MODE_DELETE_ON_CLOSE,
            MPI.MPI_INFO_NULL);
        MPI.MPI_File_set_view(fh,0,MPI.INT,MPI.INT,"native",
            MPI.MPI_INFO_NULL);
        MPI.MPI_File_set_atomicity(fh,true);
        if(rank == 0){
            for(int i = 0;i < 10;i++){
                buff[i] = 5;
            }
            buff[0] = rank;
            MPI.MPI_File_write_at(fh,0,buff,10,MPI.INT,stat);
        }
        MPI.MPI_Barrier(MPI.MPI_COMM_WORLD);
        if(rank == 1){
            MPI.MPI_File_read_at(fh,0,buff,10,MPI.INT,stat);
            System.out.println(Arrays.toString(buff));
        }

        MPI.MPI_File_close(fh);

        MPI.MPI_Finalize();
    }

    public static void main(String[] args) {
        test_writereadfile(args);
    }
}