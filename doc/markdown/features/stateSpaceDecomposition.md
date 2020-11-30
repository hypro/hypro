# General approach/assumptions for analysis
* The analyzer gets the decomposed automaton and the decomposition which contains the dynamic types on initialization
* The automaton is assumed to have a clock as the last variable in all but the linear/affine and 
  discrete subspaces (can be realized with function `addClockToAutomaton`)
* The analyzer uses a vector of `workerVariant`. The workers compute independently on the subspaces and the analyzer synchronizes
  using the clocks and by counting segments in the `LTI` case

# Time elapse
### General idea
1. Compute time elapse independently for all subspaces and extract the time interval where
  the invariant is satisfied
2. Remove all states/segments that lie outside this time interval

### Step 1 for subspaces with clock (singular/rectangular-worker)
* The worker computes 2 segments, where the second one contains all reachable states
* By maximizing/minimizing the second segment on the last variable, we get the time interval
  where the invariant is satisfied

### Step 1 for subspaces without clock (LTIWorker)
* Let the worker compute the segments
* Each segment corresponds to a time interval of size `timeStep`. To get the global time, we need
  to add the initial timing offset of the `ReachTreeNode`
* If `node->getTimings() = [a,b]`, the `n`-th segments corresponds to a time interval of
  `[a*fixedTimeStep + n*timeStep, b*fixedTimeStep + n*timeStep]`, so by counting the segments
  we can get the covered time interval.

### Step 2 for subspaces with clock
* Convert each segment to `HPolytope`, add the clock constraints and convert back. This should not give any empty
  segments, because both segments contain the initial clock value, at which point the invariants
  should be satisfied in all subspaces (otherwise the jump would not have been taken)

### Step 2 for subspaces without clock
* The initial segments should satisfy the invariant (otherwise the jump would not have been taken),
  so we throw away a tail of segments
* Let `[t1, t2]` be the time interval where all invariants are satisfied and `[a,b] = node->getTimings()`.
  Then the last segment to keep (which has non empty time intersection with `[t1,t2]`) is
  `ceil((t2 - a*fixedTimeStep ) / timeStep)`.
* Similarly, the first segment to keep would be `floor((t1 - b*fixedTimeStep ) / timeStep)`,
  but that should be `0`.


# Checking safety
### General idea
1. Intersect each subspace with its bad states and get the time interval of the intersection
  (subspaces that have no bad states should be ignored)
2. If the intersection of the extracted time intervals is nonempty, the system is unsafe

# Jumps
### General idea
1. For each transition get the enabled time intervals (as intersection) in a similar way as for bad states
2. If an interval is nonempty, intersect the guard-satisfying segments with the time interval
  (as in time elapse) and let the workers compute the jump successors

### Notes:
* For one transition there can be multiple time intervals where the guard is enabled, these
  should be handled individually.