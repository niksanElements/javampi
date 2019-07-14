package org.mpich;

import java.nio.ByteBuffer;

public class MPI_Win_buffer {
    private long base_address;
    private boolean MPI_Is_allocation;

    private ByteBuffer buffer;

    private int size;

    public MPI_Win_buffer(int size){
        this.MPI_Is_allocation = false;
        this.size = size;
    }

    public boolean MPI_Is_using_ByteBuffer(){
        if(this.buffer != null){
            return true;
        }

        return false;
    }

    public boolean MPI_Is_mpi_allocation(){
        return this.MPI_Is_allocation;
    }

    // allocates and get the buffer
    private ByteBuffer getByteBuffer(){
        if(this.buffer == null){
            this.buffer = ByteBuffer.allocateDirect(size);
        }

        return this.buffer;
    }
}