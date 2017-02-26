#!/usr/bin/env bash

set -ev

brew update --quiet
brew install doxygen eigen llvm
#brew cask install mactex

if [[ ${COMPILER} == "g++-4.8" ]]; then
	echo "g++-4.8 is not supported"
	#install gcc-4.8 g++-4.8
	#defCXX gcc-4.8 g++-4.8
elif [[ ${COMPILER} == "g++-4.9" ]]; then
	brew install gcc
	defCXX gcc-4.9 g++-4.9
elif [[ ${COMPILER} == "clang++-3.4" ]]; then
	echo "clang++-3.4 is not supported"
	#install clang-3.4
	#defCXX clang-3.4 clang++-3.4
elif [[ ${COMPILER} == "clang++-3.5" ]]; then
	defCXX clang clang++
fi
