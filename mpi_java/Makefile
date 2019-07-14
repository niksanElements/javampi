JAVA_PATH_INC=/usr/lib/jvm/java-1.8.0-openjdk-amd64
MPICH_INSTALL_DIR=/home/nikolay/workspace/mpich_install
MPICH_SOUCE_DIR=/home/nikolay/workspace/mpich
MPICH_BUILD_DIR=/home/nikolay/workspace/mpich_build
INC=-I$(JAVA_PATH_INC)/include/ -I$(JAVA_PATH_INC)/include/linux \
	-I$(MPICH_INSTALL_DIR)/include -I$(MPICH_SOUCE_DIR)/src/openpa/src	\
	-I$(MPICH_BUILD_DIR)/src/openpa/src 
LIB=-L$(MPICH_INSTALL_DIR)/lib
C_SOURCES = ../mpi_c/jni_mpi_init.c		\
			../mpi_c/jni_mpi_rank.c		\
			../mpi_c/jni_mpi_finalize.c	\
			../mpi_c/jni_mpi_send.c		\
			../mpi_c/jni_mpi_recv.c		\
			../mpi_c/jni_onload.c		\
			../mpi_c/utils.c			\
			../mpi_c/jni_mpi_get_count.c\
			../mpi_c/jni_mpi_buffer.c	\
			../mpi_c/jni_mpi_wait.c		\
			../mpi_c/jni_mpi_exception.c\
			../mpi_c/jni_mpi_request.c	\
			../mpi_c/jni_mpi_probe.c	\
			../mpi_c/jni_mpi_cancel.c	\
			../mpi_c/jni_mpi_persistent_comm.c \
			../mpi_c/jni_mpi_sendrecv.c	\
			../mpi_c/jni_mpi_barrier.c		\
			../mpi_c/jni_mpi_bcast.c		\
			../mpi_c/jni_mpi_scatgath.c		\
			../mpi_c/jni_mpi_alltoall.c		\
			../mpi_c/jni_mpi_reduce.c		\
			../mpi_c/jni_mpi_scan.c			\
			../mpi_c/jni_mpi_group.c		\
			../mpi_c/jni_mpi_comm.c			\
			../mpi_c/jni_mpi_intercomm.c	\
			../mpi_c/jni_mpi_cart.c			\
			../mpi_c/jni_mpi_graph.c		\
			../mpi_c/jni_mpi_envmanagment.c	\
			../mpi_c/jni_mpi_info.c			\
			../mpi_c/jni_mpi_proc.c			\
			../mpi_c/jni_mpi_enscomm.c		\
			../mpi_c/jni_mpi_win.c			\
			../mpi_c/jni_mpi_mem.c			\
			../mpi_c/file.c					\
			../mpi_c/jni_mpi_fileconf.c		\
			../mpi_c/jni_mpi_fileaccess.c	

java_clear:
	rm -f ./org/mpich/*.class

javaclasses: java_clear
	javac  org/mpich/*.java -Xlint -h ../mpi_c/
	javac  org/mpich/exceptions/*.java -Xlint -h ../mpi_c/ 

MpiJava:
	gcc -fPIC $(INC) -shared -o $(MPICH_INSTALL_DIR)/lib/libMpiJava.so $(C_SOURCES) $(LIB) -lmpich -lmpi
MpiJavaExceptions:
	python3 generate_exceptions.py $(MPICH_SOUCE_DIR)/src/include/mpi.h.in ./org/mpich/exceptions ../mpi_c/jni_mpi_exception_classes.h

run:
	# export LD_LIBRARY_PATH=$(MPICH_INSTALL_DIR)/lib:.
	$(MPICH_INSTALL_DIR)/bin/mpiexec -n 10 java org.mpich.Main

clean: java_clear
	rm -f libMpiJava.so

	