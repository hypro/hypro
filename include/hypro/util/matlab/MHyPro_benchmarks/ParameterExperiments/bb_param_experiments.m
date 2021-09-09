function bb_param_experiments()

% Create Automaton
automaton = MHyProHAutomaton();

% Add basic settings
settings.timeBound = 4;
settings.jumpDepth = 2;
%settings.uniformBloating = false;
settings.clustering = 0;
settings.timeStep = 0.01;
setRepr = 0;
aggr = 1;

%-----------------------------------------------%
%                 loc loc_1
%-----------------------------------------------%
loc = MHyProLocation();
loc.setName('loc');

% Set flow:
% x' = v v' = -9.81 t' = 1
flowMatrix = [0 1 0 0; 0 0 0 -9.81;0 0 0 1; 0 0 0 0];
loc.setFlow(flowMatrix);

% Set invariant x >= 0 & t <= 4
inv = MHyProCondition([-1 0 0; 0 0 1], [0; 4]);
loc.setInvariant(inv);

%-----------------------------------------------%
%                 loc sink
%-----------------------------------------------%

loc_sink = MHyProLocation();
loc_sink.setName('sink');

% Set flow:
% x' = 0 v' = 0 t' = 0
flowMatrix = zeros(3);
loc_sink.setFlow(flowMatrix);

% Set invariant x >= 0
% inv = MHyProCondition([-1 0 0], [0]);
% loc.setInvariant(inv);

l = automaton.addLocation(loc);
s = automaton.addLocation(loc_sink);

%-----------------------------------------------%
%                loc -> loc
%-----------------------------------------------%
tran = MHyProTransition();
% Set guard:
% x = 0 & v <= 0
guard = MHyProCondition();
guard.setMatrix([ -1 0 0; 1 0 0; 0 1 0]); 
guard.setVector([0;0;0]);

% Set reset
% x:= x v:= -0.75v t := t
reset = MHyProReset();
reset.setMatrix([1 0 0; 0 -0.75 0; 0 0 1]);
reset.setVector([0;0;0]);

tran.setAggregation(aggr);
tran.setGuard(guard);
tran.setSource(l);
tran.setTarget(l);
tran.setReset(reset);
tran.setLabels({MHyProLabel('t1')});

l.addTransition(tran);

%-----------------------------------------------%
%                loc -> loc_sink
%-----------------------------------------------%
tran2 = MHyProTransition();
% Set guard:
% t == 4
guard2 = MHyProCondition();
guard2.setMatrix([ 0 0 -1; 0 0 1]);
guard2.setVector([-4;4]);

% Set reset
reset2 = MHyProReset();
reset2.setMatrix(eye(3));
reset2.setVector([0;0;0]);

tran2.setAggregation(aggr);
tran2.setGuard(guard2);
tran2.setSource(l);
tran2.setTarget(s);
tran2.setReset(reset2);
tran2.setLabels({MHyProLabel('t2')});

l.addTransition(tran2);


%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% Create initial set
% x = [10, 10.2] v = 0 t = 0 
boxVector = [-10; 10.2; 0; 0; 0; 0];
boxMatrix = [-1 0 0; 1 0 0; 0 1 0; 0 -1 0; 0 0 -1; 0 0 1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(l, initialCond);

%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(setRepr);

tic;
flowpipes = reach.computeForwardReachability();
reachabilityTime = toc;

disp(['Time needed for the rechability: ', num2str(reachabilityTime)]);

dim = [2 1];
labs = ["t", "x"];
reach.plotColor(flowpipes, dim, labs,0,' ',' ',' ',[0.094, 0.725, 0.219]);
set(gca,'FontSize',15);


end
