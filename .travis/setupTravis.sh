#!/usr/bin/env bash

if [[ ${TRAVIS_OS_NAME} == "linux" ]]; then

	source setupLinux.sh

elif [[ ${TRAVIS_OS_NAME} == "osx" ]]; then

	source setupOsx.sh

fi
