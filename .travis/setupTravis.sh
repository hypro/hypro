#!/usr/bin/env bash

source functions.sh

if [[ ${TRAVIS_OS_NAME} == "linux" ]]; then

	source setupLinux.sh

elif [[ ${TRAVIS_OS_NAME} == "osx" ]]; then

	source setupOsx.sh

fi
