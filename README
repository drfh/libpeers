### Docker build environment setup
docker build --no-cache -t libpeers_dev .

## Docker environment cleanup
docker system prune -a --volumes --filter 'label=libpeers'

## Active developmet
docker run --rm -it -v ${PWD}:/usr/src/libpeers -w /usr/src/libpeers libpeers_dev bash


## Make all targets
docker run --rm -v /usr/src/libpeers -w /usr/src/libpeers libpeers_dev make all

## Make just the library
docker run --rm -v /usr/src/libpeers -w /usr/src/libpeers libpeers_dev make lib

## Make clean
docker run --rm -v /usr/src/libpeers -w /usr/src/libpeers libpeers_dev make clean
