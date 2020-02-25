#!/usr/bin/python3

import Command
import sys

if len(sys.argv) != 3:
    print("Add input file and version of the test!!")
    exit(-1)

cmd = "/home/nikolay/workspace/mpich_install/bin/mpiexec "+ \
    "-n 10 " +                \
    "java -classpath /home/nikolay/workspace/mpich_build/java "+\
    "-Djava.library.path=/home/nikolay/workspace/mpich-install-java/lib" + \
    " --illegal-access=permit " + "test.pathdag."+sys.argv[2]+" "+ sys.argv[1]
cmd_runner = Command.Command(cmd)

cmd_runner.run()

