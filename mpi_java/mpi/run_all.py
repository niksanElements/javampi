#!/usr/bin/python

import sys
import glob
import subprocess
import threading

""" Run system commands with timeout
"""
class Command(object):
    def __init__(self, cmd):
        self.cmd = cmd
        self.process = None
        self.out = None

    def run_command(self, capture = False):
        if not capture:
            self.process = subprocess.Popen(self.cmd,shell=True)
            self.process.communicate()
            return
        # capturing the outputs of shell commands
        self.process = subprocess.Popen(self.cmd,shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE,stdin=subprocess.PIPE)
        out,err = self.process.communicate()
        if len(out) > 0:
            self.out = out.splitlines()
        else:
            self.out = None

    # set default timeout to 2 minutes
    def run(self, capture = False, timeout = 120):
        thread = threading.Thread(target=self.run_command, args=(capture,))
        thread.start()
        thread.join(timeout)
        if thread.is_alive():
            print('Command timeout, kill it: ' + self.cmd)
            self.process.terminate()
            thread.join()
        return self.out

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
    if not "$" in f:
        if not "types" in f:
            if not "Utils":
                java_classes.append(f)

print(java_classes)

for _class in java_classes:
    cmd = "/home/nikolay/workspace/mpich_install/bin/mpiexec "+ \
                "-n 10 " +                \
                "java -Djava.library.path=/home/nikolay/workspace/mpich-install-java/lib" + \
                " --illegal-access=permit " + _class
    cmd_runner = Command(cmd)

    cmd_runner.run()

