define LOG_NDEBUG 0
#define LOG_TAG "IOEMCamera"

#include "IOEMCamera.h"
#define FLANE_MAX 1
    
IOEMCamera::~IOEMCamera()
{
}

bool IOEMCamera::IOEMPreviewThread()
{
    char *srcAddr, dstAddr;
    int index = getPreviewIndex();
    
    dstBuf.virt.p = (char *)mCamHeap->data + (index * (mCamSize-SPARE_SIZE * SPARE_PLANE));
    dstBuf.fd.extFd[0] = mCamFd;
    
    for (int plane = 0; plane < FLANE_MAX; plane++) {
        srcAddr = mFliteNode.buffer[index].virt.extP[plane];
        dstAddr = dstBuf.virt.extP[plane];        
        if(srcAddr != NULL && dstAddr != NULL) {
            if (mMsgEnabled & CAMERA_MSG_PREVIEW_FRAME) {
                memcpy(dstAddr, srcAddr, dstBuf.size.extS[plane]);
                mDataCb(CAMERA_MSG_PREVIEW_FRAME, mCamHeap, index, mCallback);
            }           
            
            /* preview in HAL */
            nativeFlushPreview(dstBuf.virt.extP[plane]);
        }        
    }

    nativeReleaseFrame(index);

    return true;
}
