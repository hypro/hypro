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
# first remove version 1.71.0 which is currently installed (apparently)
brew uninstall --ignore-dependencies boost

# note: probably it is sufficient to just remove boost 1.71.0, as Carl maybe ships boost 1.69.0
#wget https://dl.bintray.com/boostorg/release/1.65.1/source/boost_1_65_1.tar.gz
#tar -xzf boost_1_65_1.tar.gz
#cd boost_1_65_1
#mkdir build
#./bootstrap.sh --with-libraries=chrono,system,program_options,test,timer --prefix=build
#keep_waiting &
#		./b2 -d0 || return 1
#kill $!
#keep_waiting &
#		./b2 install || return 1
#kill $!
