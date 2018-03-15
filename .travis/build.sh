#!/usr/bin/env bash

mkdir -p build || return 1
cd build || return 1

cmake ../ || return 1

if [[ ${TASK} == "sonarcloud" ]]; then
	cmake ../ || return 1
	W="build-wrapper-linux-x86-64 --out-dir=../bw-out"
	$W make -j4 hypro || return 1
	$W make -j4 || return
	#make coverage-collect

	cd ../ && sonar-scanner -X -Dproject.settings=.travis/sonar-project.properties && cd build/

else
	cmake -j4 $FLAGS -DCMAKE_CXX_COMPILER=$COMPILER ..
	make resources -j2
	make -j4 VERBOSE=1
	make test

fi



