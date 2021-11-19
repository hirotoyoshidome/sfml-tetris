FROM ubuntu:20.04
ENV DEBIAN_FRONTEND=noninteractive

WORKDIR /var/dev

RUN apt-get update && \
    apt-get install -y build-essential cmake g++ libssl-dev vim bash-completion libsfml-dev
