package com.example.boringssltest;

import static android.content.ContentValues.TAG;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;

public class MainActivity extends AppCompatActivity {

    //使用するライブラリファイルの読み込み
    static {
        System.loadLibrary("boringssltest");
        System.loadLibrary("crypto");
        System.loadLibrary("decrepit");
        System.loadLibrary("ssl");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Log.d(TAG, "cryptoTest: "+cryptoTest());
        Log.d(TAG, "functionTest: "+functionTest());
        Log.d(TAG, "eckeyTest: "+eckeyTest());
    }

    //sha.hのdefine定義されたSHA_CBLOCK 64を表示するテスト
    public native int cryptoTest();

    //ec.h,nid.hの関数を呼び出すテスト
    public native int functionTest();

    //ec_key.hを使って鍵生成を行うテスト
    public native int eckeyTest();
}