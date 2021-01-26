package com.firstjniproject;

import android.content.Context;
import android.util.Log;

import org.junit.Test;
import org.junit.runner.RunWith;

import androidx.test.ext.junit.runners.AndroidJUnit4;
import androidx.test.platform.app.InstrumentationRegistry;

import static org.junit.Assert.assertEquals;

/**
 * Instrumented test, which will execute on an Android device.
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
@RunWith(AndroidJUnit4.class)
public class ExampleInstrumentedTest {

    static {
        System.loadLibrary("native-lib");
    }

    @Test
    public void main() {
        // Context of the app under test.
        Context appContext = InstrumentationRegistry.getInstrumentation( ).getTargetContext( );
        assertEquals("com.firstjniproject", appContext.getPackageName( ));
        System.out.println(stringFromJNI( ));
//        Log.e("zsq", );
    }

    public native String stringFromJNI();
}