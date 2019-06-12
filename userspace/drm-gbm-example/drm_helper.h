/* please refer better example: https://github.com/dvdhrm/docs/tree/master/drm-howto/ */

#ifndef _DRM_HELPER_H_
#define _DRM_HELPER_H_

#include <xf86drm.h>
#include <xf86drmMode.h>

enum {
	DEPTH = 24,
	BPP = 32,
};

struct drm_dev_t {
	uint32_t *buf;
	uint32_t conn_id, enc_id, crtc_id, fb_id;
	uint32_t width, height;
	uint32_t pitch, size, handle;
	drmModeModeInfo mode;
	drmModeCrtc *saved_crtc;
	struct drm_dev_t *next;
};

int drm_open(const char *path);

struct drm_dev_t *drm_find_dev(int fd);
void drm_setup_fb(int fd, struct drm_dev_t *dev);
void drm_destroy(int fd, struct drm_dev_t *dev_head);

#endif // _DRM_HELPER_H_
