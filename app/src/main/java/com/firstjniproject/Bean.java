package com.firstjniproject;

import android.util.Log;

/**
 * Created by Administrator
 * on 2020/8/25.
 */

class Bean {

    private String grailFriend;
    private String dog;

    public String getGrailFriend() {
        return grailFriend;
    }

    public void setGrailFriend(String grailFriend) {
        this.grailFriend = grailFriend;
    }

    public String getDog() {
        return dog;
    }

    public void setDog(String dog) {
        this.dog = dog;
        Log.e("zsq", dog);
    }

    public static void p(String s) {
        Log.e("zsq", s);
    }
}
