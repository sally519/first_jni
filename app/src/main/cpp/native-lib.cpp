#include <jni.h>
#include <string>
#include <android/log.h>
#include <pthread.h>

//__VA_ARGS__代表...这个可变参数
#define LOG(...) __android_log_print(ANDROID_LOG_ERROR,"zsq",__VA_ARGS__);

using namespace std;
extern "C" JNIEXPORT jstring JNICALL
Java_com_firstjniproject_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

void dynamicJava(){
    __android_log_print(ANDROID_LOG_ERROR,"JNI","dynamicJava");
}
//动态注册java native方法
static const JNINativeMethod method[]={
        {"dynamicJavaTest","()V",(void*)dynamicJava},
};
static const char *javaClass="com/firstjniproject/MainActivity";
JavaVM *_vm;
int JNI_OnLoad(JavaVM *vm,void *r){
    _vm=vm;
    //获得JNIEvn
    JNIEnv *env=nullptr;
    int s=vm->GetEnv((void **)&env, JNI_VERSION_1_6);
    if(s!=JNI_OK){
        return -1;
    }
    //获得class对象
    jclass cls = env->FindClass(javaClass);
    //注册
    env->RegisterNatives(cls,method,sizeof(method)/sizeof(JNINativeMethod));
    __android_log_print(ANDROID_LOG_ERROR,"JNI","JNI_OnLoad");
    return JNI_VERSION_1_6;
}

extern "C"
__attribute__ ((visibility ("default"))) jstring JNICALL
Java_com_firstjniproject_ExampleUnitTest_stringFromJNI(JNIEnv *env, jobject thiz) {
    // TODO: implement stringFromJNI()
    string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_firstjniproject_MainActivity_test
        (JNIEnv *env, jobject thiz, jobjectArray s, jintArray i) {
    jint *ji = env->GetIntArrayElements(i, NULL);
    int length = env->GetArrayLength(i);
    for (int k = 0; k < length; k++) {
        LOG("这是java传过来的数据%d", *(ji + k));
    }
    env->ReleaseIntArrayElements(i, ji, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_firstjniproject_MainActivity_passObject(JNIEnv *env, jobject thiz, jobject bean,
                                                 jstring s) {
    //通过反射调用java对象
    //1.获取java对应的class
    jclass beanCls = env->GetObjectClass(bean);
    //2.找到要调用的方法
    jmethodID idG = env->GetMethodID(beanCls, "getGrailFriend", "()Ljava/lang/String;");
    jmethodID idS = env->GetMethodID(beanCls, "setDog", "(Ljava/lang/String;)V");
    jmethodID idP = env->GetStaticMethodID(beanCls, "p", "(Ljava/lang/String;)V");
    //3.调用此方法
    jobject gf = env->CallObjectMethod(bean, idG);
//    LOG("这是第一个方法%s获取", static_cast<jstring>(gf));
    jstring ss = env->NewStringUTF("这是C++取的名字，火烧饼");
    env->CallVoidMethod(bean, idS, ss);
    jstring js = env->NewStringUTF("这是C++里创建的字符出串");
    env->CallStaticVoidMethod(beanCls, idP, js);

    //释放局部引用
    env->DeleteLocalRef(ss);
    env->DeleteLocalRef(js);
    //    env->DeleteLocalRef(gf);

    //通过反射创建类
    //1.获取类
    jclass cclass = env->FindClass("com/firstjniproject/Bean");
    //2.获取类的构造方法
    jmethodID gid = env->GetMethodID(cclass, "<init>", "()V");
    //3.调用此方法获得object
    jobject bean2 = env->NewObject(cclass, gid);
    //将局部引用变为全局引用，防止悬空指针
//    bean2 = env->NewGlobalRef(bean2);
    //释放局部引用
    env->DeleteLocalRef(bean2);
}

struct Context{
    jobject instance;
};

void* threadTask(void* args){
    //native线程 附加到Java虚拟机
    JNIEnv *evn;
    jint i=_vm->AttachCurrentThread(&evn,0);
    if(i!=JNI_OK){
        return 0;
    }

    Context *context= static_cast<Context *>(args);
    //获得MainActivity的class对象
    jclass cls=evn->GetObjectClass(context->instance);
    //反射获得方法
    jmethodID  updateUI=evn->GetMethodID(cls,"updateUI","()V");
    evn->CallVoidMethod(context->instance,updateUI);
    delete(context);
    context=0;

//    evn->DeleteGlobalRef(context->instance);
//    //分离
//    _vm->DetachCurrentThread();
    return 0;
    //1.下载成功
    //2.下载失败
}

extern "C"
JNIEXPORT void JNICALL
Java_com_firstjniproject_MainActivity_threadTest(JNIEnv *env, jobject thiz) {
    // TODO: implement threadTest()
    pthread_t pid;
    //启动线程，下载视频
    Context *context=new Context;
    context->instance=env->NewGlobalRef(thiz);
    pthread_create(&pid,0,threadTask,context);
}
extern "C"{
    extern int main();
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_firstjniproject_MainActivity_main(JNIEnv *env, jobject thiz) {
    __android_log_print(ANDROID_LOG_ERROR,"JNI","JNI_OnLoad%d",main());
    return main();
}