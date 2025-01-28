#include <jni.h>
#include <mpi.h>
#include <stdlib.h>
#include <string.h>
#include "MPIJavaWrapper.h"

JNIEXPORT void JNICALL Java_graphics_scenery_natives_MPIJavaWrapper_init
  (JNIEnv *env, jclass clazz, jobjectArray jargs)
{
    int argCount = (*env)->GetArrayLength(env, jargs);
    char **argv = (char**) malloc(sizeof(char*) * argCount);

    for (int i = 0; i < argCount; i++) {
        jstring js = (jstring)(*env)->GetObjectArrayElement(env, jargs, i);
        const char* temp = (*env)->GetStringUTFChars(env, js, 0);
        argv[i] = strdup(temp);
        (*env)->ReleaseStringUTFChars(env, js, temp);
    }

    MPI_Init(&argCount, &argv);

    for (int i = 0; i < argCount; i++) {
        free(argv[i]);
    }
    free(argv);
}

JNIEXPORT void JNICALL Java_graphics_scenery_natives_MPIJavaWrapper_finalizeMPI
  (JNIEnv *env, jclass clazz)
{
    MPI_Finalize();
}

JNIEXPORT jint JNICALL Java_graphics_scenery_natives_MPIJavaWrapper_commRank
  (JNIEnv *env, jclass clazz)
{
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    return (jint) rank;
}

JNIEXPORT jint JNICALL Java_graphics_scenery_natives_MPIJavaWrapper_commSize
  (JNIEnv *env, jclass clazz)
{
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    return (jint) size;
}

JNIEXPORT void JNICALL Java_graphics_scenery_natives_MPIJavaWrapper_send
  (JNIEnv *env, jclass clazz, jbyteArray jdata, jint dest, jint tag)
{
    jbyte *data = (*env)->GetByteArrayElements(env, jdata, NULL);
    jsize length = (*env)->GetArrayLength(env, jdata);

    MPI_Send(data, length, MPI_BYTE, dest, tag, MPI_COMM_WORLD);

    (*env)->ReleaseByteArrayElements(env, jdata, data, JNI_ABORT);
}

JNIEXPORT jbyteArray JNICALL Java_graphics_scenery_natives_MPIJavaWrapper_recv
  (JNIEnv *env, jclass clazz, jint source, jint tag)
{
    MPI_Status status;
    int count;

    MPI_Probe(source, tag, MPI_COMM_WORLD, &status);
    MPI_Get_count(&status, MPI_BYTE, &count);

    char* buffer = (char*) malloc(count * sizeof(char));
    MPI_Recv(buffer, count, MPI_BYTE, source, tag, MPI_COMM_WORLD, &status);

    jbyteArray jdata = (*env)->NewByteArray(env, count);
    (*env)->SetByteArrayRegion(env, jdata, 0, count, (jbyte*) buffer);

    free(buffer);
    return jdata;
}

JNIEXPORT void JNICALL Java_graphics_scenery_natives_MPIJavaWrapper_bcast
  (JNIEnv *env, jclass clazz, jbyteArray jdata, jint root)
{
    jbyte *data = (*env)->GetByteArrayElements(env, jdata, NULL);
    jsize length = (*env)->GetArrayLength(env, jdata);

    // Initialize MPI if it is not already initialized
    int mpiInitialized;
    MPI_Initialized(&mpiInitialized);
    if (!mpiInitialized) {

        printf("MPI not initialized, initializing now");

        MPI_Init(NULL, NULL);
    }

    MPI_Bcast(data, length, MPI_BYTE, root, MPI_COMM_WORLD);

    // Copy the (potentially modified) data back to Java array
    (*env)->ReleaseByteArrayElements(env, jdata, data, 0);
}

