FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update && apt-get install -y \
    python3 \
    python3-pip \
    git \
    curl \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

# Install PlatformIO
RUN pip3 install -U platformio

WORKDIR /workspace

# Create a non-root user and switch to it
RUN useradd -ms /bin/bash vscode
USER vscode

EXPOSE 3000

CMD ["bash"]
