LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

# имя нашего модуля, который будет вызываться в Java при помощи System.loadLibrary()
LOCAL_MODULE    := OpenSL

LOCAL_C_INCLUDES :=   $(LOCAL_PATH)/utils \



LOCAL_CFLAGS := -DANDROID_NDK -fexceptions -Wno-psabi -DGL_GLEXT_PROTOTYPES=1 -fpermissive

LOCAL_DEFAULT_CPP_EXTENSION := cpp

#список файлов, который нужно собрать
LOCAL_SRC_FILES := MyNative.cpp \
	utils/OSLContext.cpp \
	utils/OSLSound.cpp \
	utils/OSLWav.cpp \
	utils/OSLPlayer.cpp \
	utils/OSLBufferPlayer.cpp \
	utils/OSLAssetPlayer.cpp \


#список библиотек из ndk, которые надо включить в сборку
LOCAL_LDLIBS :=  -ldl -llog -lz -landroid -lOpenSLES

include $(BUILD_SHARED_LIBRARY)
