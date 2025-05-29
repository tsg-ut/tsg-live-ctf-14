FROM ubuntu@sha256:67cadaff1dca187079fce41360d5a7eb6f7dcd3745e53c79ad5efd8563118240


RUN apt-get update && \
  apt-get -y upgrade && \
  apt-get install -y \
  xinetd \
  iproute2

RUN groupadd -r user && useradd -r -g user user

COPY --chown=root:user ./build/start.sh /home/user/start.sh
COPY --chown=root:user ./build/flag /home/user/flag
COPY --chown=root:user ./dist/traditional_fork_chall /home/user/traditional_fork_chall
COPY --chown=root:root ./build/ctf.conf /etc/xinetd.d/ctf

WORKDIR /home/user

RUN chmod 444 ./flag && \
  chmod 555 ./traditional_fork_chall && \
  chmod 555 ./start.sh && \
  chmod 444 /etc/xinetd.d/ctf

RUN mv ./flag ./flag-$(md5sum flag | awk '{print $1}').txt

USER user
EXPOSE 38579

CMD ["xinetd", "-dontfork", "-f","/etc/xinetd.d/ctf"]
