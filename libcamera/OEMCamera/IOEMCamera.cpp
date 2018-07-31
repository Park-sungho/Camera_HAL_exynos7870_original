define LOG_NDEBUG 0
#define LOG_TAG "IOEMCamera"

#include "IOEMCamera.h"

IOEMCamera::~IOEMCamera()
{
}

bool IOEMCamera::nativePreviewThread()
{
    srcAddr = mFliteNode.buffer[index].virt.extP[plane];
    dstAddr = dstBuf.virt.extP[plane];
    if(srcAddr == NULL ||  dstAddr == NULL) {
        ALOGI(" **** previewZoomThread: Invalid memory");
    } else {
        memcpy(dstAddr, srcAddr, dstBuf.size.extS[plane]);
        mDataCb(CAMERA_MSG_PREVIEW_FRAME, mPreviewHeap, index, NULL, mCallback);
        /* Display preview in HAL */
        nativeFlushPreview(dstBuf.virt.extP[plane]);
    }
    
    return true;
}
