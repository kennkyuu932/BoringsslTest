#include <jni.h>
#include <android/log.h>
#include "include/openssl/sha.h"

// Write C++ code here.
//
// Do not forget to dynamically load the C++ library into your application.
//
// For instance,
//
// In MainActivity.java:
//    static {
//       System.loadLibrary("boringssltest");
//    }
//
// Or, in MainActivity.kt:
//    companion object {
//      init {
//         System.loadLibrary("boringssltest")
//      }
//    }
extern "C"
JNIEXPORT int JNICALL
Java_com_example_boringssltest_MainActivity_cryptoTest(JNIEnv *env, jobject /*this*/) {
    return SHA_CBLOCK;
}