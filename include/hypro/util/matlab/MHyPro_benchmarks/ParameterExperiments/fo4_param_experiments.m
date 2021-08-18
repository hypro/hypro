function fo4_param_experiments()

% vars = [x,y,x1,x2,x3,z,gc]

timeHorizon = 4;

% Add basic settings
settings.timeBound = 4;
settings.jumpDepth = 5;
%settings.uniformBloating = false;
settings.clustering = 0;
settings.timeStep = 0.05;
setRepr = 0;
aggr = 1;

% Create Automaton
automaton = MHyProHAutomaton();
dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(7));
dummy_reset.setVector(zeros(7,1));

%-----------------------------------------------%
%              Location loc1
%-----------------------------------------------%
loc1 = MHyProLocation();
loc1.setName('loc1');

% Set flow: x' = -2x + 1.4 & y' = -y - 0.7 & x1' = 5x - 5x1 &
% x_2' = 5x1 - 5x2 & x3' = 5x2 -  5x3 & z' = 5x3 - 5z & gc' = 1
flow_loc1 = [-2 0 0 0 0 0  0 1.4;...
             0 -1 0 0 0 0 0 -0.7;...
             5 0 -5 0 0 0 0 0;...
             0 0 5 -5 0 0 0 0;...
             0 0 0 5 -5 0 0 0;...
             0 0 0 0 5 -5 0 0;...
             0 0 0 0 0 0 0 1;...
             0 0 0 0 0 0 0 0];
loc1.setFlow(flow_loc1);

% Set inv: x <= 0 & y + 0.714286x >= 0 & gc <= timeHorizon
inv_loc1 = MHyProCondition([1,0,0,0,0,0,0;-0.714286,-1,0,0,0,0,0;0,0,0,0,0,0,1], [0;0;timeHorizon]);
loc1.setInvariant(inv_loc1);

%-----------------------------------------------%
%              Location loc2
%-----------------------------------------------%
loc2 = MHyProLocation();
loc2.setName('loc2');

% Set flow: x' = -2x - 1.4 & y' = -y + 0.7 & x1' = 5x - 5x1 &
% x_2' = 5x1 - 5x2 & x3' = 5x2 -  5x3 & z' = 5x3 - 5z gc' = 1
flow_loc2 = [-2 0 0 0 0 0 0 -1.4;...
             0 -1 0 0 0 0 0 0.7;...
             5 0 -5 0 0 0 0 0;...
             0 0 5 -5 0 0 0 0;...
             0 0 0 5 -5 0 0 0;...
             0 0 0 0 5 -5 0 0;...
             0 0 0 0 0 0 0 1;...
             0 0 0 0 0 0 0 0];
loc2.setFlow(flow_loc2);

% Set inv: x <= 0 & y + 0.714286x <= 0 & gc <= timeHorizon
inv_loc2 = MHyProCondition([1 0 0 0 0 0 0; 0.714286 1 0 0 0 0 0; 0 0 0 0 0 0 1], [0;0;timeHorizon]);
loc2.setInvariant(inv_loc2);

%-----------------------------------------------%
%              Location loc3
%-----------------------------------------------%
loc3 = MHyProLocation();
loc3.setName('loc3');

% Set flow: x' = -2x + 1.4 & y' = -y - 0.7 & x1' = 5x - 5x1 &
% x_2' = 5x1 - 5x2 & x3' = 5x2 -  5x3 & z' = 5x3 - 5z gc' = 1
flow_loc3 = [-2 0 0 0 0 0 0 1.4;...
             0 -1 0 0 0 0 0 -0.7;...
             5 0 -5 0 0 0 0 0;...
             0 0 5 -5 0 0 0 0;...
             0 0 0 5 -5 0 0 0;...
             0 0 0 0 5 -5 0 0;...
             0 0 0 0 0 0 0 1;...
             0 0 0 0 0 0 0 0];
loc3.setFlow(flow_loc3);

% Set inv: x >= 0 & y + 0.714286x >= 0 & gc <= timeHorizon
inv_loc3 = MHyProCondition([-1 0 0 0 0 0 0; -0.714286 -1 0 0 0 0 0; 0 0 0 0 0 0 1], [0;0;timeHorizon]);
loc3.setInvariant(inv_loc3);

