#!/usr/bin/env bash
#set -ev

function keep_waiting() {
  while true; do
    echo -e "."
    sleep 60
  done
}

if [[ ${COMPILER} == "g++-4.8" ]]; then
	echo "g++-4.8 is not supported"
elif [[ ${COMPILER} == "g++-5" ]]; then
	brew install gcc@5
	brew link --overwrite gcc@5
fi
