package mpi.op;

import java.nio.ByteBuffer;

import mpi.datatype.Datatype;

/**
 * Object Operation
 */
public abstract class ObjectOp {
    private Datatype type;

    public ObjectOp(Datatype type){
        this.type = type;
    }

    public abstract Object operation(Object a,Object b);

    private void _operation(ByteBuffer a_buff,ByteBuffer b_buff){
        Object a = this.type.constructFromByteByffer(a_buff);
        Object b = this.type.constructFromByteByffer(b_buff);

        Object c = this.operation(a, b);

        b_buff.position(0);
        this.type.setToByteBuffer(c, b_buff);
    }
}