package com.bitroller.qmlwasm1;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.res.AssetManager;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.webkit.ConsoleMessage;
import android.webkit.WebChromeClient;
import android.webkit.WebMessage;
import android.webkit.WebMessagePort;
import android.webkit.WebResourceRequest;
import android.webkit.WebResourceResponse;
import android.webkit.WebView;
import android.webkit.WebViewClient;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.UnsupportedEncodingException;

public class MainActivity extends AppCompatActivity {
    private native byte[] callBackend(String command);
    private WebView mWebView;
    private boolean qmlInitDone=false;
    private static Context context;
    private WebMessagePort port;

    static {
        try {//Load native libraries ONLY that act as Java-Native Interface.
            //Native libraries accessed by jni libs shall not be loaded.
            //Native libraries must have SONAME, check:
            //readelf --dynamic libWithSoName.so | grep SONAME
            //If not, crosscompile them on the native platform with: -Wl,-soname,libWithSoName.so
            //Native libraries must not have path in their names, only filename, check:
            //readelf --dynamic libSample.so | grep NEEDED
            //Native libraries must not have relocated text, check:
            //readelf --dynamic libTextRel.so | grep TEXTREL
            //Native libraries must have (non zero) section headers, check:
            //readelf --header libBroken.so | grep 'section headers'
            System.loadLibrary("backend");
        }
        catch (java.lang.UnsatisfiedLinkError e){
            e.getMessage();
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        context=this;
        //There are two ways to add a webview: in onCreate via setContentView or later by findViewById
        setContentView(R.layout.activity_main);
        mWebView = (WebView) findViewById(R.id.webview);
        mWebView.getSettings().setJavaScriptEnabled(true);
        mWebView.setWebChromeClient(new WebChromeClient(){
            public boolean onConsoleMessage(ConsoleMessage cm) {
                if(cm.message().contentEquals("qml: qmlwasm1")&&qmlInitDone==false){
                    qmlInitDone = true;
                    final WebMessagePort[] channel=mWebView.createWebMessageChannel();

                    port=channel[0];
                    port.setWebMessageCallback(new WebMessagePort.WebMessageCallback() {
                        @Override
                        public void onMessage(WebMessagePort port, WebMessage message) {
                            byte[] responseBytes=callBackend(message.getData());
                            try{
                                String response = new String(responseBytes, "UTF-8");
                                port.postMessage(new WebMessage(response));
                            }
                            catch (UnsupportedEncodingException e) {
                                Log.e("utf8", "conversion", e);
                            }
                        }
                    });

                    mWebView.postWebMessage(new WebMessage("test", new WebMessagePort[]{channel[1]}), Uri.EMPTY);
                }
                Log.i("MyApplication", cm.message() + " -- From line "
                        + cm.lineNumber() + " of "
                        + cm.sourceId() );
                return true;
            }
        });
        mWebView.setWebViewClient(new WebViewClient(){
            @Override
            public void onPageFinished(WebView view, String url) {
            }
            @Override
            public WebResourceResponse shouldInterceptRequest(WebView view,WebResourceRequest request) {
                String path = request.getUrl().getLastPathSegment();

                try {
                    String mime;
                    AssetManager assetManager = getAssets();

                    if (path.endsWith(".html")) mime = "text/html";
                    else if (path.endsWith(".wasm")) mime = "application/wasm";
                    else if (path.endsWith(".js")) mime = "text/javascript";
                    else if (path.endsWith(".svg")) mime = "image/svg+xml";
                    else
                        return super.shouldInterceptRequest(view, request);

                    InputStream input = assetManager.open("www/" + path);
                    return new WebResourceResponse(mime, "utf-8", input);
                } catch (IOException e) {
                    e.printStackTrace();
                    ByteArrayInputStream result = new ByteArrayInputStream
                            (("X:" + path + " E:" + e.toString()).getBytes());
                    return new WebResourceResponse("text/plain", "utf-8", result);
                }
            }
        });
        //mWebView.loadData("<html><body>Hello World</body></html>", "text/html; charset=UTF-8", "UTF-8");
        //mWebView.loadUrl("file:///android_asset/qmlwasm1.html");
        mWebView.loadUrl("https://appassets.androidplatform.net/qmlwasm1.html");
    }

    @Override
    public void onStart(){
        super.onStart();
    }
}
