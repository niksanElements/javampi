package test.types;

import java.io.Serializable;

public class Person{
    
    private int age;
    private int[] name;
    private long[] some;
    private Here here;
    private Here[] h;

    public Here getHere() {
		return here;
	}

	public void setHere(Here here) {
		this.here = here;
	}

	public Person(){

    }

    public Person(int[] name,int age){
        this.name = name;
        this.age = age;
    }
    /**
     * @return the age
     */
    public int getAge() {
        return age;
    }

    /**
     * @param age the age to set
     */
    public void setAge(int age) {
        this.age = age;
    }

    /**
     * @return the name
     */
    public int[] getName() {
        return name;
    }

    /**
     * @param name the name to set
     */
    public void setName(int[] name) {
        this.name = name;
    }

    /**
     * @return the some
     */
    public long[] getSome() {
        return some;
    }

    /**
     * @param some the some to set
     */
    public void setSome(long[] some) {
        this.some = some;
    }

	public Here[] getH() {
		return h;
	}

	public void setH(Object[] h) {
		this.h = new Here[h.length];
		for(int i = 0;i < this.h.length;i++) {
			this.h[i] = (Here)h[i];
		}
	}

}