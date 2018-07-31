/*
**
** Copyright 2018, Iris Co. LTD
**
** Added by shpark
*/
#ifndef FLUSH_PREVIEW_H
#define FLUSH_PREVIEW_H

#include <poll.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <utils/Mutex.h>
#include <unistd.h>
#include <time.h>
#include <linux/videodev2.h>
#include <hardware/gralloc.h>
#include <hardware/camera.h>

namespace android {

class FlushPreview {
private:
    Mutex           mMutex;
	mutable Mutex   mMutexLockObject;
	
public:
    FlushPreview();
    virtual ~FlushPreview();

	bool flushPreview(gralloc_module_t const* mGrallocHal, 
		preview_stream_ops *mPreviewWindow, char* prev_buffer,
			int width, int height);
private:
	bool FlushPreview::setPreviewBuffer(int width, int height,
			unsigned char* src, unsigned char* dest);
};

}; /* namespace android */

#endif /* FLUSH_CAMERA_H */
