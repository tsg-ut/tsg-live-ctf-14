FROM amd64/ubuntu:22.04


RUN apt-get update && \
        apt-get -y upgrade && \
        apt-get install -y \
        xinetd \
        iproute2 \
        qemu-system

RUN groupadd -r user && useradd -r -g user user

COPY --chown=root:user ./build/start.sh /home/user/start.sh
COPY --chown=root:root ./build/ctf.conf /etc/xinetd.d/ctf
COPY --chown=root:user ./build/rootfs.cpio /home/user/rootfs.cpio

COPY --chown=root:user ./dist/bzImage /home/user/bzImage

WORKDIR /home/user

RUN chmod 555 ./start.sh && \
    chmod 444 /etc/xinetd.d/ctf

USER user
EXPOSE 19965

CMD ["xinetd", "-dontfork", "-f","/etc/xinetd.d/ctf"]
