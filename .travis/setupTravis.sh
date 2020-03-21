#!/usr/bin/env bash

source functions.sh

if [[ ${TRAVIS_OS_NAME} == "linux" ]]; then

	source setupLinux.sh

elif [[ ${TRAVIS_OS_NAME} == "osx" ]]; then

	source setupOsx.sh

fi

mkdir -p build
pushd build
	git clone --branch 19.01 --depth 1 https://github.com/smtrat/carl.git
	#git clone --depth 1 https://github.com/smtrat/carl.git
	pushd carl
		mkdir -p build
		pushd build && cmake -DCMAKE_CXX_COMPILER=$COMPILER -DCMAKE_BUILD_TYPE=Release ..
			keep_waiting &
			make resources || return 1
			kill $!
			make carl VERBOSE=1 || return 1
		popd
	popd
popd

