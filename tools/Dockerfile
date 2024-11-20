# to build a new image with different raylib version, change the RAYLIB_VERSION value, and from the
# command line, send: docker build -t raylib_static_build:x.x tools/

FROM ubuntu:22.04

# tag from github to specify raylib version
ARG RAYLIB_VERSION=5.5

WORKDIR /app

# installing dependencies
RUN apt update && \
    apt install -y --no-install-recommends \
    build-essential \
    git \
    ca-certificates \
    libasound2-dev \
    libx11-dev \
    libxrandr-dev \
    libxi-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    libxcursor-dev \
    libxinerama-dev \
    libwayland-dev \
    libxkbcommon-dev && \
    apt clean && \
    rm -rf /var/lib/apt/lists/*

# installing raylib using the version defined before
RUN git clone --branch ${RAYLIB_VERSION} --depth 1 https://github.com/raysan5/raylib.git raylib && \
    cd raylib/src/ && \
    make PLATFORM=PLATFORM_DESKTOP && \
    make install && \
    cd ../../ && \
    rm -r raylib/

CMD [ "/bin/bash" ]