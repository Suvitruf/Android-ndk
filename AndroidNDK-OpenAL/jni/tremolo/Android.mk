LOCAL_PATH := $(call my-dir)

########################################################################################################

include $(CLEAR_VARS)

LOCAL_MODULE     := tremolo
LOCAL_ARM_MODE   := arm
#LOCAL_PATH       := $(ROOT_PATH)/tremolo
LOCAL_SRC_FILES  := bitwise.c      \
                    bitwiseARM.s   \
                    codebook.c     \
                    dpen.s         \
                    dsp.c          \
                    floor0.c       \
                    floor1.c       \
                    floor1ARM.s    \
                    floor1LARM.s   \
                    floor_lookup.c \
                    framing.c      \
                    info.c         \
                    mapping0.c     \
                    mdct.c         \
                    mdctARM.s      \
                    mdctLARM.s     \
                    misc.c         \
                    res012.c       \
                    speed.s        \
                    vorbisfile.c   \
                    speed.s        \

LOCAL_CFLAGS     := -D_ARM_ASSEM_

include $(BUILD_STATIC_LIBRARY)

