FROM alpine
ENV HOME /root
WORKDIR $HOME
ADD create_chroot.sh create_chroot.sh
RUN echo "./create_chroot.sh" > .profile && chmod +x .profile
ENTRYPOINT ["/bin/ash"]
