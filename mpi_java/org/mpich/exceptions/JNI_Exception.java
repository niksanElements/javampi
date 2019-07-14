package org.mpich.exceptions;

public class JNI_Exception extends Exception{
    public static final long serialVersionUID = 1;
    public JNI_Exception(String txt){
        super(txt);
    }
}