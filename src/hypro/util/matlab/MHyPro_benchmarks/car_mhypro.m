function car_mhypro()

% Create Automaton
automaton = MHyProHAutomaton();

%-----------------------------------------------%
%                 loc acc
%-----------------------------------------------%
loc_acc = MHyProLocation();
loc_acc.setName('loc_acc');

% Set flow:
% v' = 5 d' = 19.44 - v t' = 1
flowMatrix = [0 0 0 5; -1 0 0 19.44;0 0 0 1; 0 0 0 0];
loc_acc.setFlow(flowMatrix);

% Set invariant d >= 20
inv = MHyProCondition([0 -1 0], -20);
loc_acc.setInvariant(inv);

%-----------------------------------------------%
%                 loc brake
%-----------------------------------------------%
loc_brake = MHyProLocation();
loc_brake.setName('loc_brake');

% Set flow:
% v' = -7 d' = 19.44 - v t' = 1
flowMatrix = [0 0 0 -7; -1 0 0 19.44;0 0 0 1; 0 0 0 0];
loc_brake.setFlow(flowMatrix);

% Set invariant v >= 0
inv = MHyProCondition([-1 0 0], 0);
loc_brake.setInvariant(inv);


%-----------------------------------------------%
%                 loc idle
%-----------------------------------------------%
loc_idle = MHyProLocation();
loc_idle.setName('loc_idle');

% Set flow:
% v' = -7 d' = 19.44 - v t' = 1
flowMatrix = [0 0 0 -7; -1 0 0 19.44;0 0 0 1; 0 0 0 0];
loc_idle.setFlow(flowMatrix);

% Set invariant v >= 0
inv = MHyProCondition([1 0 0], 0);
loc_idle.setInvariant(inv);

acc = automaton.addLocation(loc_acc);
brake = automaton.addLocation(loc_brake);
idle = automaton.addLocation(loc_idle);

%-----------------------------------------------%
%                acc -> brake
%-----------------------------------------------%
tran1 = MHyProTransition();
% Set guard:
% t == 3
guard1 = MHyProCondition();
guard1.setMatrix([ 0 0 -1; 0 0 1]); 
guard1.setVector([-3;3]);

% Set reset
reset = MHyProReset();
reset.setMatrix(eye(3));
reset.setVector([0;0;0]);

tran1.setAggregation(0);
tran1.setGuard(guard1);
tran1.setSource(acc);
tran1.setTarget(brake);
tran1.setReset(reset);
tran1.setLabels({MHyProLabel('t1')});

acc.addTransition(tran1);

%-----------------------------------------------%
%                brake -> acc
%-----------------------------------------------%
tran2 = MHyProTransition();
% Set guard:
% d >= 20 & v >= 0
guard2 = MHyProCondition();
guard2.setMatrix([ 0 -1 0; -1 0 0]); 
guard2.setVector([-20;0]);

tran2.setAggregation(0);
tran2.setGuard(guard2);
tran2.setSource(brake);
tran2.setTarget(acc);
tran2.setReset(reset);
tran2.setLabels({MHyProLabel('t2')});

brake.addTransition(tran2);

%-----------------------------------------------%
%                idle -> acc
%-----------------------------------------------%
tran3 = MHyProTransition();
% Set guard:
% d >= 20
guard3 = MHyProCondition();
guard3.setMatrix([ 0 -1 0]); 
guard3.setVector(-20);

tran3.setAggregation(0);
tran3.setGuard(guard3);
tran3.setSource(idle);
tran3.setTarget(acc);
tran3.setReset(reset);
tran3.setLabels({MHyProLabel('t3')});

idle.addTransition(tran3);
% 
% %-----------------------------------------------%
% %                brake -> idle
% %-----------------------------------------------%
% tran4 = MHyProTransition();
% % Set guard:
% % true v >= 0
% guard4 = MHyProCondition();
% guard4.setMatrix([ -1 0 0]); 
% guard4.setVector(0);
% 
% tran4.setAggregation(0);
% tran4.setGuard(guard4);
% tran4.setSource(brake);
% tran4.setTarget(idle);
% tran4.setReset(reset);
% tran4.setLabels({MHyProLabel('t4')});
% 
% brake.addTransition(tran4);

%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% Create initial set
% v = 0 d = 50 
boxVector = [0; 0; 50; -50; 0; 0];
boxMatrix = [-1 0 0; 1 0 0; 0 1 0; 0 -1 0; 0 0 -1; 0 0 1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(acc, initialCond);


%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

% Add basic settings
settings.timeBound = 10;
settings.jumpDepth = 1;
settings.timeStep = 0.1;
settings.clustering = -1;

reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(0);

tic;
flowpipes = reach.computeForwardReachability();

dim = [1 2];
labs = ["v", "d"];
ext = 'png';
reach.plot(flowpipes, dim, labs,0,'','',ext);
    











