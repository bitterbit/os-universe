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

/* a dummy compute shader that does nothing */
#define COMPUTE_SHADER_SRC "          \
#version 310 es\n                                                       \
                                                                        \
layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;       \
                                                                        \
void main(void) {                                                       \
	   /* awesome compute code here */                              \
}                                                                       \
"

static EGLint const attribute_list[] = {
	EGL_RED_SIZE, 1,
	EGL_GREEN_SIZE, 1,
	EGL_BLUE_SIZE, 1,
	EGL_NONE
};

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
    //EGLDisplay egl_dpy = eglGetPlatformDisplay (EGL_PLATFORM_GBM_MESA, gbm, NULL);
    EGLDisplay dpy = eglGetDisplay(gbm);
    assert (dpy != NULL);

    result = eglInitialize(dpy, &major, &minor);
    assert(result != 0);

    const char *egl_extension_st = eglQueryString (dpy, EGL_EXTENSIONS);
    assert (strstr (egl_extension_st, "EGL_KHR_create_context") != NULL);
    assert (strstr (egl_extension_st, "EGL_KHR_surfaceless_context") != NULL);

    EGLint num_configs;
    EGLConfig config;
    eglGetConfigs(dpy, &config ,1 , &num_configs);
    assert(num_configs > 0);
    assert(config != NULL);

    EGLContext core_ctx = eglCreateContext (dpy, config, EGL_NO_CONTEXT, NULL);
    assert (core_ctx != EGL_NO_CONTEXT);

    result = eglMakeCurrent (dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, core_ctx);
    assert(result != 0);

    GLuint compute_shader = glCreateShader (GL_FRAGMENT_SHADER);
    assert (glGetError () == GL_NO_ERROR);

    const char *shader_source = COMPUTE_SHADER_SRC;
    glShaderSource (compute_shader, 1, &shader_source, NULL);
    assert (glGetError () == GL_NO_ERROR);

    glCompileShader (compute_shader);
    assert (glGetError () == GL_NO_ERROR);

    GLuint shader_program = glCreateProgram ();
    glAttachShader (shader_program, compute_shader);
    assert (glGetError () == GL_NO_ERROR);
    glLinkProgram (shader_program);
    assert (glGetError () == GL_NO_ERROR);

    glDeleteShader (compute_shader);
    glUseProgram (shader_program);
    assert (glGetError () == GL_NO_ERROR);

    /*
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 255.0f);
    */
    // clear the color buffer
    /*
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.5, 0.5);
    	glVertex2f(-0.5, -0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(-0.5, -0.5);
	glVertex2f(0.5, -0.5);
    glEnd();
    */

    /*
    // display = eglGetDisplay((EGLNativeDisplayType)gbm);
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY)  {
        printf("No display found\n");
    }

    result = eglInitialize(display, &major, &minor);
    if (result == EGL_FALSE) {
        printf("Initialize error\n");
    }

    printf("Major version %d minor  %d \n", major, minor);

    int n_of_configs;
    result = eglGetConfigs(display , &config , 1 , &n_of_configs);
    if (result == EGL_FALSE) {
        printf("Error getting config\n");
    }

    ctx = eglCreateContext(display, config, EGL_NO_CONTEXT, NULL);
    if (!ctx) {
        printf("Error creating context\n");
    }

    NativeWindowType native_window = createNativeWindow();

    eglCreateWindowSurface(display, config, native_window, NULL);
    if (!surface){
        printf("Error creating surface\n");
    }

    eglMakeCurrent(display, surface, surface, ctx);

    printf("All good, painting!\n");

    // clear the color buffer 
    glClearColor(1.0, 1.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
    
    printf("Done... cleanning up\n");

    eglDestroyContext(display, ctx);
    eglDestroySurface(display, surface);
    eglTerminate(display);
    //close(fd);
    //
    */
}

