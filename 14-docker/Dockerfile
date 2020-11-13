FROM alpine:latest

LABEL maintainer="Brunino Criniti <crinitib@gmail.com>"

VOLUME "/project"

WORKDIR "/project"

RUN apk update && \
    apk upgrade && \
    apk --update --no-cache add \
        gcc \
        g++ \
        build-base \
        cmake \
        bash \
        libstdc++ \
        cppcheck 

ENTRYPOINT [ "bash", "-c" ]