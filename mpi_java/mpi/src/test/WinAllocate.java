package test;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

import mpi.MPI;
import mpi.Win;

public class WinAllocate {

    /*
    // Copyright 2003-2014 Intel Corporation. All Rights Reserved.
    // 
    // The source code contained or described herein and all documents related 
    // to the source code ("Material") are owned by Intel Corporation or its
    // suppliers or licensors. Title to the Material remains with Intel Corporation
    // or its suppliers and licensors. The Material is protected by worldwide
    // copyright and trade secret laws and treaty provisions. No part of the
    // Material may be used, copied, reproduced, modified, published, uploaded,
    // posted, transmitted, distributed, or disclosed in any way without Intel's
    // prior express written permission.
    // 
    // No license under any patent, copyright, trade secret or other intellectual
    // property right is granted to or conferred upon you by disclosure or delivery
    // of the Materials, either expressly, by implication, inducement, estoppel
    // or otherwise. Any license under such intellectual property rights must
    // be express and approved by Intel in writing.
    */

    public static final int NUM_ELEMENT = 3;
    public static void main(String[] args) {

        ByteBuffer sharedbuffer;
        ByteBuffer localbuffer = ByteBuffer.allocateDirect(NUM_ELEMENT*4);

        MPI.Init(args);
        int id = MPI.COMM_WORLD.rank();
        int num_procs = MPI.COMM_WORLD.size();
        String name = MPI.processor_name();

        // System.out.printf("Rank %d running on %s\n", id, name);

        Win win = MPI.COMM_WORLD.win_allocate(NUM_ELEMENT*4, 1, MPI.INFO_NULL);
        sharedbuffer = win.getByteBuffer();

        for(int i = 0;i < NUM_ELEMENT;i++){
            System.out.printf("%d\n",sharedbuffer.getInt(i));
        }
        System.out.println();

        for (int i = 0; i < NUM_ELEMENT; i++)
        {
            sharedbuffer.putInt(i, id);
            localbuffer.putInt(i, 0);
        }
        System.out.println();

        win.fence(0);

        if (id != 0)
            win.get(localbuffer, 0, NUM_ELEMENT, MPI.INT_BUFFER, id-1, 0, NUM_ELEMENT, MPI.INT_BUFFER);
        else
            win.get(localbuffer, 0, NUM_ELEMENT, MPI.INT_BUFFER, num_procs-1, 0, NUM_ELEMENT, MPI.INT_BUFFER);
        win.fence(0);

        if(localbuffer.getInt(0) != id-1 && (id == 0 && localbuffer.getInt(0) != num_procs-1)){
            System.out.println("ERROR");
        }

        System.out.printf("\n");

        System.out.printf("Rank %d gets data from the shared memory:", id);

        for (int i = 0; i < NUM_ELEMENT; i++)
            System.out.printf(" %02d", localbuffer.getInt(i));

        win.fence(0);

        if (id < num_procs-1)
            win.put(localbuffer, 0, NUM_ELEMENT, MPI.INT_BUFFER, id+1, 0, NUM_ELEMENT, MPI.INT_BUFFER);
        else
            win.put(localbuffer, 0, NUM_ELEMENT, MPI.INT_BUFFER, 0, 0, NUM_ELEMENT, MPI.INT_BUFFER);

        win.fence(0);
        
        if(sharedbuffer.getInt(2) != id){
            Utils.sleepRand(200);
            System.out.printf("Error %d - %d\n",sharedbuffer.getInt(0),id);
            System.out.flush();
        }

        for (int i = 0; i < NUM_ELEMENT; i++){
            Utils.sleepRand(200);
            System.out.printf("(%d %d %d)",id, sharedbuffer.getInt(i),i);
        }

        System.out.printf("\n");

        win.free();
        MPI.Finalize();
    }
}