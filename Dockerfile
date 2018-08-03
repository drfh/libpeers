#	FROM gcc:4.9
FROM gcc:4.9 AS libpeers_dev
LABEL version=libpeers_dev
COPY . /usr/src/libpeers
WORKDIR /usr/src/libpeers
