This folder contains files needed for running benchmarks on mhypro. To run a benchmark the runMHyProBenchmarks.m has to be run with the following parameters:

   benchmarkNr: number of the benchmark
       1 - bouncing ball
       2 - cruise controll
       3 - filtered oscillator 4
       4 - filtered oscillator 8
       5 - filtered oscillator 16
       6 - switching system
       7 - spacecraft rendezvous
       8 - rod reactor
       9 - two tanks
      10 - vehicle platoon
   diff: difficulty of the specification
       1 - no specifications
       2 - easy specifications
   strategy: number of the strategy that should be used for the
             reachability analysis. The strategies can be found in
             the file getNewStrategy.m

This folder also contains additional file in the ParameterExperiments folder where each paramter can be set by hand in order to see the impact of the particular parameters on the reachability results.

The file leaking_tanks_zono_mhypro.m file contains a hybrid automaton modelliing the leaking tanks benchmark exhibiting zeno behaviour.
