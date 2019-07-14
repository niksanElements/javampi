package mpi;

import mpi.datatype.Datatype;

public class Status {
    public int count_lo;
    public int count_hi_and_cancelled;
    public int mpi_source;
    public int mpi_tag;
    public int mpi_error;

    // this variable denotes wether a request is finished
    public boolean isRequestFinish;

    public Status(){

    }

    public Status(int count_lo,int count_hi_and_cancelled,
        int mpi_source,int mpi_tag,int mpi_error
    ){
        this.count_lo = count_lo;
        this.count_hi_and_cancelled = count_hi_and_cancelled;
        this.mpi_source = mpi_source;
        this.mpi_tag = mpi_tag;
        this.mpi_error = mpi_error;
        this.isRequestFinish = true;
    }

    public Status(int count_lo,int count_hi_and_cancelled,
        int mpi_source,int mpi_tag,int mpi_error,boolean isReqFinish
    ){
        this.count_lo = count_lo;
        this.count_hi_and_cancelled = count_hi_and_cancelled;
        this.mpi_source = mpi_source;
        this.mpi_tag = mpi_tag;
        this.mpi_error = mpi_error;
        this.isRequestFinish = isReqFinish;
    }

    /**
     * @return the status object elements as a array elements
     * 
     *  {
            
            count_lo   
            count_hi_and_cancelled
            mpi_source
            mpi_tag
            mpi_error
        }
     * 
     */
    private int[] getStatus(){
        return new int[] {
            this.count_lo,this.count_hi_and_cancelled,
            this.mpi_source,this.mpi_tag,this.mpi_error};
    }

    // set status
    private void setStatus(int count_lo,int count_hi_and_cancelled,
        int mpi_source,int mpi_tag,int mpi_error,boolean isReqFinish
    ){
        this.count_lo = count_lo;
        this.count_hi_and_cancelled = count_hi_and_cancelled;
        this.mpi_source = mpi_source;
        this.mpi_tag = mpi_tag;
        this.mpi_error = mpi_error;
        this.isRequestFinish = isReqFinish;
    }
    
    public int count(Datatype datatype) {
    	int count = ((count_hi_and_cancelled >> 1) << (8 *MPI.INT.size())) + count_lo; 
    	return count/datatype.size();
    }

    public boolean isRequestFinish() {
        return isRequestFinish;
    }
    // TODO: MPI_Test_cancelled
    public boolean cancelled(){
        boolean ret;
        int cancelled =  this.count_hi_and_cancelled & 1;
        if(cancelled != 0){
            ret = true;
        }
        else{
            ret = false;
        }

        return ret;
    }

}