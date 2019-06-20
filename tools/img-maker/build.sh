cp ../../out/bzImage out/
cp ../../out/rootfs-chrome.cpio.gz out/
docker build -t osu-iso-maker .
