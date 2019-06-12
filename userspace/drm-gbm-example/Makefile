ID=6b2a76f98d41

.PHONY: docker clean

drm-gbm :
	gcc -lEGL -ldrm -lgbm -lGLESv2 -DMESA_EGL_NO_X11_HEADERS -I/usr/include/libdrm *.c *.h -o drm-gbm

docker : 
	docker cp $(PWD) $(ID):/root/

clean:
	rm drm-gbm
