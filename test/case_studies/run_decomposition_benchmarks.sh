#!/bin/bash
#
# Copyright (c) 2021.
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Please provide the (absolute) path to hydra and the base path (with trailing slash) to the benchmark folder."
    exit 1
fi

HYDRA=$1 #path to hydra
BMPATH=$2 #base path of the benchmarks
TIMEOUT=1200
MEMOUT=8388608

#switch to base path
pushd ${BMPATH}

#enable benchmark settings
NOAGG=1
AGG=1
COMPOSED=1
DECOMPOSE=1


# args: $1(benchmark name) $2(hydra args) $3(expected result) $4(csv filename to write results)
run() {
    rm /tmp/hydrapipe 2>/dev/null
    killall -s SIGKILL hydra 2>/dev/null
    if [[ ! -p /tmp/hydrapipe ]]; then
        mkfifo /tmp/hydrapipe
    fi
    /usr/bin/timeout $TIMEOUT nice -n -5 taskset -c 0 $HYDRA $2 | tee benchmark.log -a > /tmp/hydrapipe &

    echo "Running $1"
    timestamp=`date +"%Y-%m-%d_%H-%M-%S"`

    result="unsafe"
    readingStats=false
    stats=""
    starttime=`date +%s.%N`
    while IFS= read -r line
    do
        if [[ $line == 'Timeout' ]]; then
            result="timeout"
        fi
        if [[ $line == 'The model is safe.' ]]; then
            result="safe"
        fi
        if [[ $line == 'Counters:' ]]; then
            readingStats=true
            continue
        fi
        if [[ $line == 'Timers:' ]]; then
            readingStats=true
            continue
        fi
        if [[ -z $line ]]; then
            readingStats=false
            continue
        fi
        if [[ "$readingStats" == true ]]; then
            stats="$stats,$line"
        fi
    done < /tmp/hydrapipe
    runtime=$( echo "`date +%s.%N` - $starttime" | bc -l )

    echo "$timestamp,$1,$3,$result,$runtime,$stats,$2" >> "$4"
    if [[ "$result" != "$3" ]]; then
        echo "Wrong result for $1. Expected $3 but analysis returned $result"
        FAILED+=("$1")
    fi
    rm /tmp/hydrapipe 2>/dev/null
    killall -s SIGKILL hydra 2>/dev/null
    sleep 10
}

FAILED=()
#####################
# put test cases here
#####################
if [[ $DECOMPOSE != 0 ]]; then
## aggregation 0
if [[ $AGG != 0 ]]; then
## leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer
run 'leaking_box_de_agg_0clocks_1sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_agg_1clocks_1sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 1 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_agg_2clocks_1sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 2 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_agg_3clocks_1sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 3 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_agg_4clocks_1sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 4 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_agg_0clocks_2sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_agg_1clocks_2sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 1 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_agg_2clocks_2sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 2 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_agg_3clocks_2sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 3 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_agg_4clocks_2sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 4 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_agg_0clocks_3sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_agg_1clocks_3sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 1 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_agg_2clocks_3sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 2 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_agg_3clocks_3sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 3 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_agg_4clocks_3sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 4 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_polytope_h_de_agg_0clocks_1sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_polytope_h_de_agg_0clocks_3sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_support_function_de_agg_0clocks_1sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_support_function_de_agg_0clocks_2sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_support_function_de_agg_0clocks_3sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'


# thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer
run 'thermostat_box_de_agg_0clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_box_de_agg_1clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 1 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_box_de_agg_2clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 2 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_box_de_agg_3clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 3 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_box_de_agg_4clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 4 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_box_de_agg_0clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_box_de_agg_1clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 1 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_box_de_agg_2clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 2 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_box_de_agg_3clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 3 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_box_de_agg_4clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 4 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_polytope_h_de_agg_0clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_polytope_h_de_agg_1clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting -a AGG -c 0 --clockCount 1 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_polytope_h_de_agg_2clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting -a AGG -c 0 --clockCount 2 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_polytope_h_de_agg_3clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting -a AGG -c 0 --clockCount 3 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_polytope_h_de_agg_4clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting -a AGG -c 0 --clockCount 4 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_polytope_h_de_agg_0clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_polytope_h_de_agg_1clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting -a AGG -c 0 --clockCount 1 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_polytope_h_de_agg_2clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting -a AGG -c 0 --clockCount 2 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_polytope_h_de_agg_3clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting -a AGG -c 0 --clockCount 3 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_polytope_h_de_agg_4clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting -a AGG -c 0 --clockCount 4 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_support_function_de_agg_0clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_support_function_de_agg_1clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting -a AGG -c 0 --clockCount 1 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_support_function_de_agg_2clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting -a AGG -c 0 --clockCount 2 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_support_function_de_agg_3clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting -a AGG -c 0 --clockCount 3 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_support_function_de_agg_4clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting -a AGG -c 0 --clockCount 4 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_support_function_de_agg_0clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_support_function_de_agg_1clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting -a AGG -c 0 --clockCount 1 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_support_function_de_agg_2clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting -a AGG -c 0 --clockCount 2 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_support_function_de_agg_3clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting -a AGG -c 0 --clockCount 3 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_support_function_de_agg_4clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting -a AGG -c 0 --clockCount 4 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'


