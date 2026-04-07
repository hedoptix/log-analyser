FROM 		ubuntu:24.04

RUN 		apt-get update && apt-get install -y \
			build-essential \
			cmake \
			libgtest-dev \
			&& rm -rf /var/lib/apt/lists/*
RUN		cd /usr/src/gtest && cmake . && make && cp lib/*.a /usr/lib

WORKDIR 	/app
