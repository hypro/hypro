function mhypro_zeno

% Create Automaton
automaton = MHyProHAutomaton();

%-----------------------------------------------%
%                 loc_1
%-----------------------------------------------%
loc1 = MHyProLocation();
loc1.setName('loc1');

% Set flow:
% h1' = 2 h2' = -2 t' = 1
flowMatrix = [0 0 0 2; 0 0 0 -2; 0 0 0 1; 0 0 0 0];
loc1.setFlow(flowMatrix);

% Set invariant 0 <= h1 <= max 0 <= h2
inv = MHyProCondition([-1 0 0; 1 0 0; 0 -1 0], [0;5;0]);
loc1.setInvariant(inv);

%-----------------------------------------------%
%                 loc_2
%-----------------------------------------------%
loc2 = MHyProLocation();
loc2.setName('loc2');

% Set flow:
% h1' = -1 h2' = 1 t' = 1
flowMatrix = [0 0 0 -1; 0 0 0 1; 0 0 0 1; 0 0 0 0];
loc2.setFlow(flowMatrix);

% Set invariant 0 <= h2 <= max 0 <= h1
inv = MHyProCondition([-1 0 0; 0 1 0; 0 -1 0], [0;5;0]);
loc2.setInvariant(inv);

l1 = automaton.addLocation(loc1);
l2 = automaton.addLocation(loc2);

%-----------------------------------------------%
%                loc_1 -> loc_2
%-----------------------------------------------%
tran1 = MHyProTransition();
% Set guard:
% t >= 0
guard1 = MHyProCondition();
guard1.setMatrix([ 0 0 -1]);
guard1.setVector(0);

% Set reset t:= 0
reset1 = MHyProReset();
reset1.setMatrix([1 0 0; 0 1 0; 0 0 0]);
reset1.setVector([0;0;0]);

tran1.setAggregation(1);
tran1.setGuard(guard1);
tran1.setSource(l1);
tran1.setTarget(l2);
tran1.setReset(reset1);
tran1.setLabels({MHyProLabel('t1')});

l1.addTransition(tran1);

%-----------------------------------------------%
%                loc_2 -> loc_1
%-----------------------------------------------%
tran2 = MHyProTransition();
% Set guard:
% t >= 0

% Set reset t:= 0

tran2.setAggregation(1);
tran2.setGuard(guard1);
tran2.setSource(l2);
tran2.setTarget(l1);
tran2.setReset(reset1);
tran2.setLabels({MHyProLabel('t2')});

l2.addTransition(tran2);

%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% Create initial set
% h1 = h2 = [1.9; 2.1] t = 0
boxVector = [-1.9; 2.1; -1.9; 2.1; 0; 0];
boxMatrix = [-1 0 0; 1 0 0; 0 -1 0; 0 1 0; 0 0 -1; 0 0 1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(l1, initialCond);

%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

% Add basic settings
settings.timeBound = 1;
%settings.jumpDepth = 10;
settings.timeStep = 0.1;

reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(0);

tic;
flowpipes = reach.computeForwardReachability();

end