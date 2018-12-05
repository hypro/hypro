#!/usr/bin/env bash
#set -ev
brew update --quiet
brew update cmake
brew install llvm

if [[ ${COMPILER} == "g++-4.8" ]]; then
	echo "g++-4.8 is not supported"
elif [[ ${COMPILER} == "g++-4.9" ]]; then
	brew install gcc
	defCXX gcc-4.9 g++-4.9
elif [[ ${COMPILER} == "clang++-3.4" ]]; then
	echo "clang++-3.4 is not supported"
elif [[ ${COMPILER} == "clang++" ]]; then
	defCXX clang clang++
fi