# two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer
run 'two_box_de_agg_0clocks_1sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_1clocks_1sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 1 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_2clocks_1sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 2 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_3clocks_1sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 3 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_4clocks_1sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 4 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_0clocks_2sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_1clocks_2sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 1 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_2clocks_2sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 2 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_3clocks_2sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 3 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_4clocks_2sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 4 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_0clocks_3sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_1clocks_3sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 1 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_2clocks_3sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 2 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_3clocks_3sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 3 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_4clocks_3sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 4 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_0clocks_4sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 4 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_1clocks_4sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 1 --decompose --singularSubspaceSize 4 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_2clocks_4sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 2 --decompose --singularSubspaceSize 4 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_3clocks_4sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 3 --decompose --singularSubspaceSize 4 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_4clocks_4sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 4 --decompose --singularSubspaceSize 4 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_0clocks_5sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 5 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_1clocks_5sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 1 --decompose --singularSubspaceSize 5 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_2clocks_5sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 2 --decompose --singularSubspaceSize 5 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_3clocks_5sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 3 --decompose --singularSubspaceSize 5 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_agg_4clocks_5sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn -a AGG -c 0 --clockCount 4 --decompose --singularSubspaceSize 5 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_polytope_h_de_agg_0clocks_1sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_polytope_h_de_agg_0clocks_2sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_polytope_h_de_agg_0clocks_3sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_polytope_h_de_agg_0clocks_4sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 4 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_polytope_h_de_agg_0clocks_5sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 5 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_support_function_de_agg_0clocks_1sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_support_function_de_agg_0clocks_2sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_support_function_de_agg_0clocks_3sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_support_function_de_agg_0clocks_4sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 4 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_support_function_de_agg_0clocks_5sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting -a AGG -c 0 --clockCount 0 --decompose --singularSubspaceSize 5 --skipplot' 'safe' 'resultsDecompose.csv'


fi
# aggregation -1
if [[ $NOAGG != 0 ]]; then
# leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer
run 'leaking_box_de_noAgg_0clocks_1sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 0 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_noAgg_1clocks_1sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 1 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_noAgg_2clocks_1sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 2 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_noAgg_3clocks_1sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 3 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_noAgg_4clocks_1sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 4 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_noAgg_0clocks_2sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 0 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_noAgg_1clocks_2sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 1 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_noAgg_2clocks_2sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 2 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_noAgg_3clocks_2sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 3 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_noAgg_4clocks_2sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 4 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_noAgg_0clocks_3sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 0 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_noAgg_1clocks_3sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 1 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_noAgg_2clocks_3sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 2 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_noAgg_3clocks_3sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 3 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_box_de_noAgg_4clocks_3sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 4 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_polytope_h_de_noAgg_0clocks_1sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting --clockCount 0 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_polytope_h_de_noAgg_0clocks_2sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting --clockCount 0 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_polytope_h_de_noAgg_0clocks_3sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting --clockCount 0 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_support_function_de_noAgg_0clocks_1sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting --clockCount 0 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_support_function_de_noAgg_0clocks_2sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting --clockCount 0 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'leaking_support_function_de_noAgg_0clocks_3sing' '-m leaking_tank_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting --clockCount 0 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'


# thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer
run 'thermostat_box_de_noAgg_0clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 0 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_box_de_noAgg_1clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 1 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_box_de_noAgg_2clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 2 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_box_de_noAgg_3clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 3 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_box_de_noAgg_4clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 4 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_box_de_noAgg_0clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 0 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_box_de_noAgg_1clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 1 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_box_de_noAgg_2clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 2 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_box_de_noAgg_3clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 3 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_box_de_noAgg_4clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 4 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_polytope_h_de_noAgg_0clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting --clockCount 0 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_polytope_h_de_noAgg_1clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting --clockCount 1 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_polytope_h_de_noAgg_2clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting --clockCount 2 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_polytope_h_de_noAgg_3clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting --clockCount 3 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_polytope_h_de_noAgg_4clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting --clockCount 4 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_polytope_h_de_noAgg_0clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting --clockCount 0 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_polytope_h_de_noAgg_1clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting --clockCount 1 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_polytope_h_de_noAgg_2clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting --clockCount 2 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_polytope_h_de_noAgg_3clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting --clockCount 3 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_polytope_h_de_noAgg_4clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting --clockCount 4 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_support_function_de_noAgg_0clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting --clockCount 0 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_support_function_de_noAgg_1clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting --clockCount 1 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_support_function_de_noAgg_2clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting --clockCount 2 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_support_function_de_noAgg_3clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting --clockCount 3 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_support_function_de_noAgg_4clocks_1sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting --clockCount 4 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_support_function_de_noAgg_0clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting --clockCount 0 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_support_function_de_noAgg_1clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting --clockCount 1 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_support_function_de_noAgg_2clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting --clockCount 2 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_support_function_de_noAgg_3clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting --clockCount 3 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'thermostat_support_function_de_noAgg_4clocks_2sing' '-m thermostat_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting --clockCount 4 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'


# two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer
run 'two_box_de_noAgg_0clocks_1sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 0 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_1clocks_1sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 1 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_2clocks_1sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 2 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_3clocks_1sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 3 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_4clocks_1sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 4 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_0clocks_2sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 0 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_1clocks_2sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 1 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_2clocks_2sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 2 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_3clocks_2sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 3 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_4clocks_2sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 4 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_0clocks_3sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 0 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_1clocks_3sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 1 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_2clocks_3sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 2 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_3clocks_3sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 3 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_4clocks_3sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 4 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_0clocks_4sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 0 --decompose --singularSubspaceSize 4 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_1clocks_4sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 1 --decompose --singularSubspaceSize 4 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_2clocks_4sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 2 --decompose --singularSubspaceSize 4 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_3clocks_4sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 3 --decompose --singularSubspaceSize 4 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_4clocks_4sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 4 --decompose --singularSubspaceSize 4 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_0clocks_5sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 0 --decompose --singularSubspaceSize 5 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_1clocks_5sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 1 --decompose --singularSubspaceSize 5 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_2clocks_5sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 2 --decompose --singularSubspaceSize 5 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_3clocks_5sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 3 --decompose --singularSubspaceSize 5 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_box_de_noAgg_4clocks_5sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r box -s BoxLinearOptimizationOn --clockCount 4 --decompose --singularSubspaceSize 5 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_polytope_h_de_noAgg_0clocks_1sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting --clockCount 0 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_polytope_h_de_noAgg_0clocks_2sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting --clockCount 0 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_polytope_h_de_noAgg_0clocks_3sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting --clockCount 0 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_polytope_h_de_noAgg_0clocks_4sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting --clockCount 0 --decompose --singularSubspaceSize 4 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_polytope_h_de_noAgg_0clocks_5sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r polytope_h -s HPolytopeSetting --clockCount 0 --decompose --singularSubspaceSize 5 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_support_function_de_noAgg_0clocks_1sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting --clockCount 0 --decompose --singularSubspaceSize 1 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_support_function_de_noAgg_0clocks_2sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting --clockCount 0 --decompose --singularSubspaceSize 2 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_support_function_de_noAgg_0clocks_3sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting --clockCount 0 --decompose --singularSubspaceSize 3 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_support_function_de_noAgg_0clocks_4sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting --clockCount 0 --decompose --singularSubspaceSize 4 --skipplot' 'safe' 'resultsDecompose.csv'
run 'two_support_function_de_noAgg_0clocks_5sing' '-m two_tank_system_hypro_with_aggregation_separateControllerAndPlant_with_timer.model -r support_function -s SupportFunctionSetting --clockCount 0 --decompose --singularSubspaceSize 5 --skipplot' 'safe' 'resultsDecompose.csv'


fi
fi



echo "-------------------------"
FAILEDCOUNT=${#FAILED[@]}
if [[ $FAILEDCOUNT != 0 ]]; then
    echo "Failed $FAILEDCOUNT test cases:"
    printf '%s ' "${FAILED[@]}"
    echo ""
    echo "-------------------------"
else
    echo "No failed test cases"
fi


popd