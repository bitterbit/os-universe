# 1. Build kernel
# 2. Build rootfs
# 3. Build chrome.img

K_IMAGE := "osu-kernel"
GZIP_LEVEL := 1 # 1 is lowest and 9 heighest

.PHONY : kernel rootfs chromeimg chromebuild chrome
kernel : out/bzImage
rootfs : out/rootfs-chrome.cpio.gz


out/bzImage :
	k_name=osu-kernel-$$(date +'%Y%m%d-%H%M%S') && \
	    echo "name $$k_name" && \
	    cd kernel && docker build -t $(K_IMAGE) . && cd - && \
	    docker create --name "$$k_name" $(K_IMAGE) && \
	    docker cp "$$k_name:/out/bzImage" out/ && \
	    docker rm "$$k_name"

out/rootfs-chrome.cpio.gz :
	cd rootfs && \
	    find . -print0 | cpio --null -ov --format=newc | gzip -$(GZIP_LEVEL) > ../out/rootfs-chrome.cpio.gz

chrome : chromebuild chromeimg 

chromeimg :
	tools/folder2img/run-folder2img.sh $$PWD/third_party/chromium/src/out/Osone $$PWD/out/chrome.img 

chromebuild: 
	tools/chrome_build/run_chroot_docker.sh
