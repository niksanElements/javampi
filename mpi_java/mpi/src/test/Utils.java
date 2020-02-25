package test;

import java.util.Random;

public class Utils {
    
    public static void sleepRand(long max_ms){
        Random rand = new Random();
        try{ Thread.sleep(Math.abs(rand.nextInt())%max_ms); }
        catch(InterruptedException e){ e.printStackTrace(); }
    }

    public static void check(int rank,boolean flag, String test){
        if(!flag){
            System.out.printf("%s: ERROR! Rank: %d\n",test,rank);
        }
        else{
            System.out.printf("%s: PASS! Rank: %d\n",test,rank);
        }
    }
}