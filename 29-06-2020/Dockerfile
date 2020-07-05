#Dockerfile create for Task1 of Practice_29-06-2020
FROM ubuntu:18.04
MAINTAINER AndrewIgnatiev
RUN apt-get update
RUN apt-get install git
RUN apt-get install cmake
RUN git clone https://github.com/artpaul/clickhouse-cpp.git
RUN mkdir build
RUN cd build
RUN cmake ../clickhouse-cpp
RUN make
RUN apt install qt5-default
RUN apt install libqt5charts5-dev
