/*
**
** Copyright 2018, SHPark
**
** Added by shpark
*/

/* #define LOG_NDEBUG 0 */
#define LOG_TAG "FlushPreview"
#include <cutils/log.h>

#include "FlushPreview.h"

namespace android {

#ifndef NO_ERROR
#define NO_ERROR 0
#endif

FlushPreview::FlushPreview()
{
}

FlushPreview::~FlushPreview()
{
}

bool FlushPreview::setPreviewBuffer(int width, int height,
		unsigned char* src, unsigned char* dest)
{
    memcpy(dest, src, width*height);
    return true;
}

bool FlushPreview::flushPreview(gralloc_module_t const* mGrallocHal, 
		preview_stream_ops *mPreviewWindow, char* prev_buffer,
		int width, int height)
{
   if (prev_buffer == NULL) {
        ALOGE("%s: Preview buffer is NULL", __FUNCTION__);
        return false;
    }

    buffer_handle_t* buffer = NULL;
    buffer_handle_t **bufHandle = NULL;
    int stride = 0;
    int res;
    void* grallocAddr[3] = {NULL};

    if (width < 1 || height < 1) {
        ALOGE("%s: Preview size is failed.", __FUNCTION__);
        return false;
    }

    Mutex::Autolock lock(mMutexLockObject);

    /* Dequeue preview window buffer for the frame. */
    res = mPreviewWindow->dequeue_buffer(mPreviewWindow, &buffer, &stride);
    if (res != NO_ERROR || buffer == NULL) {
        ALOGE("%s: Unable to dequeue preview window buffer", __FUNCTION__);
        return false;
    }

    /* Let the preview window to lock the buffer. */
    res = mPreviewWindow->lock_buffer(mPreviewWindow, buffer);
    if (res != NO_ERROR) {
        ALOGE("%s: Unable to lock preview window buffer", __FUNCTION__);
        mPreviewWindow->cancel_buffer(mPreviewWindow, buffer);
        return false;
    }

    bufHandle = &buffer;

    /* Now let the graphics framework to lock the buffer, and provide
     * us with the framebuffer data address. */
    mGrallocHal->lock(mGrallocHal,
                    **bufHandle,
                    GRALLOC_USAGE_SW_READ_OFTEN,
                    0, 0,
                    width, height,
                    grallocAddr);

    if (grallocAddr[0] == NULL || grallocAddr[1] == NULL) {
        ALOGE("%s: Gralloc is failed.", __FUNCTION__);
        mPreviewWindow->cancel_buffer(mPreviewWindow, buffer);
        return false;
    }

    mMutex.lock();

    /* YUV plane buffer */
    setPreviewBuffer(width, height, (unsigned char*)prev_buffer, (unsigned char*)grallocAddr[0]);
    memset(grallocAddr[1], 0x80, width*height/2);

    mPreviewWindow->enqueue_buffer(mPreviewWindow, buffer);

    mMutex.unlock();

    mGrallocHal->unlock(mGrallocHal, *buffer);
	
	return true;
}

}; /* namespace android */
