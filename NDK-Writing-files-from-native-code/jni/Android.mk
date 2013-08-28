LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

# имя нашего модуля, который будет вызываться в Java при помощи System.loadLibrary()
LOCAL_MODULE    := AndroidNDK

LOCAL_CFLAGS := -DANDROID_NDK  -Wno-psabi -DGL_GLEXT_PROTOTYPES=1

LOCAL_DEFAULT_CPP_EXTENSION := cpp

#список файлов, который нужно собрать
LOCAL_SRC_FILES := MyNative.cpp 

#список библиотек из ndk, которые надо включить в сборку
LOCAL_LDLIBS :=  -llog -landroid

include $(BUILD_SHARED_LIBRARY)
