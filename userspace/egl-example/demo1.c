#define MESA_EGL_NO_X11_HEADERS

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <gbm.h>

int main() {
    int major;
    int minor;
    int result;

    // const char * extensions = eglQueryString(EGL_NO_DISPLAY, EGL_EXTENSIONS);
    // printf("configs: %d, extensions %s\n", extensions);

    int32_t fd = open ("/dev/dri/card0", O_RDWR);
    assert (fd > 0);
        
    struct gbm_device *gbm = gbm_create_device (fd);
    assert (gbm != NULL);

    // setup EGL from the GBM device
    EGLDisplay dpy = eglGetPlatformDisplay(EGL_PLATFORM_GBM_MESA, gbm, NULL);
    assert (dpy != NULL);

    result = eglInitialize(dpy, &major, &minor);
    assert(result != 0);
    printf("Initialized major: %d minor: %d\n", major, minor);

    const char *egl_extension_st = eglQueryString (dpy, EGL_EXTENSIONS);
    assert (strstr (egl_extension_st, "EGL_KHR_create_context") != NULL);
    assert (strstr (egl_extension_st, "EGL_KHR_surfaceless_context") != NULL);

    EGLint num_configs;
    eglGetConfigs(dpy, NULL, 1, &num_configs);
    printf("Number of EGL configs: %d\n", num_configs);
    assert(num_configs > 0);

    static const EGLint config_attribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT_KHR,
        EGL_NONE
    };


    EGLConfig config;
    eglChooseConfig(dpy, config_attribs, &config, 1, &num_configs);
    assert(config != NULL);

    result = eglBindAPI (EGL_OPENGL_ES_API);
    assert(result);

    EGLContext core_ctx = eglCreateContext (dpy, config, EGL_NO_CONTEXT, NULL);
    assert (core_ctx != EGL_NO_CONTEXT);

    struct gbm_surface *gbm_srfc = gbm_surface_create(gbm, 256, 256, GBM_FORMAT_ARGB8888, GBM_BO_USE_RENDERING);
    assert(gbm_srfc != NULL);
    printf("Created GBM surface\n");

    EGLSurface surface = eglCreateWindowSurface(dpy, config, (EGLNativeWindowType) gbm_srfc, NULL);
     assert(surface != NULL);
     printf("Created EGL surface\n");

    result = eglMakeCurrent (dpy, surface, surface, core_ctx);
    // result = eglMakeCurrent (dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, core_ctx);
    assert(result != 0);

    printf("All good, painting!\n");

    // clear the color buffer 
    glClearColor(1.0, 1.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    
    printf("Done... cleanning up\n");

    eglDestroyContext(dpy, core_ctx);
    // eglDestroySurface(dpy, surface);
    eglTerminate(dpy);
    // TODO: close bgm too
    close(fd);

    /*
    // display = eglGetDisplay((EGLNativeDisplayType)gbm);
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY)  {
        printf("No display found\n");
    }
    */
}

