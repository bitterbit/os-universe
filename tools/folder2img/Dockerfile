FROM debian
RUN apt-get update && apt-get install -y rsync file
RUN mkdir /mnt/img
WORKDIR /root
ADD folder2img.sh folder2img.sh
ENTRYPOINT ["/bin/bash", "folder2img.sh"]
