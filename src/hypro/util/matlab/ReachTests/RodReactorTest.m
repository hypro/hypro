function RodReactorTest

% Create Automaton
automaton = MHyProHAutomaton();

%-----------------------------------------------%
%              Location rod1
%-----------------------------------------------%
loc_rod1 = MHyProLocation();
loc_rod1.setName('rod1');

% Set flow: x' = 0.1x - 56 c1' = 1 c2' = 1
flow_rod1 = [0.1 0 0 -56; 0 0 0 1; 0 0 0 1; 0 0 0 0];
loc_rod1.setFlow(flow_rod1);

% Set inv: x >= 510 
inv_rod1 = MHyProCondition([-1 0 0], -510);
loc_rod1.setInvariant(inv_rod1);

%-----------------------------------------------%
%              Location noRods
%-----------------------------------------------%
loc_no = MHyProLocation();
loc_no.setName('noRods');

% Set flow: x' = 0.1x - 50 c1' = 1 c2' = 1
flow_no = [0.1 0 0 -50; 0 0 0 1; 0 0 0 1; 0 0 0 0];
loc_no.setFlow(flow_no);

% Set inv: x <= 550 
inv_no = MHyProCondition([1 0 0], 550);
loc_no.setInvariant(inv_no);

%-----------------------------------------------%
%              Location rod2
%-----------------------------------------------%
loc_rod2 = MHyProLocation();
loc_rod2.setName('rod2');

% Set flow: x' = 0.1x - 60 c1' = 1 c2' = 1
flow_rod2 = [0.1 0 0 -60; 0 0 0 1; 0 0 0 1; 0 0 0 0];
loc_rod2.setFlow(flow_rod2);

% Set inv: x >= 510 
inv_rod2 = MHyProCondition([-1 0 0], -510);
loc_rod2.setInvariant(inv_rod2);


%-----------------------------------------------%
%              Location sink
%-----------------------------------------------%
loc_sink = MHyProLocation();
loc_sink.setName('sink');

%-----------------------------------------------%
%              Transitions
%-----------------------------------------------%

% rod1 --> noRods
tran1 = MHyProTransition();
% Set guard: x = 510
guard1 = MHyProCondition();
guard1.setMatrix([1 0 0; -1 0 0]); % First set the matrix then the vector!?
guard1.setVector([510; -510]);
% Set reset: c1 := 0
reset1 = MHyProReset();
reset1.setMatrix([0 1 0; 0 -1 0]);
reset1.setVector([0; 0]);

%tran1.setAggregation(2);
tran1.setGuard(guard1);
tran1.setSource(loc_rod1);
tran1.setTarget(loc_no);
tran1.setLabels({MHyProLabel('tran1')});

loc_rod1.addTransition(tran1);

% noRods --> rod1
tran2 = MHyProTransition();
% Set guard: x = 550 & c1 >= 20
guard2 = MHyProCondition();
guard2.setMatrix([1 0 0; -1 0 0; 0 -1 0]); % First set the matrix then the vector!?
guard2.setVector([550; -550; -20]);

%tran2.setAggregation(2);
tran2.setGuard(guard2);
tran2.setSource(loc_no);
tran2.setTarget(loc_rod1);
tran2.setLabels({MHyProLabel('tran2')});

loc_no.addTransition(tran2);

% noRods --> rod2
tran3 = MHyProTransition();
% Set guard: x = 550 & c2 >= 20
guard3 = MHyProCondition();
guard3.setMatrix([1 0 0; -1 0 0; 0 0 -1]); % First set the matrix then the vector!?
guard3.setVector([550; -550; -20]);

%tran3.setAggregation(2);
tran3.setGuard(guard3);
tran3.setSource(loc_no);
tran3.setTarget(loc_rod2);
tran3.setLabels({MHyProLabel('tran3')});

loc_no.addTransition(tran3);

% rod2 --> noRods
tran4 = MHyProTransition();
% Set guard: x = 510
guard4 = MHyProCondition();
guard4.setMatrix([1 0 0; -1 0 0]); % First set the matrix then the vector!?
guard4.setVector([510; -510]);

% Set reset: c2 := 0
reset4 = MHyProReset();
reset4.setMatrix([0 0 -1; 0 0 1]);
reset4.setVector([0; 0]);

%tran4.setAggregation(2);
tran4.setGuard(guard4);
tran4.setSource(loc_rod2);
tran4.setTarget(loc_no);
tran4.setLabels({MHyProLabel('tran4')});

loc_rod2.addTransition(tran4);

% noRods --> sink
tran5 = MHyProTransition();
% Set guard: x = 550 & c1 <= 20 & c2 <= 20
guard5 = MHyProCondition();
guard5.setMatrix([1 0 0; -1 0 0; 0 1 0; 0 0 1]); % First set the matrix then the vector!?
guard5.setVector([550; -550; 20; 20]);

%tran5.setAggregation(2);
tran5.setGuard(guard5);
tran5.setSource(loc_no);
tran5.setTarget(loc_sink);
tran5.setLabels({MHyProLabel('tran5')});

loc_no.addTransition(tran5);


%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% x = [510 510] c1 = [20 20] c2 =[20 20]
boxVector = [510; -510; 20; -20; 20; -20];
boxMatrix = [1 0 0; -1 0 0; 0 1 0; 0 -1 0; 0 0 1; 0 0 -1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(loc_rod1, initialCond);

automaton.addLocation(loc_rod1);
automaton.addLocation(loc_rod2);
automaton.addLocation(loc_no);
automaton.addLocation(loc_sink);


%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

settings = struct('timeStep', 0.01, 'timeBound', 5, 'jumpDepth', 50);
reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(2);
reach.settings();

tic;
flowpipes = reach.computeForwardReachability();
time = toc;
disp(['Time needed: ', num2str(time)]);
dim = [2 3];
reach.plot(flowpipes, dim);
end
