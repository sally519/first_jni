package com.firstjniproject;

import android.os.Bundle;
import android.os.Looper;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("main");
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI( ));
        test(new String[]{"a"}, new int[]{5, 1, 9, 2, 1, 6, 5, 2, 6});

        Bean bean = new Bean( );
        bean.setGrailFriend("关润");
        passObject(bean, "zsq");
        //1.动态注册
        dynamicJavaTest();
        //2.native线程
        threadTest();
        main();
    }

    public void updateUI(){
        if(Looper.myLooper()==Looper.getMainLooper()){
            Toast.makeText(this, "更新UI", Toast.LENGTH_SHORT).show();
        }else {
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Toast.makeText(MainActivity.this, "更新UI", Toast.LENGTH_SHORT).show();
                }
            });
        }
    }

    public native String stringFromJNI();

    public native void test(String[] s, int[] i);

    public native void passObject(Bean bean, String s);

    public native void dynamicJavaTest();

    public native void threadTest();

    public native int main();
}
