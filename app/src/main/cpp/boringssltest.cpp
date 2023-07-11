#include <jni.h>
#include <android/log.h>
#include "include/openssl/ssl.h"


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


// includeが正常に行われているのかを確認
// defineで定義されたSHA_CBLOCKを参照できるかテスト 成功
extern "C"
JNIEXPORT int JNICALL
Java_com_example_boringssltest_MainActivity_cryptoTest(JNIEnv *env, jobject /*this*/) {
    return SHA_CBLOCK;
}

// includeファイル内のヘッダファイルで宣言された関数が実行されるのかをテスト 成功
extern "C"
JNIEXPORT int JNICALL
Java_com_example_boringssltest_MainActivity_functionTest(JNIEnv *env, jobject /*this*/) {
    int nid = EC_curve_nist2nid("P-256");//415が出力される．
    EC_GROUP *ec = EC_GROUP_new_by_curve_name(NID_X9_62_prime256v1);
    return nid;
}