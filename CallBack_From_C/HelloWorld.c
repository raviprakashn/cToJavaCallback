#include <jni.h>
#include <stdio.h>
#include "HelloWorld.h"   
#include <pthread.h>
#include <unistd.h>


void callJavaMethod();
void thread_fun(void);
JNIEnv *gEnv;
jobject gObject;
static JavaVM *cachedJVM;


static int attach_jvm(JNIEnv **gEnv)
{
printf("attach java method\n");
    if ((*cachedJVM)->GetEnv(cachedJVM, (void **)gEnv,
                               JNI_VERSION_1_8) < 0)
    {
	printf("attach java\n");
        if ((*cachedJVM)->AttachCurrentThread(cachedJVM, (void **)gEnv, NULL) < 0)
        {
	printf("attach java2 \n");
            gEnv = NULL;
            return 0;
        }
	printf("attach java2 true\n");
        return 1;
    }
    	printf("attach java not exits\n");
    return 0;
}


JNIEXPORT void JNICALL   Java_HelloWorld_print(JNIEnv *env, jobject obj)  {
     printf("Java env : %p   jobject :%p\n", env,obj);
     pthread_t thread1;
     pthread_create(&thread1,NULL, thread_fun, NULL);
     callJavaMethod();
     return;
}
void thread_fun(void){

      printf("thread %d\n", pthread_self());
      printf("This is the message before sleep() function\n");
      sleep(5); //1000 microsecond= 1 second will sleep...
      printf("This is the message after 1 second\n");
     callJavaMethod();
         pthread_exit(0);

}


JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved) {
	printf("c onload method\n");
	cachedJVM = jvm;
	return JNI_VERSION_1_8;
}

void callJavaMethod()
{
	int attached = attach_jvm(&gEnv);
	printf("attached jvm %d\n",attached);

	jclass pcieConnectionClass;
	jmethodID getDeviceName;
	//gFromAttachEnv = (JNIEnv *)AttachJava();

	//printf("callJavaMethod - gFromAttachEnv  ---- %p\n", gEnv);
	printf("callJavaMethod - gEnv  ---- %p\n", gEnv);


//	pcieConnectionClass = (*gEnv)->GetObjectClass(gEnv, gObject);
 pcieConnectionClass = (jclass)(*gEnv)->NewGlobalRef(gEnv, 
                        (*gEnv)->FindClass(gEnv, "HelloWorld"));
	printf("callJavaMethod - GetObjectClass - executed successfully\n");

	/* Get the MethodID for the getRemoteSddress available in PCIEConnection class */
	getDeviceName = (*gEnv)->GetStaticMethodID(gEnv, pcieConnectionClass, "printNumber", "(I)V");

	printf("callJavaMethod - GetMethodID - executed successfully\n");

	/* call the method to get the remote address */
	(*gEnv)->CallStaticVoidMethod(gEnv, pcieConnectionClass, getDeviceName,1);

	printf("callJavaMethod - CallVoidMethod - executed successfully\n");
}

