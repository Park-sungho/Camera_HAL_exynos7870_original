LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

# Prebuild Libpreview
ifeq ($(BOARD_PREBUILT_OEM_LIBRARY),true)
LOCAL_MODULE := libpreview
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_SRC_FILES_arm := lib/libpreview.so
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_PATH := $(TARGET_OUT)/lib
include $(BUILD_PREBUILT)
else
# Compile Libpreview
LOCAL_SHARED_LIBRARIES:= libutils libcutils libbinder liblog libcamera_client libhardware
LOCAL_SHARED_LIBRARIES += libexynosutils libhwjpeg libexynosv4l2 libexynosgscaler libion_exynos libcsc
LOCAL_SHARED_LIBRARIES += libexpat libstlport
LOCAL_SHARED_LIBRARIES += libpower

LOCAL_CFLAGS += -DGAIA_FW_BETA
LOCAL_CFLAGS += -DMAIN_CAMERA_SENSOR_NAME=$(BOARD_BACK_CAMERA_SENSOR)
LOCAL_CFLAGS += -DFRONT_CAMERA_SENSOR_NAME=$(BOARD_FRONT_CAMERA_SENSOR)
LOCAL_CFLAGS += -DUSE_CAMERA_ESD_RESET

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/../include \
	$(LOCAL_PATH)/../libcamera \
	$(TOP)/hardware/samsung_slsi-cm/exynos/libcamera/54xx \
	$(TOP)/hardware/samsung_slsi-cm/exynos/libcamera/54xx/JpegEncoderForCamera \
	$(TOP)/hardware/samsung_slsi-cm/exynos/libcamera/common \
	$(TOP)/hardware/samsung_slsi-cm/exynos/libcamera/common/Pipes \
	$(TOP)/hardware/samsung_slsi-cm/exynos/libcamera/common/Activities \
	$(TOP)/hardware/samsung_slsi-cm/exynos/libcamera/common/Buffers \
	$(TOP)/system/media/camera/include \
	$(LOCAL_PATH)/../libcamera/Vendor \
	$(TOP)/hardware/samsung_slsi-cm/exynos/include \
	$(TOP)/hardware/samsung_slsi-cm/$(TARGET_SOC)/include \
	$(TOP)/hardware/samsung_slsi-cm/$(TARGET_BOARD_PLATFORM)/include \
	$(TOP)/hardware/samsung_slsi-cm/$(TARGET_BOARD_PLATFORM)/libcamera \
	$(TOP)/hardware/libhardware_legacy/include/hardware_legacy \
	$(TOP)/vendor/samsung/feature/CscFeature/libsecnativefeature \
	$(TOP)/bionic \
	$(TOP)/external/expat/lib \
	$(TOP)/external/stlport/stlport

LOCAL_SRC_FILES:= \
	flushpreview.cpp

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := libpreview

include $(BUILD_SHARED_LIBRARY)
endif
