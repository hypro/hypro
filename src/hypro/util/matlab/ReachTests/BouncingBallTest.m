function BouncingBallTest

% Create Automaton
automaton = MHyProHAutomaton();
loc = MHyProLocation();
tran = MHyProTransition();
reset = MHyProReset();
guard = MHyProCondition();

% Set invariant x >= 0
inv_mat = [-1 0];
inv_vec = 0;
inv = MHyProCondition(inv_mat, inv_vec);
loc.setInvariant(inv);
loc.setName('loc1');

% Set flow:
% x' = v v' = -9.81
flowMatrix = [0 1 0; 0 0 -9.81; 0 0 0];
loc.setFlow(flowMatrix);

% Set guard:
% x = 0 or v > 0
guardMatrix = [1 0; -1 0; 0 1];
guardVector = [0;0;0];
guard.setMatrix(guardMatrix); % First set the matrix then the vector!?
guard.setVector(guardVector);

% Set reset
% x:= x v:= -0.9v
constReset = [0; 0];
linReset = [1 0; 0 -0.9];
reset.setMatrix(linReset);
reset.setVector(constReset);

% Setup transition
%tran.setAggregation(0);
tran.setGuard(guard);
tran.setSource(loc);
tran.setTarget(loc);
tran.setReset(reset);
tran.setLabels({MHyProLabel('t1')});

loc.addTransition(tran);

% Create initial set
% x = [10, 10.2] v = 0
boxVector = [10.2; -10; 0; 0];
boxMatrix = [1 0; -1 0; 0 1; 0 -1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(loc, initialCond);
automaton.addLocation(loc);

% Reachability

settings = struct('timeStep', 0.01, 'timeBound', 3.2, 'jumpDepth', 2);
reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(0);
reach.settings();

tic;
flowpipes = reach.computeForwardReachability();
time = toc;
disp(['Time needed: ', num2str(time)]);
dim = [1 2];
reach.plot(flowpipes, dim);
end
