ROOT=$HOME/dev/os-universe
docker run  --mount type=bind,source=$ROOT/third_party/cros-sdk,target=/root/chroot \
            --mount type=bind,source=$ROOT/third_party/chromium/,target=/root/chroot/chromium \
            --mount type=bind,source=$ROOT/userspace/,target=/root/chroot/userspace \
            --mount type=bind,source=$ROOT/tools/chrome_build/chrooted_scripts,target=/root/chroot/scripts \
    --cap-add=SYS_ADMIN \
    --privileged \
    -it osu-docker-chroot -l
