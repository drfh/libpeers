#	FROM gcc:4.9
FROM gcc:4.9 AS libpeers_dev
LABEL version=libpeers_dev
RUN git clone https://github.com/json-c/json-c.git &&\
			cd json-c &&\
			sh autogen.sh &&\
			./configure &&\
			make &&\
			make install
RUN rm -rf json-c/
COPY . /usr/src/libpeers
WORKDIR /usr/src/libpeers
