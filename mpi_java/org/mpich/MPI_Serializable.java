package org.mpich;

import java.nio.ByteBuffer;

interface MPI_Serializable {
    public ByteBuffer mpi_get_buff(boolean toSet);
    public void mpi_create();
}