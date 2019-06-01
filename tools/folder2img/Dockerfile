FROM debian
RUN apt-get update && apt-get install -y rsync
RUN mkdir /mnt/img
WORKDIR /root
ADD folder2img.sh folder2img.sh
ENTRYPOINT ["/bin/sh", "folder2img.sh"]
