#include <jni.h>
#include <android/log.h>
#include "include/openssl/ssl.h"
#include "include/openssl/ec_key.h"
#include "include/openssl/rsa.h"



// includeが正常に行われているのかを確認
// defineで定義されたSHA_CBLOCKを参照できるかテスト 成功
extern "C"
JNIEXPORT int JNICALL
Java_com_example_boringssltest_MainActivity_cryptoTest(JNIEnv *env, jobject /*this*/) {
    //ライブラリを使う前に必ず呼ぶものらしい 初期化?
    //参考 https://lemniscus.hatenablog.com/entry/20090730/1248970407
    SSL_library_init();
    return SHA_CBLOCK;
}

// includeファイル内のヘッダファイルで宣言された関数が実行されるのかをテスト 成功
extern "C"
JNIEXPORT int JNICALL
Java_com_example_boringssltest_MainActivity_functionTest(JNIEnv *env, jobject /*this*/) {
    SSL_library_init();
    int nid = EC_curve_nist2nid("P-256");//415が出力される．
    EC_GROUP *ec = EC_GROUP_new_by_curve_name(NID_X9_62_prime256v1);
    return nid;
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_boringssltest_MainActivity_eckeyTest(JNIEnv *env, jobject /*this*/) {
    SSL_library_init();
    int nid = EC_curve_nist2nid("P-256");
    EC_KEY *testkey = EC_KEY_new_by_curve_name(nid);
    if(EC_KEY_generate_key(testkey)){
        //鍵生成が成功
        EC_KEY_free(testkey);
        __android_log_print(ANDROID_LOG_DEBUG, "cpp", "testgenkey");
        return 1;
    }else {
        __android_log_print(ANDROID_LOG_DEBUG, "cpp", "key generate error");
        return 0;
    }
}