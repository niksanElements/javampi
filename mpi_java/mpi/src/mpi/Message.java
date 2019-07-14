package mpi;

import java.nio.ByteBuffer;

import mpi.datatype.Datatype;

/**
 * MPI_Message
 */
public class Message {
    private long handler;
    private Status status;

    public Message(long handler,Status status){
        this.handler = handler;
        this.status = status;
    }

    public long getHandler() {
        return handler;
    }

    public Status getStatus() {
        return status;
    }

    // MPI_MRECV
    public Status mrecv(Object buff,int offset,int count,
        Datatype datatype,ByteBuffer objBuff
    ){
        MPI.checkInitialization();
        Status stat = new Status(0, 0, 0, 0, 0);
        // TODO: To think of something to prevent that allocation 
        // on buffer when it comes to a Object communication
        if(!datatype.isPrimitive()){
            int cap = count*datatype.size();
            if(objBuff == null){
                objBuff = ByteBuffer.allocateDirect(cap);
            }
            else{
                // completely reset the buffer
                objBuff.limit(objBuff.capacity());
                objBuff.rewind();
            }
            Object[] objArr = (Object[])buff;
            for(int i = offset;i < (offset+count);i++){
                objArr[i] = datatype.constructFromByteByffer(objBuff);
            }

            this.handler = _mrecv(objArr,offset, count, datatype.getHandler(), 
                this.handler, stat);
        }
        else{
            this.handler = _mrecv(buff, offset, count, datatype.getHandler(), 
                this.handler, stat);
        } 

        return stat;
    }
    private static native long _mrecv(Object buff,int offset,int count,
        long datatype,long message,Status stat);

        // MPI_Irecv
    public Request imrecv(Object buff,int offset,int count,
        Datatype datatype
    ){
        MPI.checkInitialization();
        Request req = new Request(-1);

        this.handler = _imrecv(buff, offset, count, datatype.getHandler(), 
            this.handler, req);

        return req;
    }
    private static native long _imrecv(Object buff,int offset,int count,
        long datatype,long msg,Request request);
}