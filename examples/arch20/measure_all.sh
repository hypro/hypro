#!/bin/bash
TOOL_PATH=../../build/bin/hydra

run_benchmark() {
    if [[ ! -p mypipe ]]; then
        mkfifo mypipe
    fi

    # run tool, parse command line output
    echo "Execute benchmark $2, instance $3 ..."
    $TOOL_PATH $1 > mypipe &
    while IFS= read -r line
    do
        [[ $line =~ 'Verification took '([0-9]*\.[0-9]*)'s' ]] && runningTime=${BASH_REMATCH[1]}
        [[ $line =~ 'The model is safe' ]] && safe=${BASH_REMATCH[0]}
    done < mypipe
    echo "Done."
    if [[ $safe ]]
    then
        safestring="1"
    else
        safestring="0"
    fi
    result="HyDRA,$2,$3,$safestring,$runningTime"
}

#clear results file
> results_hydra.csv

run_benchmark '-m aff/BLDC01-BDS01.model -d 1/250 -r support_function --setting SupportFunctionSetting --plotoutputformat eps' 'BLDC01' 'BLDS01'
echo $result >> results_hydra.csv

run_benchmark '-m aff/BLDC01-BDS01.model -d 1/250 -t 1 -r support_function --setting SupportFunctionSetting --plotoutputformat eps --plotoutput BLDC01_BDS01_1sek' 'BLDC01' 'BLDS01_1sek'
echo $result >> results_hydra.csv

run_benchmark '-m aff/PLAD01_BND42.model -d 1/4 -r support_function --setting SupportFunctionSetting --plotoutputformat eps' 'PLAD01' 'BND42'
echo $result >> results_hydra.csv

run_benchmark '-m aff/PLAD01_BND30.model -d 1/4 -r support_function --setting NoBoxReduction --plotoutputformat eps' 'PLAD01' 'BND30'
echo $result >> results_hydra.csv

run_benchmark '-m aff/heat_5.model -d 1/35 -t 40 -r SFN --setting SupportFunctionNewDefault --plotoutputformat eps' 'HEAT3D' 'HEAT01'
echo $result >> results_hydra.csv

run_benchmark '-m aff/heat_10.model -d 1/75 -t 40 -r SFN --setting SupportFunctionNewDefault --plotoutputformat eps' 'HEAT3D' 'HEAT02'
echo $result >> results_hydra.csv

echo "All benchmarks run"

