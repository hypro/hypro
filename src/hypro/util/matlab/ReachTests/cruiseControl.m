function cruiseControl

% vars: [v, x, t]

% Create Automaton
automaton = MHyProHAutomaton();
dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(3));
dummy_reset.setVector([0; 0; 0]);

%-----------------------------------------------%
%              Location loc1
%-----------------------------------------------%
loc_1 = MHyProLocation();
loc_1.setName('loc1');

% Set flow: v' = -t -2.5 x' = 0 t' = 1
flow_1 = [0 0 -1 -2.5;...
          0 0 0 0;...
          0 0 0 1;...
          0 0 0 0];
loc_1.setFlow(flow_1);

% Set inv: v >= 15 & v <= 40 & t >= 0& t<= 2.5
inv_1 = MHyProCondition([-1 0 0;1 0 0; 0 0 -1; 0 0 1], [-15;40;0;2.5]);
loc_1.setInvariant(inv_1);

%-----------------------------------------------%
%              Location loc2
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
%              Location loc3
%-----------------------------------------------%
loc_3 = MHyProLocation();
loc_3.setName('loc3');

% Set flow: v' = -2.5 x' = 0 t' = 0
flow_3 = [0 0 0 -2.5;...
          0 0 0 0;...
          0 0 0 0;...
          0 0 0 0];
loc_3.setFlow(flow_3);

% Set inv: v >= 5 & v <= 20
inv_3 = MHyProCondition([-1 0 0;1 0 0], [-5;20]);
loc_3.setInvariant(inv_3);

%-----------------------------------------------%
%              Location loc4
%-----------------------------------------------%
loc_4 = MHyProLocation();
loc_4.setName('loc4');

% Set flow: v' = -t -1.2 x' = 0 t' = 0.5
flow_4 = [0 0 -1 -1.2;...
          0 0 0 0;...
          0 0 0 0.5;...
          0 0 0 0];
loc_4.setFlow(flow_4);

% Set inv: v >= 5 & v <= 20 & t >= 0& t<= 1.3
inv_4 = MHyProCondition([-1 0 0;1 0 0; 0 0 -1; 0 0 1], [-5;20;0;1.3]);
loc_4.setInvariant(inv_4);


%-----------------------------------------------%
%              Location loc5
%-----------------------------------------------%
loc_5 = MHyProLocation();
loc_5.setName('loc5');

% Set flow: v' = -0.001x - 0.052v x' = v t' = 0
flow_5 = [-0.052 -0.001 0 0;...
          1 0 0 0;...
          0 0 0 0;...
          0 0 0 0];
loc_5.setFlow(flow_5);

% Set inv: v >= -15 & v <= 15 & x >= -500 & x <= 500
inv_5 = MHyProCondition([-1 0 0;1 0 0; 0 -1 0; 0 1 0], [15;15;500;500]);
loc_5.setInvariant(inv_5);

%-----------------------------------------------%
%              Location loc6
%-----------------------------------------------%
loc_6 = MHyProLocation();
loc_6.setName('loc6');

% Set flow: v' = 1.5 x' = 0 t' = 0
flow_6 = [0 0 0 1.5;...
          0 0 0 0;...
          0 0 0 0;...
          0 0 0 0];
loc_6.setFlow(flow_6);

% Set inv: v >= -20 & v <= -5 
inv_6 = MHyProCondition([-1 0 0;1 0 0], [20;-5]);
loc_6.setInvariant(inv_6);


%-----------------------------------------------%
%              Add locations to HA
%-----------------------------------------------%

l1 = automaton.addLocation(loc_1);
l2 = automaton.addLocation(loc_2);
l3 = automaton.addLocation(loc_3);
l4 = automaton.addLocation(loc_4);
l5 = automaton.addLocation(loc_5);
l6 = automaton.addLocation(loc_6);

