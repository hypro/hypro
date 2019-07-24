#!/bin/bash

declare -i tout=90
declare -a bench=(1 2 3 4 5 6 7 8 9 10)
declare -a diffic=(1 2 3)
declare -a th=(4 100 4 4 4 20 10 0.3 2 12)

for d in ${diffic[@]}
do
	for b in ${bench[@]}
	do
		timeH=${th[$b-1]}
		timeout $tout matlab -r "compareMHyProAndCORA($b,$timeH,$d);exit;" -sd /home/marta/hypro/src/hypro/util/matlab
	done
done
