FROM ubuntu:22.04

RUN apt update && apt install -y \
    iproute2 \
    iputils-ping \
    net-tools \
    arping \
    tcpdump \
	build-essential \
	make

WORKDIR /app

COPY ./libft /app/libft
COPY ./mandatory /app/mandatory
COPY ./inc /app/inc
COPY ./Makefile /app/

RUN make

CMD ["/app/ft_malcolm"]