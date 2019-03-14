function res = testMHyProHAutomaton
% Automaton for bouncing ball

automaton = MHyProHAutomaton();
loc = MHyProLocation();
tran = MHyProTransition();
reset = MHyProReset();
guard = MHyProCondition();

% Set invariant
inv_mat = [-1 0];
inv_vec = 0;
inv = MHyProCondition(inv_mat, inv_vec);
loc.setInvariant(inv);

% Set flow
flowMatrix = [0 1 0; 0 0 -9.81; 0 0 0];
loc.setFlow(flowMatrix);

% Set guard
guardVector = [0;0;0];
guardMatrix = [1 0; -1 0; 0 1];
guard.setMatrix(guardMatrix); % First set the matrix then the vector!?
guard.setVector(guardVector);


% Set reset
constReset = [0; 0];
linReset = [1 0; 0 -0.9];
reset.setMatrix(linReset);
reset.setVector(constReset);


% Setup transition
tran.setAggregation('parallelotopeAgg');
tran.setGuard(guard);
tran.setSource(loc);
tran.setTarget(loc);
tran.setReset(reset);
loc.addTransition(tran);

% Create initial set
boxVector = [10.2; -10; 0; 0];
boxMatrix = [1 0; -1 0; 0 1; 0 -1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(loc, initialCond);

automaton.addLocation(loc);










% automaton_locs_init 






res = 1;