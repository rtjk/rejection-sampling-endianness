FROM ubuntu:22.04

ENV DEBIAN_FRONTEND noninteractive

# Get all packages
RUN apt update
RUN apt install -y git cmake libssl-dev nano

RUN echo "aaaa"

# Clone
WORKDIR /my
RUN git clone --depth 1 https://github.com/rtjk/rejection-sampling-endianness

STOPSIGNAL SIGTERM

# Run
WORKDIR /my/rejection-sampling-endianness
ENTRYPOINT \
    # WITH ADDRESS SANITIZER
    #rm main.o; gcc main.c -o main.o -g -fsanitize=address; ./main.o; \
    # WITHOUT ADDRESS SANITIZER
    rm main.o; gcc main.c -o main.o; ./main.o; \
    /bin/bash