%-----------------------------------------------%
%              Location loc4
%-----------------------------------------------%
loc4 = MHyProLocation();
loc4.setName('loc4');

% Set flow: x' = -2x - 1.4 & y' = -y + 0.7 & x1' = 5x - 5x1 &
% x_2' = 5x1 - 5x2 & x3' = 5x2 -  5x3 & z' = 5x3 - 5z gc' = 1
flow_loc4 = [-2 0 0 0 0 0 0 -1.4;...
             0 -1 0 0 0 0 0 0.7;...
             5 0 -5 0 0 0 0 0;...
             0 0 5 -5 0 0 0 0;...
             0 0 0 5 -5 0 0 0;...
             0 0 0 0 5 -5 0 0;...
             0 0 0 0 0 0 0 1;...
             0 0 0 0 0 0 0 0];
loc4.setFlow(flow_loc4);

% Set inv: x >= 0 & y + 0.714286x <= 0 & gc <= timeHorizon
inv_loc4 = MHyProCondition([-1 0 0 0 0 0 0; 0.714286 1 0 0 0 0 0; 0 0 0 0 0 0 1], [0;0;timeHorizon]);
loc4.setInvariant(inv_loc4);

%-----------------------------------------------%
%              Location sink
%-----------------------------------------------%
loc_sink = MHyProLocation();
loc_sink.setName('sink');

flowMatrix = zeros(7);
loc_sink.setFlow(flowMatrix);

l1 = automaton.addLocation(loc1);
l2 = automaton.addLocation(loc2);
l3 = automaton.addLocation(loc3);
l4 = automaton.addLocation(loc4);
s = automaton.addLocation(loc_sink);

%-----------------------------------------------%
%              loc1 -> loc3
%-----------------------------------------------%

tran1 = MHyProTransition();
% Set guard: x = 0 & 0.714286x + y >= 0
guard1 = MHyProCondition();
guard1.setMatrix([1 0 0 0 0 0 0; -1 0 0 0 0 0 0; -0.714286 -1 0 0 0 0 0]);
guard1.setVector([0;0;0]);

tran1.setAggregation(aggr);
tran1.setGuard(guard1);
tran1.setSource(l1);
tran1.setTarget(l3);
tran1.setReset(dummy_reset);
tran1.setLabels({MHyProLabel('tran1')});

l1.addTransition(tran1);

%-----------------------------------------------%
%              loc3 -> loc4
%-----------------------------------------------%

tran2 = MHyProTransition();
% Set guard: x >= 0 & 0.714286x + y = 0
guard2 = MHyProCondition();
guard2.setMatrix([-1 0 0 0 0 0 0; -0.714286 -1 0 0 0 0 0; 0.714286 1 0 0 0 0 0]);
guard2.setVector([0;0;0]);

tran2.setAggregation(aggr);
tran2.setGuard(guard2);
tran2.setSource(l3);
tran2.setTarget(l4);
tran2.setReset(dummy_reset);
tran2.setLabels({MHyProLabel('tran2')});

l3.addTransition(tran2);

%-----------------------------------------------%
%              loc4 -> loc2
%-----------------------------------------------%

tran3 = MHyProTransition();
% Set guard: x = 0 & 0.714286x + y <= 0
guard3 = MHyProCondition();
guard3.setMatrix([-1 0 0 0 0 0 0; 1 0 0 0 0 0 0; 0.714286 1 0 0 0 0 0]);
guard3.setVector([0;0;0]);

tran3.setAggregation(aggr);
tran3.setGuard(guard3);
tran3.setSource(l4);
tran3.setTarget(l2);
tran3.setReset(dummy_reset);
tran3.setLabels({MHyProLabel('tran3')});

l4.addTransition(tran3);

%-----------------------------------------------%
%              loc2 -> loc1
%-----------------------------------------------%

