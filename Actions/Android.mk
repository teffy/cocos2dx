LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

MY_CPP_LIST := $(wildcard $(LOCAL_PATH)/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/hellocpp/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)
LOCAL_SRC_FILES := $(MY_CPP_LIST:$(LOCAL_PATH)/%=%)


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
#使用了iconv的库，需要添加至到编译路径中
$(LOCAL_PATH)/../../cocos2d/iconv/include \
$(LOCAL_PATH)/../../cocos2d/iconv/libcharset \
$(LOCAL_PATH)/../../cocos2d/iconv/lib \
$(LOCAL_PATH)/../../cocos2d/iconv/libcharset/include \
$(LOCAL_PATH)/../../cocos2d/iconv/srclib \
$(LOCAL_PATH)/../../cocos2d/iconv \
 
LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += iconv_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,iconv)
