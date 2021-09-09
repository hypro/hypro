#!/bin/bash

# With this file all cora benchmarks can be run automatically.
# The arr array contains all strategies that should be tested.
# the bench array contains all numbers of benchmarks that should
# be tested. The numbering is equal as in the runCORABenchmarks.m
# file specificated.

declare -a arr=("1" "2" "3" "4" "5" "6" "7" "8" "9" "10" "11" "12" "13" "14" "15" "16" "17" "18" "19" "20" "21" "22" "23" "24" "25" "26" "27" "28" "29" "30" "31" "32" "33" "34" "35" "36")
declare -a bench=("1" "3" "4" "5" "6" "7" "8" "9" "10")


# This loop runs all benchmarks with easy specifications. Timeout is set to 105 seconds.
for b in "${bench[@]}"
do
	for i in "${arr[@]}"
	do
		echo "strategy: $i"
		echo "benchmark: $b"
		echo "difficulty: 1"
		timeout 105 matlab -minimize -r "runCORABenchmarks($b,1,$i);exit;" -sd /home/marta/hypro/src/hypro/util/matlab
	done
done

# This loop runs all benchmarks with hard specifications. Timeout is set to 195 seconds.
for b in "${bench[@]}"
do
	for i in "${arr[@]}"
	do
		echo "strategy: $i"
		echo "benchmark: $b"
		echo "difficulty: 3"
		timeout 195 matlab -minimize -r "runCORABenchmarks($b,3,$i);exit;" -sd /home/marta/hypro/src/hypro/util/matlab
	done
done

