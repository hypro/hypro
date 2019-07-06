function time = FilteredOscillator8(safe, safePath, figName)

% vars = [x,y,f4a_x1,f4a_x2,f4a_x3,f8_x1,f4b_x1,f4b_x2,f4b_x3,z]

% Create Automaton
automaton = MHyProHAutomaton();
dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(10));
dummy_reset.setVector(zeros(10,1));

%-----------------------------------------------%
%              Location loc1
%-----------------------------------------------%
loc1 = MHyProLocation();
loc1.setName('loc1');

% Set flow:
flow_loc1 = [-2 0 0 0 0 0 0 0 0 0 1.4;...
             0 -1 0 0 0 0 0 0 0 0 -0.7;...
             5  0 -5 0 0 0 0 0 0 0 0;...
             0 0 5 -5 0 0 0 0 0 0 0;...
             0 0 0 5 -5 0 0 0 0 0 0;...
             0 0 0 0 5 -5 0 0 0 0 0;...
             0 0 0 0 0 5 -5 0 0 0 0;...
             0 0 0 0 0 0 5 -5 0 0 0;...
             0 0 0 0 0 0 0  5 -5 0 0;...
             0 0 0 0 0 0 0 0 5 -5 0;...
             0 0 0 0 0 0 0 0 0 0 0];
loc1.setFlow(flow_loc1);

% Set inv: x <= 0 & y + 0.714286x >= 0
invMat = [1,0,0,0,0,0,0,0,0,0;-0.714286,-1,0,0,0,0,0,0,0,0];
inv_loc1 = MHyProCondition(invMat, [0;0]);
loc1.setInvariant(inv_loc1);


%-----------------------------------------------%
%              Location loc2
%-----------------------------------------------%
loc2 = MHyProLocation();
loc2.setName('loc2');

flow_loc2 = [-2 0 0 0 0 0 0 0 0 0 -1.4;...
             0 -1 0 0 0 0 0 0 0 0 0.7;...
             5  0 -5 0 0 0 0 0 0 0 0;...
             0 0 5 -5 0 0 0 0 0 0 0;...
             0 0 0 5 -5 0 0 0 0 0 0;...
             0 0 0 0 5 -5 0 0 0 0 0;...
             0 0 0 0 0 5 -5 0 0 0 0;...
             0 0 0 0 0 0 5 -5 0 0 0;...
             0 0 0 0 0 0 0  5 -5 0 0;...
             0 0 0 0 0 0 0 0 5 -5 0;...
             0 0 0 0 0 0 0 0 0 0 0];
loc2.setFlow(flow_loc2);

% Set inv: x <= 0 & y + 0.714286x <= 0
invMat = [1,0,0,0,0,0,0,0,0,0;0.7142869,1,0,0,0,0,0,0,0,0];
inv_loc2 = MHyProCondition(invMat, [0;0]);
loc2.setInvariant(inv_loc2);

%-----------------------------------------------%
%              Location loc3
%-----------------------------------------------%
loc3 = MHyProLocation();
loc3.setName('loc3');

% Set flow:
flow_loc3 = [-2 0 0 0 0 0 0 0 0 0 1.4;...
             0 -1 0 0 0 0 0 0 0 0 -0.7;...
             5  0 -5 0 0 0 0 0 0 0 0;...
             0 0 5 -5 0 0 0 0 0 0 0;...
             0 0 0 5 -5 0 0 0 0 0 0;...
             0 0 0 0 5 -5 0 0 0 0 0;...
             0 0 0 0 0 5 -5 0 0 0 0;...
             0 0 0 0 0 0 5 -5 0 0 0;...
             0 0 0 0 0 0 0  5 -5 0 0;...
             0 0 0 0 0 0 0 0 5 -5 0;...
             0 0 0 0 0 0 0 0 0 0 0];
loc3.setFlow(flow_loc3);

% Set inv: x >= 0 & y + 0.714286x >= 0
invMat = [-1,0,0,0,0,0,0,0,0,0;-0.714286,-1,0,0,0,0,0,0,0,0];
inv_loc3 = MHyProCondition(invMat, [0;0]);
loc3.setInvariant(inv_loc3);

%-----------------------------------------------%
%              Location loc4
%-----------------------------------------------%
loc4 = MHyProLocation();
loc4.setName('loc4');

