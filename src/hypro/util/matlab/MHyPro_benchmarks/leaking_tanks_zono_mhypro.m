function leaking_tanks_zono_mhypro()

% Create Automaton
automaton = MHyProHAutomaton();

%-----------------------------------------------%
%                 loc refill t1
%-----------------------------------------------%
loc_t1 = MHyProLocation();
loc_t1.setName('loc_t1');

% Set flow:
% h1' = 1.5 h2' = -1.5 t' = 1
flowMatrix = [0 0 0 1.5; 0 0 0 -1.5;0 0 0 1; 0 0 0 0];
loc_t1.setFlow(flowMatrix);

% Set invariant
% 0 <= h1 <= 10 & 0 <= h2
inv = MHyProCondition([-1 0 0; 1 0 0; 0 -1 0], [0;10;0]);
loc_t1.setInvariant(inv);

%-----------------------------------------------%
%                 loc refill t2
%-----------------------------------------------%
loc_t2 = MHyProLocation();
loc_t2.setName('loc_t2');

% Set flow:
% h1' = -2.5 h2' = 2.5 t' = 1
flowMatrix = [0 0 0 -2.5; 0 0 0 2.5;0 0 0 1; 0 0 0 0];
loc_t2.setFlow(flowMatrix);

% Set invariant
% 0 <= h1  & 0 <= h2 <= 10
inv = MHyProCondition([-1 0 0; 0 1 0; 0 -1 0], [0;10;0]);
loc_t2.setInvariant(inv);

t1 = automaton.addLocation(loc_t1);
t2 = automaton.addLocation(loc_t2);

%-----------------------------------------------%
%                t1 -> t2
%-----------------------------------------------%
tran1 = MHyProTransition();
% Set guard:
% t >= 0
guard1 = MHyProCondition();
guard1.setMatrix([ 0 0 -1]); 
guard1.setVector(0);

% Set reset
reset = MHyProReset();
reset.setMatrix([1 0 0; 0 1 0; 0 0 0]);
reset.setVector([0;0;0]);

tran1.setAggregation(0);
tran1.setGuard(guard1);
tran1.setSource(t1);
tran1.setTarget(t2);
tran1.setReset(reset);
tran1.setLabels({MHyProLabel('t1')});

t1.addTransition(tran1);

%-----------------------------------------------%
%                t2 -> t1
%-----------------------------------------------%
tran2 = MHyProTransition();
% Set guard:
% t >= 0
guard2 = MHyProCondition();
guard2.setMatrix([ 0 0 -1]); 
guard2.setVector(0);

tran2.setAggregation(0);
tran2.setGuard(guard1);
tran2.setSource(t2);
tran2.setTarget(t1);
tran2.setReset(reset);
tran2.setLabels({MHyProLabel('t2')});

t2.addTransition(tran2);

%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% Create initial set
% h1 = h2 = 5 t = 0
boxVector = [-5; 5; 5; -5; 0; 0];
boxMatrix = [-1 0 0; 1 0 0; 0 1 0; 0 -1 0; 0 0 -1; 0 0 1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(t1, initialCond);


%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

% Add basic settings
settings.timeBound = 3;
settings.jumpDepth = 2;
settings.timeStep = 0.1;
settings.clustering = -1;

reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(0);

tic;
flowpipes = reach.computeForwardReachability();

dim = [3 1];
labs = ["t", "h1"];
ext = 'png';
reach.plot(flowpipes, dim, labs,0,'','',ext);

