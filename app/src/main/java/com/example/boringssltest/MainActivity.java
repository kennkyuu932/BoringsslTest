package com.example.boringssltest;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("crypto");
        System.loadLibrary("decrepit");
        System.loadLibrary("ssl");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
}