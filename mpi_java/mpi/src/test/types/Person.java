package test.types;

import java.io.Serializable;
// execute point 
public class Person{
    private int age;
    private int[] name;
    private long[] some;
    private Here here;
    private Here[] h;
    public Here getHere() {return here;}
	public void setHere(Here here) {this.here = here;}
	public Person(){}
    public Person(int[] name,int age){this.name = name;this.age = age;}
    public int getAge() {return age;}
    public void setAge(int age) {this.age = age;}
    public int[] getName() {return name;}
    public void setName(int[] name) {this.name = name;}
    public long[] getSome() {return some;}
    public void setSome(long[] some) {this.some = some;}
	public Here[] getH() {return h;}
	public void setH(Object[] h) {
		this.h = new Here[h.length];
		for(int i = 0;i < this.h.length;i++) {
			this.h[i] = (Here)h[i];
		}
	}
}