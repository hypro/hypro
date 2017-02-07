#!/usr/bin/env bash

set -ev

sudo add-apt-repository -y ppa:george-edison55/cmake-3.x

if [[ ${COMPILER} == "g++-5" ]]; then
	sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
	sudo apt-get update
	install_linux g++-5
	defCXX gcc-5 g++-5
elif [[ ${COMPILER} == "g++-6" ]]; then
	sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
	sudo apt-get update
	install_linux g++-6
	defCXX gcc-6 g++-6
elif [[ ${COMPILER} == "clang++-3.4" ]]; then
	sudo add-apt-repository -y "deb http://llvm.org/apt/precise/ llvm-toolchain-precise-3.4 main"
	sudo apt-get update
	install_linux clang++-3.4
	defCXX clang-3.4 clang++-3.4
elif [[ ${COMPILER} == "clang++-3.5" ]]; then
	sudo add-apt-repository -y "deb http://llvm.org/apt/precise/ llvm-toolchain-precise-3.5 main"
	sudo apt-get update
	install_linux clang++-3.5
	defCXX clang-3.5 clang++-3.5
elif [[ ${COMPILER} == "clang++-3.6" ]]; then
	sudo add-apt-repository -y "deb http://llvm.org/apt/precise/ llvm-toolchain-precise-3.6 main"
	sudo apt-get update
	install_linux clang++-3.6
	defCXX clang-3.6 clang++-3.6
elif [[ ${COMPILER} == "clang++-3.7" ]]; then
	sudo add-apt-repository -y "deb http://llvm.org/apt/precise/ llvm-toolchain-precise-3.7 main"
	sudo apt-get update
	install_linux clang++-3.7
	defCXX clang-3.7 clang++-3.7
fi

sudo apt-get install cmake libboost1.55-all-dev libeigen3-dev libglpk-dev doxygen graphviz

if [[ ${FLAGS} == "-DHYPRO_COVERAGE=ON" ]]; then
  cd ${TRAVIS_BUILD_DIR}
  wget http://ftp.de.debian.org/debian/pool/main/l/lcov/lcov_1.11.orig.tar.gz
  tar xf lcov_1.11.orig.tar.gz
  sudo make -C lcov-1.11/ install
  gem install coveralls-lcov
  cd ${TRAVIS_BUILD_DIR}
  lcov --directory . --zerocounters
fi
