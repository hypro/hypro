#!/usr/bin/env bash

#Checking tests and some examples with sanitizers. Failing if anything is written to stderr or non-zero is returned.
#llvm-sanitizer has to be available

function check() {
    #Redirects streams such that stderr is captured and stdout ends up back in stdout
    { erroutput="$($1 3>&2 2>&1 1>&3)"; } 2>&1

    if [ $? != 0 ] || [ -n "$erroutput" ]
    then
        echo ""
        echo "FAILURE! Errors encountered:"
        echo ""
        echo "$erroutput"
        exit 1
    fi
}

check "./bin/example_reachability ../examples/input/rod_reactor.model 1"
check "./bin/example_reachability ../examples/input/rod_reactor.model 3"

for target in ./bin/run*
do
    check "$target"
done

