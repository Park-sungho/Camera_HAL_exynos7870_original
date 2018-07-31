
#ifndef HAL_OEMCAMERA_HEADER
#define HAL_OEMCAMERA_HEADER

#include <poll.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <private/android_filesystem_config.h>

#include <time.h>
#include <cutils/properties.h>
#include <camera/Camera.h>
#include <media/hardware/MetadataBufferType.h>
#include <utils/Endian.h>

#include <linux/videodev2.h>

#include <ExynosJpegApi.h>
#include <FlushPreview.h>

#include "IOEMCamera.h"
#include "Exif.h"

namespace android {

class OEMCamera : public IOEMCamera {
public:
    OEMCamera(int cameraId, camera_device_t *dev);
    virtual ~OEMCamera();

protected:
    virtual bool nativeFlushPreview(char* prev_buffer);
}

}; /* namespace android */

#endif
