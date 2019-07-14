package test;

import java.util.Random;

public class Utils {
    public static void sleepRand(long max_ms){
        Random rand = new Random();
        try{ Thread.sleep(Math.abs(rand.nextInt())%max_ms); }
        catch(InterruptedException e){ e.printStackTrace(); }
    }
}