%-----------------------------------------------%
%              loc1 --> loc2
%-----------------------------------------------%
tran1 = MHyProTransition();
% Set guard: t = 2.5 & 15 <= v <= 40
guard1 = MHyProCondition();
guard1.setMatrix([0 0 -1; 0 0 1; 0 0 -1; 0 0 1]); 
guard1.setVector([-2.5;2.5;-15;40]);

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
%              loc2 --> loc4
%-----------------------------------------------%
tran3 = MHyProTransition();
% Set guard: t = 2.5 & 15 <= v <= 16
guard3 = MHyProCondition();
guard3.setMatrix([-1 0 0; 1 0 0; 0 0 -1; 0 0 1]); 
guard3.setVector([-15;16;-2.5;2.5]);

tran3.setAggregation(1);
tran3.setGuard(guard3);
tran3.setSource(l2);
tran3.setTarget(l4);
reset3 = MHyProReset();
reset3.setMatrix([1 0 0; 0 1 0; 0 0 0]);
reset3.setVector([0; 0; 0]);
tran3.setReset(reset3);
tran3.setLabels({MHyProLabel('tran3')});

l2.addTransition(tran3);

%-----------------------------------------------%
%              loc3 --> loc1
%-----------------------------------------------%
tran4 = MHyProTransition();
% Set guard: t = 1.3 & 18 <= v <= 20
guard4 = MHyProCondition();
guard4.setMatrix([-1 0 0; 1 0 0; 0 0 -1; 0 0 1]); 
guard4.setVector([-18;20;-1.3;1.3]);

tran4.setAggregation(1);
tran4.setGuard(guard4);
tran4.setSource(l3);
tran4.setTarget(l1);
reset4 = MHyProReset();
reset4.setMatrix([1 0 0; 0 1 0; 0 0 0]);
reset4.setVector([0; 0; 0]);
tran4.setReset(reset4);
tran4.setLabels({MHyProLabel('tran4')});

l3.addTransition(tran4);

%-----------------------------------------------%
%              loc3 --> loc5
%-----------------------------------------------%
tran5 = MHyProTransition();
% Set guard: t = 1.3 & v = [5,11]
guard5 = MHyProCondition();
guard5.setMatrix([-1 0 0; 1 0 0; 0 0 -1; 0 0 1]); 
guard5.setVector([-1.3;1.3;-5;11]);

tran5.setAggregation(1);
tran5.setGuard(guard4);
tran5.setSource(l3);
tran5.setTarget(l5);
reset5 = MHyProReset();
reset5.setMatrix([1 0 0; 0 0 0; 0 0 1]);
reset5.setVector([0; 0; 0]);
tran5.setReset(reset5);
tran5.setLabels({MHyProLabel('tran5')});

l3.addTransition(tran5);

%-----------------------------------------------%
%              loc4 --> loc1
%-----------------------------------------------%
tran6 = MHyProTransition();
% Set guard: 18 <= v <= 20 & 0 <= t <= 1.3
guard6 = MHyProCondition();
guard6.setMatrix([-1 0 0; 1 0 0; 0 0 -1; 0 0 1]); 
guard6.setVector([-18;20;0;1.3]);

tran6.setAggregation(1);
tran6.setGuard(guard6);
tran6.setSource(l4);
tran6.setTarget(l1);
reset6 = MHyProReset();
reset6.setMatrix([1 0 0; 0 1 0; 0 0 0]);
reset6.setVector([0; 0; 0]);
tran6.setReset(reset6);
tran6.setLabels({MHyProLabel('tran6')});

l4.addTransition(tran6);

%-----------------------------------------------%
%              loc4 --> loc5
%-----------------------------------------------%
tran7 = MHyProTransition();
% Set guard:  5 <= v <= 11 6 0 <= t <= 1.3
guard7 = MHyProCondition();
guard7.setMatrix([-1 0 0; 1 0 0; 0 0 -1; 0 0 1]); 
guard7.setVector([-5;11;0;1.3]);

