#!/usr/bin/env bash

function install_linux {
	sudo apt-get -qq install --force-yes $*
}

function defCXX {
	export CC="$1"
	export CXX="$2"
}

function keep_waiting() {
  while true; do
    echo -e "."
    sleep 60
  done
}
