FROM alpine
ENV HOME /root
WORKDIR $HOME
ADD scripts/chroot.sh chroot.sh
ADD scripts/chrooted_build.sh chrooted_build.sh 

RUN echo "./chrooted_build.sh" > .profile && chmod +x .profile

ENTRYPOINT ["/bin/ash"]
