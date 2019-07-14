JAVA_PATH_INC=/usr/lib/jvm/java-1.8.0-openjdk-amd64
MPICH_INSTALL_DIR=/home/nikolay/workspace/mpich-install-java
MPICH_SOUCE_DIR=/home/nikolay/workspace/mpich
MPICH_BUILD_DIR=/home/nikolay/workspace/mpich_build_java
JAVA_BUILD_PATH=/home/nikolay/workspace/mpich_build/java
INC=-I$(JAVA_PATH_INC)/include/ -I$(JAVA_PATH_INC)/include/linux \
	-I$(MPICH_INSTALL_DIR)/include -I$(MPICH_SOUCE_DIR)/src/openpa/src	\
	-I$(MPICH_BUILD_DIR)/src/openpa/src 	\
	-I$(MPICH_SOUCE_DIR)/src/include
JAVA_SOURCES=	./src/mpi/*.java	\
				./src/test/*.java	\
				./src/mpi/exception/*.java \
				./src/test/types/*.java \
				./src/mpi/datatype/*.java	\
				./src/mpi/op/*.java

LIB=-L$(MPICH_INSTALL_DIR)/lib
C_SOURCES = 		./c/jni_mpi_types.c \
					./c/jni_onload.c \
					./c/jni_onunload.c \
					./c/jni_init_native.c	\
					./c/mpi_proc.c			\
					./c/jni_mpi_comm.c		\
					./c/jni_mpi_throw.c		\
					./c/mpi_send.c			\
					./c/mpi_recv.c			\
					./c/mpi_type.c			\
					./c/mpi_buff.c			\
					./c/mpi_isend.c			\
					./c/mpi_irecv.c			\
					./c/mpi_wait.c			\
					./c/jni_mpi_request.c	\
					./c/mpi_test.c			\
					./c/mpi_req_get_status.c\
					./c/mpi_req_free.c		\
					./c/mpi_probe.c			\
					./c/mpi_iprobe.c		\
					./c/mpi_cancel.c		\
					./c/mpi_send_init.c		\
					./c/mpi_recv_init.c		\
					./c/mpi_start.c			\
					./c/mpi_mprobe.c		\
					./c/mpi_improbe.c		\
					./c/mpi_mrecv.c			\
					./c/jni_mpi_message.c	\
					./c/mpi_imrecv.c		\
					./c/mpi_sendrecv.c		\
					./c/mpi_sendrecv_replace.c\
					./c/mpi_barrier.c		\
					./c/mpi_bcast.c			\
					./c/mpi_ibcast.c		\
					./c/mpi_scatter.c		\
					./c/mpi_iscatter.c		\
					./c/mpi_gather.c		\
					./c/mpi_igather.c		\
					./c/mpi_allgather.c		\
					./c/mpi_iallgather.c	\
					./c/mpi_alltoall.c		\
					./c/mpi_ialltoall.c		\
					./c/jni_mpi_op.c		\
					./c/mpi_reduce.c		\
					./c/mpi_op_create.c		\
					./c/mpi_ireduce.c		\
					./c/mpi_op_free.c		\
					./c/mpi_allreduce.c		\
					./c/mpi_iallreduce.c	\
					./c/mpi_scan.c			\
					./c/mpi_iscan.c			\
					./c/mpi_exscan.c		\
					./c/mpi_iexscan.c		\
					./c/mpi_comm_split.c	\
					./c/mpi_comm_free.c		\
					./c/mpi_comm_dup.c		\
					./c/mpi_comm_group.c	\
					./c/mpi_group_size.c	\
					./c/mpi_group_rank.c	\
					./c/mpi_group_free.c	\
					./c/mpi_comm_create_group.c\
					./c/mpi_group_incl.c	\
					./c/mpi_comm_compare.c	\
					./c/mpi_comm_create.c	\
					./c/mpi_group_compare.c	\
					./c/mpi_group_difference.c	\
					./c/mpi_group_excl.c	\
					./c/mpi_group_intersection.c	\
					./c/mpi_group_union.c		\
					./c/mpi_group_translate.c	\
					./c/mpi_intercomm_create.c	\
					./c/mpi_comm_remote_size.c	\
					./c/mpi_intercomm_merge.c	\
					./c/mpi_comm_remote_group.c	\
					./c/mpi_info_create.c		\
					./c/mpi_info_delete.c		\
					./c/mpi_info_dup.c			\
					./c/mpi_info_get.c			\
					./c/mpi_info_get_nkeys.c	\
					./c/mpi_info_set.c			\
					./c/mpi_info_get_nthkey.c	\
					./c/mpi_info_free.c			\
					./c/mpi_cart_create.c		\
					./c/mpi_abort.c				\
					./c/mpi_cart_coords.c		\
					./c/mpi_cart_rank.c			\
					./c/mpi_dims_create.c		\
					./c/mpi_graph_create.c		\
					./c/mpi_topo_test.c			\
					./c/mpi_cart_get.c			\
					./c/mpi_graphdims_get.c		\
					./c/mpi_graph_get.c			\
					./c/mpi_dist_graph_create.c	\
					./c/mpi_cart_shift.c		\
					./c/mpi_cart_sub.c			\
					./c/mpi_cartdims_get.c		\
					./c/mpi_graph_neighbors.c	\
					./c/mpi_graph_neighbors_count.c \
					./c/mpi_get_processor_name.c	\
					./c/mpi_time.c				\
					./c/mpi_initialized.c		\
					./c/mpi_comm_spawn.c 		\
					./c/mpi_comm_get_parent.c	\
					./c/mpi_open_port.c			\
					./c/mpi_close_port.c		\
					./c/mpi_publish_name.c		\
					./c/mpi_unpublish_name.c	\
					./c/mpi_lookup_name.c		\
					./c/mpi_comm_connect.c		\
					./c/mpi_comm_accept.c		\
					./c/mpi_comm_disconnect.c	\
					./c/mpi_win_create.c		\
					./c/mpi_win_fence.c			\
					./c/mpi_get.c				\
					./c/mpi_put.c				\
					./c/mpi_win_free.c			\
					./c/mpi_flush.c				\
					./c/mpi_win_get_name.c		\
					./c/mpi_win_get_info.c		\
					./c/mpi_win_get_group.c		\
					./c/mpi_win_lock.c			\
					./c/mpi_win_unlock.c		\
					./c/mpi_win_allocate.c		\
					./c/mpi_win_sync.c			\
					./c/mpi_win_shared_query.c	\
					./c/mpi_file_open.c			\
					./c/mpi_file_close.c		\
					./c/mpi_file_write.c		\
					./c/mpi_file_read.c			\
					./c/mpi_file_delete.c		\
					./c/mpi_file.c				\
					./c/mpi_file_set_view.c		\
					./c/mpi_type_create_subarray.c\
					./c/mpi_type_commit.c		\
					./c/mpi_type_free.c			\
					./c/jni_mpi_status.c		\
					./c/mpi_file_iwrite.c		\
					./c/mpi_file_iread.c

all:
	gcc -fPIC $(INC) -shared -o $(MPICH_INSTALL_DIR)/lib/libjavampi.so $(C_SOURCES) $(LIB) -lmpich -lmpi

java: javaclasses

java_clear:
	rm -f -r $(JAVA_BUILD_PATH)/*

javaclasses: java_clear
	javac -d $(JAVA_BUILD_PATH)  $(JAVA_SOURCES) -Xlint -h ./c


clean: 
	rm -f $(MPICH_INSTALL_DIR)/lib/libjavampi.so

	