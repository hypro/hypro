function time = boost_converter(safe, safePath, figName, bad)

% vars: [il; vc; t; gt]

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
flow_1 = [0,0,0,0,400000;...
          0,-40000,0,0,0;...
          0,0,0,0,1;...
          0,0,0,0,1;...
          0,0,0,0,0];
loc_1.setFlow(flow_1);

% Set inv:
invMat = [-1*eye(4);eye(4)];
invVec = [1000;1000;0;0;1000;1000;0.0000033333000000000003;0.00025];
inv_1 = MHyProCondition(invMat, invVec);
loc_1.setInvariant(inv_1);

%-----------------------------------------------%
%              Location discharge
%-----------------------------------------------%
loc_2 = MHyProLocation();
loc_2.setName('loc2');

% Set flow:
flow_2 = [0,-20000,0,0,400000;...
          40000,-40000,0,0,0;...
          0,0,0,0,1;...
          0,0,0,0,1;...
          0,0,0,0,0];
loc_2.setFlow(flow_2);

% Set inv:
invMat = [-1*eye(4);eye(4)];
invVec = [1000;1000;0;0;1000;1000;0.0000066667;0.00025];
inv_2 = MHyProCondition(invMat, invVec);
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
% Set guard:
guard1 = MHyProCondition();
guard1.setMatrix([0 0 -1 0]); 
guard1.setVector(-0.0000033333000000000003);

reset = MHyProReset();
reset.setMatrix([1 0 0 0; 0 1 0 0; 0 0 0 0; 0 0 0 1]);
reset.setVector([0;0;0;0]);

tran1.setAggregation(2);
tran1.setGuard(guard1);
tran1.setSource(l1);
tran1.setTarget(l2);
tran1.setReset(reset);
tran1.setLabels({MHyProLabel('tran1')});

l1.addTransition(tran1);

%-----------------------------------------------%
%              loc2 --> loc1
%-----------------------------------------------%
tran2 = MHyProTransition();
% Set guard:
guard2 = MHyProCondition();
guard2.setMatrix([0 0 -1 0]); 
guard2.setVector(-0.0000066667);

tran2.setAggregation(2);
tran2.setGuard(guard2);
tran2.setSource(l2);
tran2.setTarget(l1);
reset2 = MHyProReset();
reset2.setMatrix([1,0,0,0;0,0,0,0;0,0,1,0;0,0,0,1]);
reset2.setVector([0;0;0;0]);
tran2.setReset(reset2);
tran2.setLabels({MHyProLabel('tran2')});

l2.addTransition(tran2);


%-----------------------------------------------%
%                 Bad States
%-----------------------------------------------%

if bad
    %TODO
end

%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% il; t; gt; vc = 0
boxVector = zeros(8,1);
boxMatrix = [eye(4);-1*eye(4)];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(l1, initialCond);

%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

settings = struct('timeStep', 0.0000001, 'timeBound',  0.1, 'jumpDepth', 999999999);
reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(0);
%reach.settings();

tic;
flowpipes = reach.computeForwardReachability();
time = toc;
disp(['Time needed: ', num2str(time)]);
dim = [1 2];
labs = ["il","vc"];
ext = 'png';
reach.plot(flowpipes, dim, labs,safe,safePath,figName,ext);
end