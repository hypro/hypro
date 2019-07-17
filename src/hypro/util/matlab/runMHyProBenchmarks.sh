#!/bin/bash

declare -i tout=90
declare -a bench=("3" "4" "5" "6" "7" "8" "9" "10")
declare -a arr=("31" "32" "33" "34" "35" "36" "37" "38" "39" "40" "41" "42" "43" "44" "45" "46" "47" "48" "49" "50" "51" "52" "53" "54" "55" "56" "57" "58" "59" "60")
#"1" "2" "3" "4" "5" "10" "11" "12" "13" "14" "15" "16" "17" "18" "19" "20" "21" "22" "23" "24" "25" "26" "27" "28" "29" "30"
declare -a diffic=("0" "1" "2")

for d in "${diffic[@]}"
do
	for b in "${bench[@]}"
	do
		for i in "${arr[@]}"
		do
			echo "strategy: $i"
			echo "benchmark: $b"
			echo "difficulty: $d"
			timeout $tout matlab -minimize -r "runMHyProAllStrategies($b,$d,$i);exit;" -sd /home/marta/hypro/src/hypro/util/matlab
		done
	done
done
