#!/usr/bin/env bash
#set -ev

function keep_waiting() {
  while true; do
    echo -e "."
    sleep 60
  done
}

if [[ ${COMPILER} == "g++-4.8" ]]; then
	echo "g++-4.8 is not supported"
elif [[ ${COMPILER} == "g++-5" ]]; then
	brew install gcc@5
	brew link --overwrite gcc@5
fi

# boost <= 1.70 is currently required until we can use a newer version of CArL which supports osx.
wget https://dl.bintray.com/boostorg/release/1.65.1/source/boost_1_65_1.tar.gz
tar -xzf boost_1_65_1.tar.gz
cd boost_1_65_1
./bootstrap.sh
./b2
./b2 install
