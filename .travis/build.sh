#!/usr/bin/env bash

mkdir -p build

pushd build

if [[ ${TASK} == "sonarcloud" ]]; then
	echo "Building with build wrapper."
	cmake ../ -DHYPRO_COVERAGE=ON -DCMAKE_CXX_COMPILER=$COMPILER || return 1
	build-wrapper-linux-x86-64 --out-dir bw-outputs make hypro_coverage -j4 || return 1
	#$WRAPPER make hypro_coverage -j4 || return 1
	#lcov --directory . --capture --no-external --output-file coverage.info # capture coverage info
	#lcov --remove hypro_coverage.info 'test/*' '/usr/*' '*/carl/*' '*/parser/*' --output-file hypro_coverage.info # filter out system and test code
	#lcov --list hypro_coverage.info # debug before upload

	cd ../ && sonar-scanner -X -Dproject.settings=.travis/sonar-project.properties && cd build/

elif [[ ${TASK} == "clang-sanitizer" ]]; then
	cmake ../ -DDEVELOPER=ON -DCMAKE_CXX_COMPILER=$COMPILER || return 1
	make resources -j2 || return 1
	keep_waiting &
	make -j2 VERBOSE=1 || return 1
	keep_waiting &
	make example_reachability -j2 VERBOSE=1 || return 1
	kill $!
	make test
	./../.travis/runSanitizedTests.sh
else
	cmake -DCMAKE_CXX_COMPILER=$COMPILER ..
	make resources -j2 || return 1
	keep_waiting &
	make -j2 VERBOSE=1 || return 1
	kill $!
	make test
fi

popd