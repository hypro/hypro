function BouncingBallTest

% Create Automaton
automaton = MHyProHAutomaton();
loc = MHyProLocation();
tran = MHyProTransition();
reset = MHyProReset();
guard = MHyProCondition();

%-----------------------------------------------%
%                 loc loc_1
%-----------------------------------------------%

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
% x = 0 or v >= 0
guardMatrix = [1 0; -1 0; 0 -1];
guardVector = [0;0;0];
guard.setMatrix(guardMatrix); % First set the matrix then the vector!?
guard.setVector(guardVector);

% Set reset
% x:= x v:= -0.9v
constReset = [0;0];
linReset = [1 0; 0 -0.9];
reset.setMatrix(linReset);
reset.setVector(constReset);

l = automaton.addLocation(loc);

%-----------------------------------------------%
%                loc -> loc
%-----------------------------------------------%

% Setup transition
%tran.setAggregation(0);
tran.setGuard(guard);
tran.setSource(l);
tran.setTarget(l);
tran.setReset(reset);
tran.setLabels({MHyProLabel('t1')});

l.addTransition(tran);

%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% Create initial set
% x = [10, 10.2] v = 0
boxVector = [10.2; -10; 0; 0];
boxMatrix = [1 0; -1 0; 0 1; 0 -1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(l, initialCond);


%-----------------------------------------------%
%                 Bad States
%-----------------------------------------------%

% unsafe: x >= 10.7

badState = MHyProCondition();
badState.setMatrix([-1 0]);
badState.setVector(-10.7);
badStates(1).loc = l;
badStates(1).cond = badState;

automaton.setLocalBadStates(badStates);

%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

settings = struct('timeStep', 0.01, 'timeBound', 20, 'jumpDepth', 20);
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
