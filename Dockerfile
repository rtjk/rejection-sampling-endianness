FROM ubuntu:latest

ENV DEBIAN_FRONTEND noninteractive

# Get all packages
RUN apt update
RUN apt install -y git cmake libssl-dev nano clang

# Clone
WORKDIR /my
# GITHUB
#RUN git clone --depth 1 https://github.com/rtjk/rejection-sampling-endianness
# LOCAL
WORKDIR /my/rejection-sampling-endianness
COPY . .

STOPSIGNAL SIGTERM

# Run
WORKDIR /my/rejection-sampling-endianness
ENTRYPOINT \
    # WITH ADDRESS SANITIZER
    #rm main.o; gcc main.c -o main.o -g -fsanitize=address; ./main.o; \
    # WITHOUT ADDRESS SANITIZER
    #rm main.o; gcc main.c -o main.o; ./main.o; \
    # CLANG
    rm main.o; clang main.c -o main.o; ./main.o; \
    /bin/bash