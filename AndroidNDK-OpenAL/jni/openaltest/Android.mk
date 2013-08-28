LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

# имя нашего модуля, который будет вызываться в Java при помощи System.loadLibrary()
LOCAL_MODULE    := AndroidNDK

LOCAL_C_INCLUDES :=  $(LOCAL_PATH)/../openal/ $(LOCAL_PATH)/../openal/include/AL $(LOCAL_PATH)/utils $(LOCAL_PATH)/../tremolo

LOCAL_STATIC_LIBRARIES :=  openal tremolo

LOCAL_CFLAGS := -DANDROID_NDK -fexceptions -Wno-psabi -DGL_GLEXT_PROTOTYPES=1

LOCAL_DEFAULT_CPP_EXTENSION := cpp

#список файлов, который нужно собрать
LOCAL_SRC_FILES := MyNative.cpp \
	utils\AAssetFile.cpp \
	utils\OALContext.cpp \
	utils\OALSound.cpp \
	utils\OALOgg.cpp \
	utils\OALWav.cpp
#список библиотек из ndk, которые надо включить в сборку
LOCAL_LDLIBS :=  -ldl -llog -lz -landroid

include $(BUILD_SHARED_LIBRARY)
