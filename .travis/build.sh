#!/usr/bin/env bash

mkdir -p build || return 1
cd build || return 1

cmake ../ || return 1

if [[ ${TASK} == "sonarcloud" ]]; then
	cmake ../ -DHYPRO_COVERAGE=ON || return 1
	build-wrapper-linux-x86-64 --out-dir ../bw-out make -j4 hypro
	#make coverage-collect
	echo "This folder:"
	ls -la
	echo "Parent folder:"
	ls ../

	cd ../ && sonar-scanner -X -Dproject.settings=.travis/sonar-project.properties && cd build/

else
	cmake -j4 $FLAGS -DCMAKE_CXX_COMPILER=$COMPILER ..
	make resources -j2
	make -j4 VERBOSE=1
	make test

fi



