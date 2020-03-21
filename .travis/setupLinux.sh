#!/usr/bin/env bash

#sudo add-apt-repository -y ppa:george-edison55/cmake-3.x
sudo apt-get update

if [[ ${COMPILER} == "g++-7" ]]; then
	defCXX gcc-7 g++-7
elif [[ ${COMPILER} == "g++-8" ]]; then
	defCXX gcc-8 g++-8
elif [[ ${COMPILER} == "clang++-7.0" ]]; then
	defCXX clang-7.0 clang++-7.0
elif [[ ${COMPILER} == "clang-5.0" ]]; then
	defCXX clang-5.0 clang++-5.0
fi

if [[ ${TASK} == "sonarcloud" ]]; then
  cd ${TRAVIS_BUILD_DIR}
  #wget https://binaries.sonarsource.com/Distribution/sonar-scanner-cli/sonar-scanner-cli-4.1.0.1829-linux.zip
  #unzip sonar-scanner-cli-4.1.0.1829-linux.zip
  #export PATH="${TRAVIS_BUILD_DIR}/sonar-scanner-cli-4.1.0.1829-linux/bin/:$PATH"
  wget https://sonarcloud.io/static/cpp/build-wrapper-linux-x86.zip
  unzip build-wrapper-linux-x86.zip
  export PATH="${TRAVIS_BUILD_DIR}/build-wrapper-linux-x86/:$PATH"
fi

#if [[ ${FLAGS} == "-DHYPRO_COVERAGE=ON" ]]; then
#  cd ${TRAVIS_BUILD_DIR}
#  wget http://ftp.de.debian.org/debian/pool/main/l/lcov/lcov_1.11.orig.tar.gz
#  tar xf lcov_1.11.orig.tar.gz
#  sudo make -C lcov-1.11/ install
#  gem install coveralls-lcov
#  cd ${TRAVIS_BUILD_DIR}
#  lcov --directory . --zerocounters
#fi

#mkdir -p ~/usr
#PREFIX=`cd ~/usr; pwd`

#if [ ! -f $PREFIX/bin/cmake ]; then#
#	wget -nv https://cmake.org/files/v3.7/cmake-3.7.2-Linux-x86_64.sh
#	chmod +x cmake-3.7.2-Linux-x86_64.sh
#	./cmake-3.7.2-Linux-x86_64.sh --prefix=$PREFIX --exclude-subdir --skip-license
#fi

#export PATH="$PREFIX/bin:$PATH"
