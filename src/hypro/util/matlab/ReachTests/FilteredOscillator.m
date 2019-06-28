function FilteredOscillator

% vars = [x,y,x1,x2,x3,z]

% Create Automaton
automaton = MHyProHAutomaton();

%-----------------------------------------------%
%              Location loc1
%-----------------------------------------------%
loc1 = MHyProLocation();
loc1.setName('loc1');

% Set flow: x' = -2x + 1.4 & y' = -y - 0.7 & x1' = 5x - 5x1 &
% x_2' = 5x1 - 5x2 & x3' = 5x2 -  5x3 & z' = 5x3 - 5z
flow_loc1 = [-2 0 0 0 0 0 1.4;...
             0 -1 0 0 0 0 -0.7;...
             5 0 -5 0 0 0 0;...
             0 0 5 -5 0 0 0;...
             0 0 0 5 -5 0 0;...
             0 0 0 0 5 -5 0;...
             0 0 0 0 0 0 0];
loc1.setFlow(flow_loc1);

% Set inv: x <= 0 & y + 0.714286x >= 0
invMat = [1 0 0 0 0 0; -0.714286 -1 0 0 0 0];
inv_loc1 = MHyProCondition(invMat, [0;0]);
loc1.setInvariant(inv_loc1);

% test
f = loc1.getLinearFlow();
fm = f.getFlowMatrix();
assert(isequal(flow_loc1, fm));
i = loc1.getInvariant();
assert(i == inv_loc1);
% test end

%-----------------------------------------------%
%              Location loc2
%-----------------------------------------------%
loc2 = MHyProLocation();
loc2.setName('loc2');

% Set flow: x' = -2x - 1.4 & y' = -y + 0.7 & x1' = 5x - 5x1 &
% x_2' = 5x1 - 5x2 & x3' = 5x2 -  5x3 & z' = 5x3 - 5z
flow_loc2 = [-2 0 0 0 0 0 -1.4;...
             0 -1 0 0 0 0 0.7;...
             5 0 -5 0 0 0 0;...
             0 0 5 -5 0 0 0;...
             0 0 0 5 -5 0 0;...
             0 0 0 0 5 -5 0;...
             0 0 0 0 0 0 0];
loc2.setFlow(flow_loc2);

% Set inv: x <= 0 & y + 0.714286x <= 0
invMat = [1 0 0 0 0 0; 0.714286 1 0 0 0 0];
inv_loc2 = MHyProCondition(invMat, [0;0]);
loc2.setInvariant(inv_loc2);

% test
f = loc2.getLinearFlow();
fm = f.getFlowMatrix();
assert(isequal(flow_loc2, fm));
i = loc2.getInvariant();
assert(i == inv_loc2);
% test end

%-----------------------------------------------%
%              Location loc3
%-----------------------------------------------%
loc3 = MHyProLocation();
loc3.setName('loc3');

% Set flow: x' = -2x + 1.4 & y' = -y - 0.7 & x1' = 5x - 5x1 &
% x_2' = 5x1 - 5x2 & x3' = 5x2 -  5x3 & z' = 5x3 - 5z
flow_loc3 = [-2 0 0 0 0 0 1.4;...
             0 -1 0 0 0 0 -0.7;...
             5 0 -5 0 0 0 0;...
             0 0 5 -5 0 0 0;...
             0 0 0 5 -5 0 0;...
             0 0 0 0 5 -5 0;...
             0 0 0 0 0 0 0];
loc3.setFlow(flow_loc3);

% Set inv: x >= 0 & y + 0.714286x >= 0
invMat = [-1 0 0 0 0 0; -0.714286 -1 0 0 0 0];
inv_loc3 = MHyProCondition(invMat, [0;0]);
loc3.setInvariant(inv_loc3);

% test
f = loc3.getLinearFlow();
fm = f.getFlowMatrix();
assert(isequal(flow_loc3, fm));
i = loc3.getInvariant();
assert(i == inv_loc3);
% test end

%-----------------------------------------------%
%              Location loc4
%-----------------------------------------------%
loc4 = MHyProLocation();
loc4.setName('loc4');

% Set flow: x' = -2x - 1.4 & y' = -y + 0.7 & x1' = 5x - 5x1 &
% x_2' = 5x1 - 5x2 & x3' = 5x2 -  5x3 & z' = 5x3 - 5z
flow_loc4 = [-2 0 0 0 0 0 -1.4;...
             0 -1 0 0 0 0 0.7;...
             5 0 -5 0 0 0 0;...
             0 0 5 -5 0 0 0;...
             0 0 0 5 -5 0 0;...
             0 0 0 0 5 -5 0;...
             0 0 0 0 0 0 0];
loc4.setFlow(flow_loc4);

% Set inv: x >= 0 & y + 0.714286x <= 0
invMat = [-1 0 0 0 0 0; 0.714286 1 0 0 0 0];
inv_loc4 = MHyProCondition(invMat, [0;0]);
loc4.setInvariant(inv_loc4);

% test
f = loc4.getLinearFlow();
fm = f.getFlowMatrix();
assert(isequal(flow_loc4, fm));
i = loc4.getInvariant();
assert(i == inv_loc4);
% test end

%-----------------------------------------------%
%              loc1 -> loc3
%-----------------------------------------------%

