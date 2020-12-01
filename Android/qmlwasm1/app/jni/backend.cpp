#include <jni.h>
#include <iostream>
#include "backend.h"
#include <android/log.h>

extern "C"{
    JNIEXPORT jbyteArray JNICALL
    Java_com_bitroller_qmlwasm1_MainActivity_callBackend
    (JNIEnv *env, jobject obj, jstring command)
    {
        const char *command_=env->GetStringUTFChars(command, JNI_FALSE);
        __android_log_print(ANDROID_LOG_INFO, "qwa", "command: %s", command_);
//        JavaVM* javaVM=NULL;
//        env->GetJavaVM(&javaVM);
//        jobject activity = env->NewGlobalRef(obj);

        const char *response=execute(command_);
        env->ReleaseStringUTFChars(command, command_);
        jbyteArray bytes = env->NewByteArray(strlen(response));
        env->SetByteArrayRegion(bytes,0,strlen(response),(jbyte*)response);
        delete[] response;
        return bytes;
    }

}
