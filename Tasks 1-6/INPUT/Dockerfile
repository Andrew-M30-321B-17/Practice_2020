#Загрузить образ убунту 18.04
FROM ubuntu:18.04

# Установим обновления
RUN apt-get update
#add https support
RUN apt -y install apt-transport-https
# Установим gcc-9 and g++-9
RUN apt -y install build-essential
RUN apt -y install software-properties-common
RUN add-apt-repository ppa:ubuntu-toolchain-r/test
RUN apt-get -y install gcc-9 g++-9
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 90 --slave /usr/bin/g++ g++ /usr/bin/g++-9
#git and cmake
RUN apt -y install git
RUN apt -y install cmake
#clone clickhouse
RUN mkdir ch
RUN cd ch && git clone https://github.com/artpaul/clickhouse-cpp.git
#make clickhouse
RUN mkdir build
RUN cd build && cmake ../ch/clickhouse-cpp &&  make
#qt5
RUN apt -y install qt5-default
RUN apt -y install qtcreator
#copy files of my app
RUN mkdir myapp
RUN cd myapp && git clone https://github.com/Andrew-M30-321B-17/test.git
RUN cd myapp && ls
RUN make myapp/test/Practice_29-06-2020
