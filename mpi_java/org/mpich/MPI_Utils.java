package org.mpich;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.ObjectInput;
import java.io.ObjectInputStream;
import java.io.ObjectOutput;
import java.io.ObjectOutputStream;
import java.io.Serializable;

public class MPI_Utils{
    public static byte[] serializeObject(Serializable obj){
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        ObjectOutput out = null;
        byte[] buff = null;
        try {
            out = new ObjectOutputStream(bos);   
            out.writeObject(obj);
            out.flush();
            buff = bos.toByteArray();
        } 
        catch(IOException e){
            e.printStackTrace();
        }
        finally {
            try {
                bos.close();
            } catch (IOException ex) {
                // ignore close exception
            }
        }

        return buff;
    }

    public static Serializable deserializeObject(byte[] buff){
        ByteArrayInputStream bis = new ByteArrayInputStream(buff);
        ObjectInput in = null;
        Object o = null;
        try {
            in = new ObjectInputStream(bis);
            o = in.readObject(); 
        } 
        catch(ClassNotFoundException e){
            e.printStackTrace();
        }
        catch(IOException e){
            e.printStackTrace();
        }
        finally {
            try {
                if (in != null) {
                    in.close();
                }
            } 
            catch (IOException ex) {
                // ignore close exception
            }
        }

        return (Serializable)o;
    }
}