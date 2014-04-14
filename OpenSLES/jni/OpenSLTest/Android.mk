LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)


LOCAL_MODULE    := OpenSL

LOCAL_C_INCLUDES :=   $(LOCAL_PATH)/utils  $(LOCAL_PATH)/../tremolo \

LOCAL_STATIC_LIBRARIES :=  tremolo

LOCAL_CFLAGS := -DANDROID_NDK -fexceptions -Wno-psabi -DGL_GLEXT_PROTOTYPES=1 -fpermissive

LOCAL_DEFAULT_CPP_EXTENSION := cpp


LOCAL_SRC_FILES := MyNative.cpp \
	utils/OSLContext.cpp \
	utils/OSLSound.cpp \
	utils/OSLWav.cpp \
	utils/OSLMp3.cpp \
	utils/OSLOgg.cpp \
	utils/OSLPlayer.cpp \
	utils/OSLBufferPlayer.cpp \
	utils/OSLAssetPlayer.cpp \



LOCAL_LDLIBS :=  -ldl -llog -lz -landroid  -lOpenSLES
include $(BUILD_SHARED_LIBRARY)
