package org.mpich.exceptions;

public class JNI_Null_exception extends Exception{
    public static final long serialVersionUID = 1;
    public JNI_Null_exception(String txt){
        super(txt);
    }
}