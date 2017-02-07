#!/usr/bin/env bash

#sudo add-apt-repository -y ppa:george-edison55/cmake-3.x
sudo apt-get update

if [[ ${COMPILER} == "g++-5" ]]; then
	defCXX gcc-5 g++-5
elif [[ ${COMPILER} == "g++-6" ]]; then
	defCXX gcc-6 g++-6
elif [[ ${COMPILER} == "clang++-3.4" ]]; then
	defCXX clang-3.4 clang++-3.4
elif [[ ${COMPILER} == "clang-3.5" ]]; then
	defCXX clang-3.5 clang++-3.5
elif [[ ${COMPILER} == "clang++-3.6" ]]; then
	defCXX clang-3.6 clang++-3.6
elif [[ ${COMPILER} == "clang++-3.7" ]]; then
	defCXX clang-3.7 clang++-3.7
elif [[ ${COMPILER} == "clang++-3.8" ]]; then
	defCXX clang-3.8 clang++-3.8
fi

if [[ ${FLAGS} == "-DHYPRO_COVERAGE=ON" ]]; then
  cd ${TRAVIS_BUILD_DIR}
  wget http://ftp.de.debian.org/debian/pool/main/l/lcov/lcov_1.11.orig.tar.gz
  tar xf lcov_1.11.orig.tar.gz
  sudo make -C lcov-1.11/ install
  gem install coveralls-lcov
  cd ${TRAVIS_BUILD_DIR}
  lcov --directory . --zerocounters
fi
