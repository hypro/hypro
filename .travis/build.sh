#!/usr/bin/env bash

mkdir -p build || return 1
cd build || return 1

cmake ../ || return 1

if [[ ${TASK} == "sonarcloud" ]]; then
	cmake ../ || return 1
	build-wrapper-linux-x86-64 --out-dir=../bw-out make clean hypro -j4 || return 1
	#make coverage-collect

	cd ../ && sonar-scanner -X -Dproject.settings=.travis/sonar-project.properties -Dsonar.login&& cd build/

else
	cmake -j4 $FLAGS -DCMAKE_CXX_COMPILER=$COMPILER ..
	make resources -j2
	make -j4 VERBOSE=1
	make test

fi



