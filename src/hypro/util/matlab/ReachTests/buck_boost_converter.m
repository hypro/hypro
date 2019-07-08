function time = buck_boost_converter(safe, safePath, figName)

% vars: [il; t; gt; vc]

% Create Automaton
automaton = MHyProHAutomaton();
dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(4));
dummy_reset.setVector([0; 0; 0; 0]);

%-----------------------------------------------%
%              Location charge
%-----------------------------------------------%
loc_1 = MHyProLocation();
loc_1.setName('charge');

% Set flow:
flow_1 = [0,0,0,0,0;...
          0,0,0,0,1;...
          0,0,0,0,1;...
          0,0,0,-40000,0;...
          0,0,0,0,0];
loc_1.setFlow(flow_1);

% Set inv:
invMat = [0,-1,0,0;...
0,1,0,0;...
0,0,-1,0;...
0,0,1,0;...
0,0,0,0;...
0,0,0,0;...
-1,0,0,0;...
1,0,0,0;...
0,0,0,-1;...
0,0,0,1];
invVec = [-0;3.333E-06;-0;...
0.00025;...
0.3333;0.6666;...
1000;1000;1000;1000];
inv_1 = MHyProCondition(invMat, invVec);
loc_1.setInvariant(inv_1);

%-----------------------------------------------%
%              Location discharge
%-----------------------------------------------%
loc_2 = MHyProLocation();
loc_2.setName('loc2');

% Set flow: v' = -5 x' = 0 t' = 0
flow_2 = [0 0 0 -5;...
          0 0 0 0;...
          0 0 0 0;...
          0 0 0 0];
loc_2.setFlow(flow_2);

% Set inv: v >= 15 & v <= 40
inv_2 = MHyProCondition([-1 0 0; 1 0 0], [-15;40]);
loc_2.setInvariant(inv_2);


%-----------------------------------------------%
%              Add locations to HA
%-----------------------------------------------%

l1 = automaton.addLocation(loc_1);
l2 = automaton.addLocation(loc_2);


%-----------------------------------------------%
%              loc1 --> loc2
%-----------------------------------------------%
tran1 = MHyProTransition();
% Set guard: t = 2.5 & 15 <= v <= 40
guard1 = MHyProCondition();
guard1.setMatrix([0 0 -1; 0 0 1; 0 0 -1; 0 0 1]); 
guard1.setVector([-2.5;2.5;-15;40]);

reset = MHyProReset();
reset.setMatrix([1,0,0,0;0,0,0,0;0,0,1,0;0,0,0,1]);
reset.setVector([0;0;0;0]);

tran1.setAggregation(1);
tran1.setGuard(guard1);
tran1.setSource(l1);
tran1.setTarget(l2);
tran1.setReset(dummy_reset);
tran1.setLabels({MHyProLabel('tran1')});

l1.addTransition(tran1);

%-----------------------------------------------%
%              loc1 --> loc4
%-----------------------------------------------%
tran2 = MHyProTransition();
% Set guard: 15 <= v <= 16 & 0 <= t <= 2.5
guard2 = MHyProCondition();
guard2.setMatrix([-1 0 0; 1 0 0; 0 0 -1; 0 0 1]); 
guard2.setVector([-15;16;0;2.5]);

tran2.setAggregation(1);
tran2.setGuard(guard2);
tran2.setSource(l1);
tran2.setTarget(l4);
reset2 = MHyProReset();
reset2.setMatrix([1 0 0; 0 1 0; 0 0 0]);
reset2.setVector([0; 0; 0]);
tran2.setReset(reset2);
tran2.setLabels({MHyProLabel('tran2')});

l1.addTransition(tran2);


%-----------------------------------------------%
%                 Bad States
%-----------------------------------------------%

% unsafe: l1,l2,l3,l4,l5,l6: x >= 146

% badState = MHyProCondition();
% badState.setMatrix([0 -1 0]);
% badState.setVector(-146);
% badStates(1).loc = l1;
% badStates(1).cond = badState;
% badStates(2).loc = l2;
% badStates(2).cond = badState;
% badStates(3).loc = l3;
% badStates(3).cond = badState;
% badStates(4).loc = l4;
% badStates(4).cond = badState;
% badStates(5).loc = l5;
% badStates(5).cond = badState;
% badStates(6).loc = l6;
% badStates(6).cond = badState;
% 
% automaton.setLocalBadStates(badStates);


%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% v = [15, 40] x = [0, 0]  t =[0, 2.5]
boxVector = [40; -15; 0; 0; 2.5; 0];
boxMatrix = [1 0 0; -1 0 0; 0 1 0; 0 -1 0; 0 0 1; 0 0 -1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(l1, initialCond);

%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

settings = struct('timeStep', 0.1, 'timeBound', 100, 'jumpDepth', 20);
reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(0);
%reach.settings();

tic;
flowpipes = reach.computeForwardReachability();
time = toc;
disp(['Time needed: ', num2str(time)]);
dim = [3 1];
labs = ["t","v"];
ext = 'png';
reach.plot(flowpipes, dim, labs,safe,safePath,figName,ext);
end