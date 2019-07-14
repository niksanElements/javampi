#include "mpi_Intracomm.h"
#include "jni_mpi.h"


/*
 * Class:     mpi_Intracomm
 * Method:    _dist_graph_create
 * Signature: (JII[II[II[II[IJZ)J
 */
JNIEXPORT jlong JNICALL 
Java_mpi_Intracomm__1dist_1graph_1create(
    JNIEnv *env, jclass class, jlong comm, 
    jint offsetsources, jint n, jintArray sources, jint offsetdegrees, jintArray degrees, 
    jint offsetdestinations, jintArray destinations, jint offsetweights, jintArray weights, 
    jlong info, jboolean reordered)
{
    long new_comm = 0;
    int size;
    jint *_sources,*_degrees,*_destinations,*_weights;
    int dest_weight_size;
    int result;

#ifdef JNI_REGION_COPY
    // if the buffer is DirectBuffer
    // allocate _buff
    size = sizeof(jint);

    _sources = malloc(size*n);
    if(_sources == NULL){
        jniOutOfMemoryException(env,"malloc");
        return -1;
    }
    _degrees = malloc(size*n);
    if(_degrees == NULL){
        free(_sources);
        jniOutOfMemoryException(env,"malloc");
        return -1;
    }

    getIntRegion(env,sources,offsetsources,n,(void**)&_sources,0);
    getIntRegion(env,degrees,offsetdegrees,n,(void**)&_degrees,0);
#elif defined JNI_CRITICAL_SECTION
    getCriticalSection(env,sources,offsetsources,n,(void**)&_sources,sizeof(jint),0);
    getCriticalSection(env,degrees,offsetdegrees,n,(void**)&_degrees,sizeof(jint),0);
#endif

    // calculateing the size of the edges
    dest_weight_size = _degrees[0];
    for(int i = 1;i < n;i++){
        dest_weight_size += _degrees[i];
    }

#ifdef JNI_REGION_COPY
    // if the buffer is DirectBuffer
    // allocate _buff
    size = sizeof(jint);

    _destinations = malloc(size*dest_weight_size);
    if(_destinations == NULL){
        free(_sources);
        free(_degrees);
        jniOutOfMemoryException(env,"malloc");
        return -1;
    }
    _weights = malloc(size*dest_weight_size);
    if(_weights == NULL){
        free(_sources);
        free(_degrees);
        free(_destinations);
        jniOutOfMemoryException(env,"malloc");
        return -1;
    }

    getIntRegion(env,destinations,offsetdestinations,dest_weight_size,(void**)&_destinations,0);
    getIntRegion(env,weights,offsetweights,dest_weight_size,(void**)&_weights,0);
#elif defined JNI_CRITICAL_SECTION
    getCriticalSection(env,destinations,offsetdestinations,dest_weight_size,
        (void**)&_destinations,sizeof(jint),0);
    getCriticalSection(env,weights,offsetweights,dest_weight_size,
        (void**)&_weights,sizeof(jint),0);
#endif
    result = MPI_Dist_graph_create((MPI_Comm)comm,n,_sources,_degrees,_destinations,_weights,
        (MPI_Info)info,(int)reordered,(MPI_Comm*)&new_comm);
    if(result != MPI_SUCCESS){
        mpiErr(env,result,"MPI_graph_create");
    }

#ifdef JNI_REGION_COPY
    free(_sources);
    free(_degrees);
    free(_destinations)
    free(_weights);
#elif defined JNI_CRITICAL_SECTION
    relCriticalSection(env,sources,offsetsources,n,
        (void**)&_sources,sizeof(jint),JNI_ABORT);
    relCriticalSection(env,degrees,offsetdegrees,n,
        (void**)&_degrees,sizeof(jint),JNI_ABORT);
    relCriticalSection(env,destinations,offsetdestinations,n,
        (void**)&_destinations,sizeof(jint),JNI_ABORT);
    relCriticalSection(env,weights,offsetweights,n,
        (void**)&_weights,sizeof(jint),JNI_ABORT);
#endif
    return new_comm;
}
