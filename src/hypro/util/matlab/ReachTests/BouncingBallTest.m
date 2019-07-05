function BouncingBallTest

% Create Automaton
automaton = MHyProHAutomaton();

%-----------------------------------------------%
%                 loc loc_1
%-----------------------------------------------%
loc = MHyProLocation();
loc.setName('loc');

% Set flow:
% x' = v v' = -9.81
flowMatrix = [0 1 0; 0 0 -9.81;0 0 0];
loc.setFlow(flowMatrix);

% Set invariant x >= 0
inv = MHyProCondition([-1 0], 0);
loc.setInvariant(inv);


l = automaton.addLocation(loc);

%-----------------------------------------------%
%                loc -> loc
%-----------------------------------------------%
tran = MHyProTransition();
% Set guard:
% x = 0 or v >= 0
guard = MHyProCondition();
guard.setMatrix([ -1 0; 0 -1]); % First set the matrix then the vector!?
guard.setVector([0;0]);

% Set reset
% x:= x v:= -0.75v
reset = MHyProReset();
reset.setMatrix([1 0; 0 -0.75]);
reset.setVector([0;0]);

tran.setAggregation(0);
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
boxVector = [-10; 10.2; 0; 0];
boxMatrix = [-1 0; 1 0; 0 1; 0 -1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(l, initialCond);


%-----------------------------------------------%
%                 Bad States
%-----------------------------------------------%

% unsafe: x >= 10.7

% badState = MHyProCondition();
% badState.setMatrix([-1 0]);
% badState.setVector(-10.7);
% badStates(1).loc = l;
% badStates(1).cond = badState;

% automaton.setLocalBadStates(badStates);

%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

settings = struct('timeStep', 0.01, 'timeBound', 40, 'jumpDepth', 20);
reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(2);
reach.settings();

tic;
flowpipes = reach.computeForwardReachability();
time = toc;
disp(['Time needed: ', num2str(time)]);
dim = [1 2];
labs = ["x", "v"];
reach.plot(flowpipes, dim, labs);
end
