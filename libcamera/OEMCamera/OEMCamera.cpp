define LOG_NDEBUG 0
#define LOG_TAG "OemCamera"

#include "OemCamera.h"

gralloc_module_t const* SecCameraHardware::mGrallocHal;
ExynosBuffer TempBuf;

SecCameraHardware::~SecCameraHardware()
{
    setCamPower(mExtCamType, 0);
}

bool SecCameraHardware::nativeFlushPreview(char* prev_buffer)
{
#if defined(FLUSH_PREVIEW_H)
    /* process the preview in HAL. */
    FlushPreview *flushPrev = new FlushPreview();
    flushPrev->flushPreview(
                  mGrallocHal,
                  mPrevWindow,
                  prev_buffer,
                  mWidth,
                  mHeight);
#else
    ALOGV("%s: is not supported.", __FUNCTION__);
#endif
    return true;
}
