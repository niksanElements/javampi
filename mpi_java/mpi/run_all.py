#!/usr/bin/python3

import sys
import glob
import Command

if len(sys.argv) != 2:
    print("run_all.py /path/to/java/classes")
    exit(-1)

root_package = "test"

files = [f for f in glob.glob(sys.argv[1] + "**/*")]
java_classes = []

for file in files:
    s = file.find("test")
    f = file[s:]
    f = f.replace("/",".")
    f = f[:-6]
    if f != 'test':
        if f != 'test.p':
            if not '' is f:
                if not "$" in f:
                    if not "types" in f:
                        if not "Utils" in f:
                            java_classes.append(f)

print(java_classes)
# print(files)

for _class in java_classes:
    print("test {} begines".format(_class))
    cmd = "/home/nikolay/workspace/mpich_install/bin/mpiexec "+ \
                "-n 10 " +                \
                "java -classpath /home/nikolay/workspace/mpich_build/java -Djava.library.path=/home/nikolay/workspace/mpich-install-java/lib" + \
                " --illegal-access=permit " + _class
    cmd_runner = Command.Command(cmd)

    cmd_runner.run()
    print("test {} ends".format(_class))

