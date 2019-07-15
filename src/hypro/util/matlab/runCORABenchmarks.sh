#!/bin/bash

declare -i tout=135
declare -a bench=("9")
declare -a arr=("1" "2" "3" "4" "5" "6" "7" "8" "9" "10" "11" "12" "13" "14" "15" "16" "17" "18" "19" "20" "21" "22");
#declare -a diffic=("0" "1" "2" "3")
declare -a diffic=("3")

for d in "${diffic[@]}"
do
	for b in "${bench[@]}"
	do
		for i in "${arr[@]}"
		do
			echo "strategy: $i"
			echo "benchmark: $b"
			echo "difficulty: $d"
			timeout $tout matlab -minimize -r "runCORABenchmarks($b,$d,$i);exit;" -sd /home/marta/hypro/src/hypro/util/matlab
		done
	done
done
