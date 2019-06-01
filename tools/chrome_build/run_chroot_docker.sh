ROOT=$HOME/dev/os-universe-new
docker run  --mount type=bind,source=$ROOT/third_party/cros-sdk,target=/root/chroot \
            --mount type=bind,source=$ROOT/third_party/chromium/,target=/root/chroot/chromium \
            --mount type=bind,source=$ROOT/userspace/,target=/root/chroot/userspace \
    --cap-add=SYS_ADMIN \
    --privileged \
    -it osu-docker-chroot -l