tran1 = MHyProTransition();
% Set guard: x = 0 & 0.714286x + y >= 0
guardMatrix = [1 0 0 0 0 0; -1 0 0 0 0 0; -0.714286 -1 0 0 0 0];
guard1 = MHyProCondition();
guard1.setMatrix(guardMatrix); % First set the matrix then the vector!?
guard1.setVector([0;0;0]);

%tran1.setAggregation(2);
tran1.setGuard(guard1);
tran1.setSource(loc1);
tran1.setTarget(loc3);
tran1.setLabels({MHyProLabel('tran1')});

loc1.addTransition(tran1);

% test
locT = loc1.getTransitions();
assert(length(locT) == 1);
lab1 = locT{1}.getLabels();
assert(isequal(lab1{1}.getName(), 'tran1'));
g = tran1.getGuard();
assert(g == guard1);
s = tran1.getSource();
t = tran1.getTarget();
assert(s == loc1);
assert(t == loc3);
% test end

%-----------------------------------------------%
%              loc3 -> loc4
%-----------------------------------------------%

tran2 = MHyProTransition();
% Set guard: x >= 0 & 0.714286x + y = 0
guardMatrix = [-1 0 0 0 0 0; -0.714286 -1 0 0 0 0; 0.714286 1 0 0 0 0];
guard2 = MHyProCondition();
guard2.setMatrix(guardMatrix); % First set the matrix then the vector!?
guard2.setVector([0;0;0]);

%tran2.setAggregation(2);
tran2.setGuard(guard2);
tran2.setSource(loc3);
tran2.setTarget(loc4);
tran2.setLabels({MHyProLabel('tran2')});

loc3.addTransition(tran2);

% test
locT = loc3.getTransitions();
assert(length(locT) == 1);
lab1 = locT{1}.getLabels();
assert(isequal(lab1{1}.getName(), 'tran2'));
g = tran2.getGuard();
assert(g == guard2);
s = tran2.getSource();
t = tran2.getTarget();
assert(s == loc3);
assert(t == loc4);
% test end

%-----------------------------------------------%
%              loc4 -> loc2
%-----------------------------------------------%

tran3 = MHyProTransition();
% Set guard: x = 0 & 0.714286x + y <= 0
guardMatrix = [-1 0 0 0 0 0; 1 0 0 0 0 0; 0.714286 1 0 0 0 0];
guard3 = MHyProCondition();
guard3.setMatrix(guardMatrix); % First set the matrix then the vector!?
guard3.setVector([0;0;0]);

%tran3.setAggregation(2);
tran3.setGuard(guard3);
tran3.setSource(loc4);
tran3.setTarget(loc2);
tran3.setLabels({MHyProLabel('tran3')});

loc4.addTransition(tran3);

% test
locT = loc4.getTransitions();
assert(length(locT) == 1);
lab1 = locT{1}.getLabels();
assert(isequal(lab1{1}.getName(), 'tran3'));
g = tran3.getGuard();
assert(g == guard3);
s = tran3.getSource();
t = tran3.getTarget();
assert(s == loc4);
assert(t == loc2);
% test end


%-----------------------------------------------%
%              loc2 -> loc1
%-----------------------------------------------%

tran4 = MHyProTransition();
% Set guard: x -= 0 & 0.714286x + y = 0
guardMatrix = [1 0 0 0 0 0; 0.714286 1 0 0 0 0; -0.714286 -1 0 0 0 0];
guard4 = MHyProCondition();
guard4.setMatrix(guardMatrix); % First set the matrix then the vector!?
guard4.setVector([0;0;0]);

%tran4.setAggregation(2);
tran4.setGuard(guard4);
tran4.setSource(loc2);
tran4.setTarget(loc1);
tran4.setLabels({MHyProLabel('tran4')});

loc2.addTransition(tran4);

% test
locT = loc2.getTransitions();
assert(length(locT) == 1);
lab1 = locT{1}.getLabels();
assert(isequal(lab1{1}.getName(), 'tran4'));
g = tran4.getGuard();
assert(g == guard4);
s = tran4.getSource();
t = tran4.getTarget();
assert(s == loc2);
assert(t == loc1);
% test end


automaton.addLocation(loc1);
automaton.addLocation(loc2);
automaton.addLocation(loc3);
automaton.addLocation(loc4);

%-----------------------------------------------%
%              Initial Set
%-----------------------------------------------%

% x = [0.2, 0.3], y = [-0.1, 0.1] z,x1,x2,x3 = 0
boxVector = [0.3; 0.1; 0; 0; 0; 0; 0.2; -0.1; 0; 0; 0; 0];
boxMatrix = [eye(6); -1*eye(6)];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(loc1, initialCond);

%test
locs = automaton.getLocations();
assert(length(locs) == 4);
assert(isequal(locs{1}.getName(), 'loc1'));
assert(isequal(locs{2}.getName(), 'loc2'));
assert(isequal(locs{3}.getName(), 'loc3'));
assert(isequal(locs{4}.getName(), 'loc4'));
initialMapping = automaton.getInitialStates();
assert(length(initialMapping) == 1);
iCond = initialMapping(1).cond;
assert(iCond == initialCond);
iLoc = initialMapping(1).loc;
assert(iLoc == loc1);
%test end

%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

settings = struct('timeStep', 0.1, 'timeBound', 4, 'jumpDepth', 1);
reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(0);
%reach.settings();

tic;
flowpipes = reach.computeForwardReachability();
time = toc;
disp(['Time needed: ', num2str(time)]);
dim = [1 2];
reach.plot(flowpipes, dim);

end