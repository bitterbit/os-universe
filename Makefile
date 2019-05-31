# 1. Build kernel
# 2. Build rootfs
# 3. Build chrome.img

K_IMAGE := "osu-kernel"

kernel : out/bzImage

out/bzImage :
	k_name=osu-kernel-$$(date +'%Y%m%d-%H%M%S') && \
	    echo "name $$k_name" && \
	    cd linux-kernel && docker build -t $(K_IMAGE) . && cd - && \
	    docker create --name "$$k_name" $(K_IMAGE) && \
	    docker cp "$$k_name:/out/bzImage" out/ && \
	    docker rm "$$k_name"

