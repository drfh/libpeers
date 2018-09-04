#	FROM gcc:4.9
FROM gcc:latest
LABEL maintainer="davidrfharris@gmail.com"
LABEL version=latest
RUN apt-get update
RUN	apt-get -y install cmake
RUN	apt-get -y install build-essential
RUN	apt-get -y install git
RUN	apt-get -y install libsodium-dev
RUN	apt-get -y install libqrencode-dev
RUN	apt-get -y install qrencode

WORKDIR /usr/src/libpeers
RUN git clone https://github.com/json-c/json-c.git
RUN cd json-c/
WORKDIR /usr/src/libpeers/json-c/
RUN ./autogen.sh
RUN ./configure
RUN make
RUN make install
WORKDIR /usr/src/libpeers
RUN rm -rf json-c/

#COPY . /usr/src/libpeers

EXPOSE 8333
