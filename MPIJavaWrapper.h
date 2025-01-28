#include <jni.h>
/* Header for class graphics_scenery_natives_MPIJavaWrapper */

#ifndef _Included_MPIJavaWrapper
#define _Included_MPIJavaWrapper
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     graphics_scenery_natives_MPIJavaWrapper
 * Method:    init
 * Signature: ([Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_graphics_scenery_natives_graphics_scenery_natives_MPIJavaWrapper_init
  (JNIEnv *, jclass, jobjectArray);

/*
 * Class:     graphics_scenery_natives_MPIJavaWrapper
 * Method:    finalizeMPI
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_graphics_scenery_natives_graphics_scenery_natives_MPIJavaWrapper_finalizeMPI
  (JNIEnv *, jclass);

/*
 * Class:     graphics_scenery_natives_MPIJavaWrapper
 * Method:    commRank
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_graphics_scenery_natives_graphics_scenery_natives_MPIJavaWrapper_commRank
  (JNIEnv *, jclass);

/*
 * Class:     graphics_scenery_natives_MPIJavaWrapper
 * Method:    commSize
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_graphics_scenery_natives_graphics_scenery_natives_MPIJavaWrapper_commSize
  (JNIEnv *, jclass);

/*
 * Class:     graphics_scenery_natives_MPIJavaWrapper
 * Method:    send
 * Signature: ([BII)V
 */
JNIEXPORT void JNICALL Java_graphics_scenery_natives_graphics_scenery_natives_MPIJavaWrapper_send
  (JNIEnv *, jclass, jbyteArray, jint, jint);

/*
 * Class:     graphics_scenery_natives_MPIJavaWrapper
 * Method:    recv
 * Signature: (II)[B
 */
JNIEXPORT jbyteArray JNICALL Java_graphics_scenery_natives_MPIJavaWrapper_recv
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     graphics_scenery_natives_MPIJavaWrapper
 * Method:    bcast
 * Signature: ([BI)V
 */
JNIEXPORT void JNICALL Java_graphics_scenery_natives_MPIJavaWrapper_bcast
  (JNIEnv *, jclass, jbyteArray, jint);

#ifdef __cplusplus
}
#endif
#endif
