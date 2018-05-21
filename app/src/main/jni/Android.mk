MY_LOCAL_PATH := $(call my-dir) 

include $(CLEAR_VARS)    

LOCAL_PATH := $(MY_LOCAL_PATH)
  
include $(CLEAR_VARS)    

LOCAL_MODULE := signature  
LOCAL_SRC_FILES := signature.cpp 
include $(BUILD_SHARED_LIBRARY)   

