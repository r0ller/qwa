package com.bitroller.qmlwasm1;

import android.app.Activity;
import android.content.Context;
import android.util.Log;
import android.webkit.JavascriptInterface;

import java.util.ArrayList;

public class jsi{
    Context mContext;

    /** Instantiate the interface and set the context */
    jsi(Context c) {
        mContext = c;
    }

    @JavascriptInterface
    public String postMessage(String text){
        class OneShotTask implements Runnable{
            private String mText;
            public OneShotTask(String str) { mText = str; }
            @Override
            public void run(){
                Log.i("hi",mText);
            }
        }
        Activity activity = (Activity) mContext;
        //As JS runs on UI thread, performing any operations on variables
        //coming from JS or calling any method on them results in exception: Error calling method on NPObject.
        //The only workaround seems to be to do such things on UIthread and store results in private attributes.
        activity.runOnUiThread(new OneShotTask(text));
        return "done";
    }

    @JavascriptInterface
    public void refresh(){
    }
}
