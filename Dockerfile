FROM ubuntu:22.04

# set working dir
WORKDIR /usr/src/app

# set working language
ENV LANG C.UTF-8

# set timezone
ENV TZ="America/New_York"
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# copy content to container
COPY . /usr/src/app

# update repositories
RUN apt update

# install required software
# RUN apt install -y cmake
RUN apt install -y git
RUN apt install -y gcc g++
RUN apt install -y pkg-config
RUN apt install -y curl wget zip unzip tar
RUN apt install -y libsctp-dev
RUN apt install -y automake libtool flex

# install bison2
RUN wget http://launchpadlibrarian.net/140087282/bison_2.7.1.dfsg-1_amd64.deb
RUN wget http://launchpadlibrarian.net/140087283/libbison-dev_2.7.1.dfsg-1_amd64.deb
RUN dpkg -i libbison-dev_2.7.1.dfsg-1_amd64.deb
RUN dpkg -i bison_2.7.1.dfsg-1_amd64.deb

# To prevent update manager from overwriting this package
RUN apt-mark hold libbison-dev
RUN apt-mark hold bison


# install asn1c
# RUN git clone --depth 1 https://github.com/vlm/asn1c asn1c
RUN git clone --depth 1 https://github.com/mouse07410/asn1c asn1c # it works!
RUN cd asn1c && (test -f configure || autoreconf -iv) && ./configure && make && make install

### run
ENTRYPOINT bash build.sh
