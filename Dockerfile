FROM gitpod/workspace-full:latest

# Inspiration: https://www.gitpod.io/blog/docker-in-gitpod/
# Install clang-tidy
USER root
RUN apt-get update && apt-get install -y \
		clang-tidy libboost-all-dev \
	&& apt-get clean && rm -rf /var/cache/apt/* && rm -rf /var/lib/apt/lists/* && rm -rf /tmp/*
