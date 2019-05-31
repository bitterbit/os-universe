FROM alpine 

RUN wget https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.10.6.tar.xz && tar xf linux-4.10.6.tar.xz && rm linux-4.10.6.tar.xz
ADD kernel.config /linux-4.10.6/.config
RUN apk add build-base bc

WORKDIR /linux-4.10.6

# Build needs kernel headers, put them where it expectes them
RUN make INSTALL_HDR_PATH=dest headers_install && \
    find dest/include \( -name .install -o -name ..install.cmd \) -delete && \
    cp -rv dest/include/* /usr/include

RUN make -j$(grep -c ^processor /proc/cpuinfo)

# Publish output under /out
RUN mkdir -p /out/include && \ 
    cp arch/x86/boot/bzImage /out/ && \
    cp -rv dest/include/* /out/include

WORKDIR /
