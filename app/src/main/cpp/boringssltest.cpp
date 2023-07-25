#include <jni.h>
#include <android/log.h>
#include "include/openssl/ssl.h"
#include "include/openssl/ec_key.h"
#include "include/openssl/rsa.h"
#include "include/openssl/rand.h"
#include "include/openssl/bn.h"
#include "include/openssl/evp.h"



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
        const EC_GROUP *group = EC_KEY_get0_group(testkey);
        EC_POINT *pub_key_point = EC_POINT_new(group);
        //公開鍵の取得
        if (!EC_POINT_copy(pub_key_point, EC_KEY_get0_public_key(testkey))){
            //失敗したら0を返す
            EC_KEY_free(testkey);
            return 0;
        }
        //メッセージ
        const unsigned char *message = (const unsigned char *) "Test Message!";
        size_t message_len= strlen((const char *)message);
        //暗号化
        EVP_PKEY *pub_key = EVP_PKEY_new();
        if(pub_key==NULL) return 0;
        //EVP_PKEY_assign_EC_KEY(pub_key,testkey);
        if(EVP_PKEY_set1_EC_KEY(pub_key,testkey)!=1) return 0;
        EVP_PKEY_CTX *ctx= EVP_PKEY_CTX_new(pub_key,NULL);
        if(ctx==NULL) return 0;
        //__android_log_print(ANDROID_LOG_DEBUG, "cpp", "ctx init %d",EVP_PKEY_encrypt_init(ctx));
        if(EVP_PKEY_encrypt_init(ctx)<=0) {
            return 0;
        }

        size_t encrypted_len;
        if(EVP_PKEY_encrypt(ctx,NULL,&encrypted_len,message,message_len)<=0) return 0;
        unsigned char *encrypted_message = static_cast<unsigned char *>(OPENSSL_malloc(encrypted_len));
        if (encrypted_message==NULL) return 0;
        //暗号化処理
        if(EVP_PKEY_encrypt(ctx,encrypted_message,&encrypted_len,message,message_len)<=0) return 0;
        EVP_PKEY_CTX_free(ctx);
        //終了　メモリ開放
        EC_KEY_free(testkey);
        __android_log_print(ANDROID_LOG_DEBUG, "cpp", "testgenkey");
        return 1;
    }else {
        __android_log_print(ANDROID_LOG_DEBUG, "cpp", "key generate error");
        return 0;
    }
}



extern "C"
JNIEXPORT jint JNICALL
Java_com_example_boringssltest_MainActivity_rsakeyTest(JNIEnv *env, jobject /*this*/) {
    RSA *rsa_key=RSA_new();
    if (rsa_key==NULL) return 0;
    if (RSA_generate_key_ex(rsa_key,1024,NULL,NULL)!=1){
        return 0;
    }
    RSA_free(rsa_key);
    return 1;
}