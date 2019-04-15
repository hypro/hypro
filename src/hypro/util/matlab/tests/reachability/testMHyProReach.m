function res = testMHyProReach

% Create Automaton
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
tran.setLabels({MHyProLabel('t1')});
loc.addTransition(tran);

% Create initial set
boxVector = [10.2; -10; 0; 0];
boxMatrix = [1 0; -1 0; 0 1; 0 -1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(loc, initialCond);

automaton.addLocation(loc);

% Reachability

settings = struct('timeStep', 0.01, 'timeBound', 20, 'jumpDepth', 3);
reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(0);

loc = automaton.getLocations();
tran = loc{1}.getTransitions();
for i = 1:length(tran)
    labs = tran{i}.getLabels();
    name = labs{1}.getName();
    assert(isequal(name, 't1'));
end

flowpipes = reach.computeForwardReachability();

num_flowpipes = length(flowpipes);
for pipe = 1:num_flowpipes
    currentStates =  flowpipes{pipe}
    num_states = length(currentStates);
end



res = 1;