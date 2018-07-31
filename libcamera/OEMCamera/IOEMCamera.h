#ifndef HAL_IOEMCAMERA_HEADER
#define HAL_IOEMCAMERA_HEADER

#include <utils/List.h>
#include <utils/threads.h>
#include <utils/RefBase.h>
#include <cutils/compiler.h>
#include <binder/MemoryBase.h>
#include <binder/MemoryHeapBase.h>
#include <ui/GraphicBufferMapper.h>
#include <hardware/camera.h>
#include <hardware/gralloc.h>
#include <camera/CameraParameters.h>
#include <cutils/properties.h>
#include <fcntl.h>
#include <utils/Log.h>

namespace android {

class OEMCamera : public virtual RefBase {
public:
    IOEMCamera(int cameraId, camera_device_t *dev);
    virtual ~IOEMCamera();

protected:
    virtual bool nativeFlushPreview(char* prev_buffer) = 0;
}

}; /* namespace android */

#endif
