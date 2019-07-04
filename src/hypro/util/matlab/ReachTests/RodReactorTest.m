function RodReactorTest

% Create Automaton
automaton = MHyProHAutomaton();
dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(3));
dummy_reset.setVector([0; 0; 0]);

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
%              Add locations to HA
%-----------------------------------------------%

rod1 = automaton.addLocation(loc_rod1);
rod2 = automaton.addLocation(loc_rod2);
noRod = automaton.addLocation(loc_no);

%-----------------------------------------------%
%              rod1 --> noRods
%-----------------------------------------------%
tran1 = MHyProTransition();
% Set guard: x = 510
guard1 = MHyProCondition();
guard1.setMatrix([1 0 0; -1 0 0]); % First set the matrix then the vector!?
guard1.setVector([510; -510]);
% Set reset: c1 := 0
reset1 = MHyProReset();
reset1.setMatrix([1 0 0; 0 0 0; 0 0 1]);
reset1.setVector([0; 0; 0]);

tran1.setAggregation(1);
tran1.setGuard(guard1);
tran1.setSource(rod1);
tran1.setTarget(noRod);
tran1.setReset(reset1);
tran1.setLabels({MHyProLabel('tran1')});

rod1.addTransition(tran1);

%-----------------------------------------------%
%              noRods --> rod1
%-----------------------------------------------%
tran2 = MHyProTransition();
% Set guard: x = 550 & c1 >= 20
guard2 = MHyProCondition();
guard2.setMatrix([1 0 0; -1 0 0; 0 -1 0]); % First set the matrix then the vector!?
guard2.setVector([550; -550; -20]);

tran2.setAggregation(1);
tran2.setGuard(guard2);
tran2.setSource(noRod);
tran2.setTarget(rod1);
tran2.setReset(dummy_reset);
tran2.setLabels({MHyProLabel('tran2')});

noRod.addTransition(tran2);

%-----------------------------------------------%
%              noRods --> rod2
%-----------------------------------------------%
tran3 = MHyProTransition();
% Set guard: x = 550 & c2 >= 20
guard3 = MHyProCondition();
guard3.setMatrix([1 0 0; -1 0 0; 0 0 -1]); % First set the matrix then the vector!?
guard3.setVector([550; -550; -20]);

tran3.setAggregation(1);
tran3.setGuard(guard3);
tran3.setSource(noRod);
tran3.setTarget(rod2);
tran3.setReset(dummy_reset);
tran3.setLabels({MHyProLabel('tran3')});

noRod.addTransition(tran3);

%-----------------------------------------------%
%              rod2 --> noRods
%-----------------------------------------------%
tran4 = MHyProTransition();
% Set guard: x = 510
guard4 = MHyProCondition();
guard4.setMatrix([1 0 0; -1 0 0]); % First set the matrix then the vector!?
guard4.setVector([510; -510]);
% Set reset: c2 := 0
reset4 = MHyProReset();
reset4.setMatrix([1 0 0; 0 1 0; 0 0 0]);
reset4.setVector([0; 0; 0]);

tran4.setAggregation(1);
tran4.setGuard(guard4);
tran4.setSource(rod2);
tran4.setTarget(noRod);
tran4.setReset(reset4);
tran4.setLabels({MHyProLabel('tran4')});

rod2.addTransition(tran4);

%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% x = [510 520] c1 = [20 20] c2 =[20 20]
boxVector = [520; -510; 20; -20; 20; -20];
boxMatrix = [1 0 0; -1 0 0; 0 1 0; 0 -1 0; 0 0 1; 0 0 -1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(noRod, initialCond);


%test
locs = automaton.getLocations();
assert(length(locs) == 3);
assert(isequal(locs{1}.getName(), 'rod1'));
assert(isequal(locs{2}.getName(), 'rod2'));
assert(isequal(locs{3}.getName(), 'noRods'));
% assert(isequal(locs{4}.getName(), 'sink'));
initialMapping = automaton.getInitialStates();
assert(length(initialMapping) == 1);
iCond = initialMapping(1).cond;
assert(iCond == initialCond);
iLoc = initialMapping(1).loc;
assert(iLoc == noRod);
%test end

%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

settings = struct('timeStep', 0.1, 'timeBound', 15, 'jumpDepth', 20);
reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(0);
%reach.settings();

tic;
flowpipes = reach.computeForwardReachability();
time = toc;
disp(['Time needed: ', num2str(time)]);
dim = [1 3];
labs = ["x", "c2"];
reach.plot(flowpipes, dim, labs);

end
