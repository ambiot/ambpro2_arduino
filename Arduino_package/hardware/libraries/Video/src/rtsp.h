#ifndef __RTSP_H__
#define __RTSP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "rtsp_drv.h"
#include "avcodec.h"

#ifdef __cplusplus
}
#endif

#include "video.h"
#include "audio.h"

class RTSP:public MMFModule {
    public:
        RTSP(void);
        ~RTSP(void);

        void configVideo(VideoSetting& config);
        void configAudio(AudioSetting& config);
        void begin(void);
        void end(void);

        int enableAudio(void);
        int getPort(void);
        int printInfo (void);

    private:
};

#endif