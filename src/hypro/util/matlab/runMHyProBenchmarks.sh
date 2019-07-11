#!/bin/bash

declare -i tout=120

# bouncing ball - standard strategy: 1
timeout $tout matlab -nodisplay -nosplash -r "runMHyProWithStrategy(1,0)" -sd /home/marta/hypro/src/hypro/util/matlab

# cruise control - standard strategy: 2
timeout $tout matlab -nodisplay -nosplash -r "runMHyProWithStrategy(2,2)" -sd /home/marta/hypro/src/hypro/util/matlab

# filtered oscillator 4 - standard strategy: 3
timeout $tout matlab -nodisplay -nosplash -r "runMHyProWithStrategy(3,3)" -sd /home/marta/hypro/src/hypro/util/matlab

# filtered oscillator 8 - standard strategy: 3
timeout $tout matlab -nodisplay -nosplash -r "runMHyProWithStrategy(4,3)" -sd /home/marta/hypro/src/hypro/util/matlab

# filtered oscillator 16 - standard strategy: 3
timeout $tout matlab -nodisplay -nosplash -r "runMHyProWithStrategy(5,3)" -sd /home/marta/hypro/src/hypro/util/matlab

# linear switching system - standard strategy: 4
timeout $tout matlab -nodisplay -nosplash -r "runMHyProWithStrategy(6,4)" -sd /home/marta/hypro/src/hypro/util/matlab

# rendezvous - standard strategy: 1
timeout $tout matlab -nodisplay -nosplash -r "runMHyProWithStrategy(7,1)" -sd /home/marta/hypro/src/hypro/util/matlab

# rod reactor - standard strategy: 1
timeout $tout matlab -nodisplay -nosplash -r "runMHyProWithStrategy(8,1)" -sd /home/marta/hypro/src/hypro/util/matlab

# two tanks - standard strategy: 1
timeout $tout matlab -nodisplay -nosplash -r "runMHyProWithStrategy(9,1)" -sd /home/marta/hypro/src/hypro/util/matlab

# vehicle platoon - standard strategy: 5
timeout $tout matlab -nodisplay -nosplash -r "runMHyProWithStrategy(10,5)" -sd /home/marta/hypro/src/hypro/util/matlab

done

