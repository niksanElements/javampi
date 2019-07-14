package test;

import mpi.Info;
import mpi.MPI;

public class InfoCreate {
    public static void main(String[] args) {
     
        MPI.Init(args);
     
        Info info1 =  new Info();
        info1.create();
        info1.set("host", "myhost.myorg.org");
        info1.set("file", "runfile.txt");
        info1.set("soft", "2:1000:4,3:1000:7");
     
        Info infodup = info1.dup();
     
        int nkeysdup = infodup.nkeys();
        int nkeys = info1.nkeys();
        if (nkeys != nkeysdup) {
            System.out.printf( "Dup'ed info has a different number of keys; is %d should be %d\n", 
                nkeysdup, nkeys );
            System.out.flush();
        }
        for (int i=0; i<nkeys; i++) {
            /* MPI requires that the keys are in the same order after the dup */
            String key = info1.get_nthkey(i);
            String keydup = infodup.get_nthkey(i);
            if (key.compareTo(keydup) != 0) {
                System.out.printf( "keys do not match: %s should be %s\n", keydup, key);
                System.out.flush();
            }
     
            String value = info1.get(key);
            String valuedup = infodup.get(keydup);
            if (value.compareTo(valuedup) != 0) {
                System.out.printf( "Info values for key %s not the same after dup\n", key );
                System.out.flush();
            }
        }
     
        /* Change info and check that infodup does NOT have the new value (ensure that lazy dups are still duped) */
        info1.set("path", "/a:/b:/c/d");
        info1.set("soft","234243");
     
        String value = infodup.get("file");
        String value1 = info1.get("soft");

        System.out.println(value1);
        System.out.flush();
        System.out.println(value);
    
        info1.free();
        infodup.free();
    
        MPI.Finalize();
    }
}