% Set flow: x' = -2x - 1.4 & y' = -y + 0.7 & x1' = 5x - 5x1 &
% x_2' = 5x1 - 5x2 & x3' = 5x2 -  5x3 & z' = 5x3 - 5z
flow_loc4 = [-2 0 0 0 0 0 0 0 0 0 -1.4;...
             0 -1 0 0 0 0 0 0 0 0 0.7;...
             5  0 -5 0 0 0 0 0 0 0 0;...
             0 0 5 -5 0 0 0 0 0 0 0;...
             0 0 0 5 -5 0 0 0 0 0 0;...
             0 0 0 0 5 -5 0 0 0 0 0;...
             0 0 0 0 0 5 -5 0 0 0 0;...
             0 0 0 0 0 0 5 -5 0 0 0;...
             0 0 0 0 0 0 0  5 -5 0 0;...
             0 0 0 0 0 0 0 0 5 -5 0;...
             0 0 0 0 0 0 0 0 0 0 0];
loc4.setFlow(flow_loc4);

% Set inv: x >= 0 & y + 0.714286x <= 0
invMat = [-1 0 0 0 0 0 0 0 0 0; 0.714286 1 0 0 0 0 0 0 0 0];
inv_loc4 = MHyProCondition(invMat, [0;0]);
loc4.setInvariant(inv_loc4);

l1 = automaton.addLocation(loc1);
l2 = automaton.addLocation(loc2);
l3 = automaton.addLocation(loc3);
l4 = automaton.addLocation(loc4);

%-----------------------------------------------%
%              loc1 -> loc3
%-----------------------------------------------%

tran1 = MHyProTransition();
% Set guard: x = 0 & 0.714286x + y >= 0
guardMatrix = [1 0 0 0 0 0 0 0 0 0; -1 0 0 0 0 0 0 0 0 0; -0.714286 -1 0 0 0 0 0 0 0 0];
guard1 = MHyProCondition();
guard1.setMatrix(guardMatrix);
guard1.setVector([0;0;0]);

tran1.setAggregation(1);
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
guardMatrix = [-1 0 0 0 0 0 0 0 0 0; -0.714286 -1 0 0 0 0 0 0 0 0; 0.714286 1 0 0 0 0 0 0 0 0];
guard2 = MHyProCondition();
guard2.setMatrix(guardMatrix);
guard2.setVector([0;0;0]);

tran2.setAggregation(1);
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
guardMatrix = [-1 0 0 0 0 0 0 0 0 0; 1 0 0 0 0 0 0 0 0 0; 0.714286 1 0 0 0 0 0 0 0 0];
guard3 = MHyProCondition();
guard3.setMatrix(guardMatrix);
guard3.setVector([0;0;0]);

tran3.setAggregation(1);
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
guardMatrix = [1,0,0,0,0,0,0,0,0,0;-0.714286,-1,0,0,0,0,0,0,0,0;0.714286,1,0,0,0,0,0,0,0,0];
guard4 = MHyProCondition();
guard4.setMatrix(guardMatrix);
guard4.setVector([0;0;0]);

tran4.setAggregation(1);
tran4.setGuard(guard4);
tran4.setSource(l2);
tran4.setTarget(l1);
tran4.setReset(dummy_reset);
tran4.setLabels({MHyProLabel('tran4')});

l2.addTransition(tran4);

%-----------------------------------------------%
%              Initial Set
%-----------------------------------------------%
% x = [0.2, 0.3], y = [-0.1, 0.1] z,f4a_x1,f4a_x2,f4a_x3,f8_x1
%   f4b_x1,f4b_x2,f4b_x3 = 0
boxVector = [0.3; 0.1;0;0;0;0;0;0;0;0; -0.2; 0.1; 0; 0; 0; 0;0;0;0;0];
boxMatrix = [eye(10); -1*eye(10)];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(l3, initialCond);

%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

settings = struct('timeStep', 0.05, 'timeBound', 4, 'jumpDepth', 5);
reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(0);
%reach.settings();

tic;
flowpipes = reach.computeForwardReachability();
time = toc;
disp(['Time needed: ', num2str(time)]);
dim = [1 6];
labs = ["x","f8x1"];
ext = 'png';
reach.plot(flowpipes, dim, labs,safe,safePath,figName,ext);
end