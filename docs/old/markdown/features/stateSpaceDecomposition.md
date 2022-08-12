# General approach/assumptions for analysis

* The analyzer gets the decomposed automaton and the decomposition which contains the dynamic types on initialization
* The automaton is assumed to have a clock as the last variable in all but the linear/affine and
  discrete subspaces (can be realized with function `addClockToAutomaton`)
* The analyzer uses a vector of `workerVariant`. The workers compute independently on the subspaces and the analyzer
  synchronizes
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

* Iterate over the local and global bad states
* For each bad state, first get the bad time intervals for the singular/rectangular/timed subspaces
  (These should really be intervals) and intersect them
* From this interval determine the segments to check in the other subspaces (i.e. build index set)
* For each LTI subspace intersect each segment with the bad state and if the intersection is empty,
  remove the segment-index from the index set.
* If at the end the index set is not empty, the system is unsafe.

# Jumps

### General idea (Do for each transition)

* Iterate over singular/timed/rectangular subspaces first
* For each of these subspaces compute the guard-intersection, the reset and the intersection with the
  new invariant. From this we get a time interval, where the jump is possible in the singular subspaces
* To handle the lti subspaces first get the segments that are within this time interval and also satisfy the guard (
  guard intersection)
* Perform aggregation and reset with the segments. If (aggregated sets of) reset segments don't satisfy
  the new invariant, drop the corresponding indices and segments in *all* lti-subspaces
* We end up with a list of segment indices (intervals if aggregated), where the guard+invariant is satisfied
  in all subspaces
* For each of these intersect the singular subspaces with the corresponding time interval and add them
  all together as a child node

### Notes:

* It can happen that in the child node the segment covers a time of e.g. [1.0, 1.2] but the singular
  subspaces were intersected with the time interval [1.1, 1.2]. However the singular time interval
  will be a subset of the segment-time interval and after the next time elapse it is still guaranteed
  that the first segment should be kept.