tran4 = MHyProTransition();
% Set guard: x <= 0 & 0.714286x + y = 0
guard4 = MHyProCondition();
guard4.setMatrix([1 0 0 0 0 0 0; 0.714286 1 0 0 0 0 0; -0.714286 -1 0 0 0 0 0]);
guard4.setVector([0;0;0]);

tran4.setAggregation(aggr);
tran4.setGuard(guard4);
tran4.setSource(l2);
tran4.setTarget(l1);
tran4.setReset(dummy_reset);
tran4.setLabels({MHyProLabel('tran4')});

l2.addTransition(tran4);

%-----------------------------------------------%
%              loc1 -> sink
%-----------------------------------------------%

tran1s = MHyProTransition();
% Set guard: gc == timeHorizon
guard1s = MHyProCondition();
guard1s.setMatrix([0 0 0 0 0 0 -1; 0 0 0 0 0 0 1]);
guard1s.setVector([-timeHorizon;timeHorizon]);

tran1s.setAggregation(0);
tran1s.setGuard(guard1s);
tran1s.setSource(l1);
tran1s.setTarget(s);
tran1s.setReset(dummy_reset);
tran1s.setLabels({MHyProLabel('tran1s')});

l1.addTransition(tran1s);

%-----------------------------------------------%
%              loc2 -> sink
%-----------------------------------------------%

tran2s = MHyProTransition();
% Set guard: gc == timeHorizon
guard2s = MHyProCondition();
guard2s.setMatrix([0 0 0 0 0 0 -1; 0 0 0 0 0 0 1]);
guard2s.setVector([-timeHorizon;timeHorizon]);

tran2s.setAggregation(0);
tran2s.setGuard(guard2s);
tran2s.setSource(l2);
tran2s.setTarget(s);
tran2s.setReset(dummy_reset);
tran2s.setLabels({MHyProLabel('tran2s')});

l2.addTransition(tran2s);

%-----------------------------------------------%
%              loc3 -> sink
%-----------------------------------------------%

tran3s = MHyProTransition();
% Set guard: gc == timeHorizon
guard3s = MHyProCondition();
guard3s.setMatrix([0 0 0 0 0 0 -1; 0 0 0 0 0 0 1]);
guard3s.setVector([-timeHorizon;timeHorizon]);

tran3s.setAggregation(0);
tran3s.setGuard(guard3s);
tran3s.setSource(l3);
tran3s.setTarget(s);
tran3s.setReset(dummy_reset);
tran3s.setLabels({MHyProLabel('tran3s')});

l3.addTransition(tran3s);

%-----------------------------------------------%
%              loc4 -> sink
%-----------------------------------------------%

tran4s = MHyProTransition();
% Set guard: gc == timeHorizon
guard4s = MHyProCondition();
guard4s.setMatrix([0 0 0 0 0 0 -1; 0 0 0 0 0 0 1]);
guard4s.setVector([-timeHorizon;timeHorizon]);

tran4s.setAggregation(0);
tran4s.setGuard(guard4s);
tran4s.setSource(l4);
tran4s.setTarget(s);
tran4s.setReset(dummy_reset);
tran4s.setLabels({MHyProLabel('tran4s')});

l4.addTransition(tran4s);

%-----------------------------------------------%
%              Initial Set
%-----------------------------------------------%
% x = [0.2, 0.3], y = [-0.1, 0.1] z,x1,x2,x3,gc = 0
boxVector = [0.3; 0.1; 0; 0; 0; 0; 0; -0.2; 0.1; 0; 0; 0; 0; 0];
boxMatrix = [eye(7); -1*eye(7)];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(l3, initialCond);

%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%



reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(setRepr);

tic;
flowpipes = reach.computeForwardReachability();
flowpipes2 = reach.computeForwardReachability();
reachabilityTime = toc;
disp(['Time needed for reachability: ', num2str(reachabilityTime)]);

dim = [3 2];
labs = ["x1", "y"];
%reach.plotColor(flowpipes, dim, labs,0,' ',' ',' ',[0.094, 0.725, 0.219]);
reach.plotComparison({flowpipes,flowpipes2}, dim, labs,{[0.094, 0.725, 0.219],[0.231, 0.788, 0.172]});
set(gca,'FontSize',15);


end
