FROM ubuntu:22.04

RUN apt update && apt install -y \
    iproute2 \
    iputils-ping \
    net-tools \
    arping \
    tcpdump

WORKDIR /root

CMD ["sleep", "infinity"]