#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <jni.h>
#include <jvmti.h>

static jvmtiEnv *jvmti;
static jrawMonitorID ExtraeJ_AgentLock;

void printStackTrace(JNIEnv *env, jobject exception) {
  jclass throwable_class = env->FindClass("java/lang/Throwable");
  jmethodID print_method =
      env->GetMethodID(throwable_class, "printStackTrace", "()V");
  env->CallVoidMethod(exception, print_method);
}

static void JNICALL exception_callback(jvmtiEnv *jvmti_env, JNIEnv *jni_env,
                                       jthread thread, jmethodID method,
                                       jlocation location, jobject exception,
                                       jmethodID catch_method,
                                       jlocation catch_location) {
  char *class_name;
  jclass exception_class = jni_env->GetObjectClass(exception);
  jvmti->GetClassSignature(exception_class, &class_name, NULL);

  printf("Exception: %s \n", class_name);
  printStackTrace(jni_env, exception);
}

JNIEXPORT jint JNICALL Agent_OnLoad(JavaVM *vm, char *options, void *reserved) {
  jvmtiCapabilities capabilities;
  jvmtiEventCallbacks callbacks;

  vm->GetEnv((void **)&jvmti, JVMTI_VERSION);
  memset(&capabilities, 0, sizeof(capabilities));
  capabilities.can_generate_exception_events = 1;
  capabilities.can_get_line_numbers = 1;
  jvmti->AddCapabilities(&capabilities);
  memset(&callbacks, 0, sizeof(callbacks));
  callbacks.Exception = &exception_callback;
  jvmti->SetEventCallbacks(&callbacks, sizeof(callbacks));
  jvmti->SetEventNotificationMode(JVMTI_ENABLE, JVMTI_EVENT_EXCEPTION, NULL);
  return 0;
}

JNIEXPORT void JNICALL Agent_OnUnload(JavaVM *vm) {}
