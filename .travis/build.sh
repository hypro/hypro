#!/usr/bin/env bash

mkdir -p build || return 1
cd build || return 1

cmake ../ || return 1

function keep_waiting() {
  while true; do
    echo -e "."
    sleep 60
  done
}


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
	git clone https://github.com/smtrat/carl.git
	cd carl && mkdir build && cd build && cmake -DCMAKE_CXX_COMPILER=$COMPILER -DCMAKE_BUILD_TYPE=Release .. && make resources
	keep_waiting &
	make lib_carl VERBOSE=1 || return 1
	kill $!
	cmake -j4 $FLAGS -DCMAKE_CXX_COMPILER=$COMPILER ..
	keep_waiting &
	make resources -j2 || return 1
	kill $!
	make -j4 VERBOSE=1
	make test

fi