tran7.setAggregation(1);
tran7.setGuard(guard7);
tran7.setSource(l4);
tran7.setTarget(l5);
reset7 = MHyProReset();
reset7.setMatrix([1 0 0; 0 0 0; 0 0 1]);
reset7.setVector([0; 0; 0]);
tran7.setReset(reset7);
tran7.setLabels({MHyProLabel('tran7')});

l4.addTransition(tran7);

%-----------------------------------------------%
%              loc4 --> loc3
%-----------------------------------------------%
tran71 = MHyProTransition();
% Set guard: t = 1.3 & 5 <= v <= 20
guard71 = MHyProCondition();
guard71.setMatrix([-1 0 0; 1 0 0; 0 0 -1; 0 0 1]); 
guard71.setVector([-5;20;-1.3;1.3]);

tran71.setAggregation(1);
tran71.setGuard(guard71);
tran71.setSource(l4);
tran71.setTarget(l3);
tran71.setReset(dummy_reset);
tran71.setLabels({MHyProLabel('tran71')});

l4.addTransition(tran71);

%-----------------------------------------------%
%              loc5 --> loc4
%-----------------------------------------------%
tran8 = MHyProTransition();
% Set guard: 13 <= v <= 15 & -500 <= x <= 500
guard8 = MHyProCondition();
guard8.setMatrix([-1 0 0; 1 0 0; 0 -1 0; 0 1 0]); 
guard8.setVector([-13;15; 500;500]);

tran8.setAggregation(1);
tran8.setGuard(guard8);
tran8.setSource(l5);
tran8.setTarget(l4);
reset8 = MHyProReset();
reset8.setMatrix([1 0 0; 0 1 0; 0 0 0]);
reset8.setVector([0; 0; 0]);
tran8.setReset(reset8);
tran8.setLabels({MHyProLabel('tran8')});

l5.addTransition(tran8);

%-----------------------------------------------%
%              loc5 --> loc6
%-----------------------------------------------%
tran9 = MHyProTransition();
% Set guard:  -15 <= v <= -14 & -500 <= x <= 500
guard9 = MHyProCondition();
guard9.setMatrix([-1 0 0; 1 0 0; 0 -1 0; 0 1 0]); 
guard9.setVector([15;-14;500;500]);

tran9.setAggregation(1);
tran9.setGuard(guard9);
tran9.setSource(l5);
tran9.setTarget(l6);
tran9.setReset(dummy_reset);
tran9.setLabels({MHyProLabel('tran9')});

l5.addTransition(tran9);

%-----------------------------------------------%
%              loc6 --> loc5
%-----------------------------------------------%
tran10 = MHyProTransition();
% Set guard:-6 <= v <= -5 & -500 <= x <= 500
guard10 = MHyProCondition();
guard10.setMatrix([-1 0 0; 1 0 0; 0 -1 0; 0 1 0]); 
guard10.setVector([6;-5; 500;500]);

tran10.setAggregation(1);
tran10.setGuard(guard10);
tran10.setSource(l6);
tran10.setTarget(l5);
reset10 = MHyProReset();
reset10.setMatrix([1 0 0; 0 0 0; 0 0 1]);
reset10.setVector([0; 0; 0]);
tran10.setReset(reset10);
tran10.setLabels({MHyProLabel('tran10')});

l6.addTransition(tran10);

%-----------------------------------------------%
%                 Bad States
%-----------------------------------------------%

% unsafe: l1,l2,l3,l4,l5,l6: x >= 146

badState = MHyProCondition();
badState.setMatrix([0 -1 0]);
badState.setVector(-146);
badStates(1).loc = l1;
badStates(1).cond = badState;
badStates(2).loc = l2;
badStates(2).cond = badState;
badStates(3).loc = l3;
badStates(3).cond = badState;
badStates(4).loc = l4;
badStates(4).cond = badState;
badStates(5).loc = l5;
badStates(5).cond = badState;
badStates(6).loc = l6;
badStates(6).cond = badState;

automaton.setLocalBadStates(badStates);


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
dim = [1 2];
reach.plot(flowpipes, dim);
end