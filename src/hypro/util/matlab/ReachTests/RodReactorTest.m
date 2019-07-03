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

% test
f = loc_rod1.getLinearFlow();
fm = f.getFlowMatrix();
assert(isequal(flow_rod1, fm));
i = loc_rod1.getInvariant();
im = i.getMatrix();
iv = i.getVector();
assert(isequal(im, [-1 0 0]));
assert(isequal(iv, -510));
% test end

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

% test
f = loc_no.getLinearFlow();
fm = f.getFlowMatrix();
assert(isequal(flow_no, fm));
i = loc_no.getInvariant();
im = i.getMatrix();
iv = i.getVector();
assert(isequal(im, [1 0 0]));
assert(isequal(iv, 550));
% test end

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

% test
f = loc_rod2.getLinearFlow();
fm = f.getFlowMatrix();
assert(isequal(flow_rod2, fm));
i = loc_rod2.getInvariant();
im = i.getMatrix();
iv = i.getVector();
assert(isequal(im, [-1 0 0]));
assert(isequal(iv, -510));
% test end


%-----------------------------------------------%
%              Location sink
%-----------------------------------------------%
% loc_sink = MHyProLocation();
% loc_sink.setName('sink');

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

% test
locT = rod1.getTransitions();
assert(length(locT) == 1);
lab1 = locT{1}.getLabels();
assert(isequal(lab1{1}.getName(), 'tran1'));
g = tran1.getGuard();
gm = g.getMatrix();
gv = g.getVector();
assert(isequal(gm, [1 0 0; -1 0 0]));
assert(isequal(gv, [510; -510]));
r = tran1.getReset();
rm = r.getMatrix(1);
rv = r.getVector(1);
assert(isequal(rm, [1 0 0; 0 0 0; 0 0 1]));
assert(isequal(rv, [0; 0; 0]));
% test end


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

% test
locT = noRod.getTransitions();
assert(length(locT) == 1);
lab1 = locT{1}.getLabels();
assert(isequal(lab1{1}.getName(), 'tran2'));
g = tran2.getGuard();
gm = g.getMatrix();
gv = g.getVector();
assert(isequal(gm, [1 0 0; -1 0 0; 0 -1 0]));
assert(isequal(gv, [550; -550; -20]));
r = tran2.getReset();
rm = r.getMatrix(1);
rv = r.getVector(1);
assert(isequal(rm, eye(3)));
assert(isequal(rv, [0; 0; 0]));
% test end


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

% test
locT = noRod.getTransitions();
assert(length(locT) == 2);
lab1 = locT{1}.getLabels();
lab2 = locT{2}.getLabels();
assert(isequal(lab1{1}.getName(), 'tran2'));
assert(isequal(lab2{1}.getName(), 'tran3'));
g = tran3.getGuard();
gm = g.getMatrix();
gv = g.getVector();
assert(isequal(gm, [1 0 0; -1 0 0; 0 0 -1]));
assert(isequal(gv, [550; -550; -20]));
r = tran3.getReset();
rm = r.getMatrix(1);
rv = r.getVector(1);
assert(isequal(rm, eye(3)));
assert(isequal(rv, [0; 0; 0]));
% test end

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


% test
locT = rod2.getTransitions();
assert(length(locT) == 1);
lab1 = locT{1}.getLabels();
assert(isequal(lab1{1}.getName(), 'tran4'));
g = tran4.getGuard();
gm = g.getMatrix();
gv = g.getVector();
assert(isequal(gm, [1 0 0; -1 0 0]));
assert(isequal(gv, [510; -510]));
r = tran4.getReset();
rm = r.getMatrix(1);
rv = r.getVector(1);
assert(isequal(rm, [1 0 0; 0 1 0; 0 0 0]));
assert(isequal(rv, [0; 0; 0]));
% test end


%-----------------------------------------------%
%              noRods --> sink
%-----------------------------------------------%

% tran5 = MHyProTransition();
% % Set guard: x = 550 & c1 <= 20 & c2 <= 20
% guard5 = MHyProCondition();
% guard5.setMatrix([1 0 0; -1 0 0; 0 1 0; 0 0 1]); % First set the matrix then the vector!?
% guard5.setVector([550; -550; 20; 20]);
%
% %tran5.setAggregation(2);
% tran5.setGuard(guard5);
% tran5.setSource(noRod);
% tran5.setTarget(sink);
% tran5.setReset(dummy_reset);
% tran5.setLabels({MHyProLabel('tran5')});
%
% noRod.addTransition(tran5);

% % test
% locT = noRod.getTransitions();
% assert(length(locT) == 3);
% lab1 = locT{1}.getLabels();
% lab2 = locT{2}.getLabels();
% lab3 = locT{3}.getLabels();
% assert(isequal(lab1{1}.getName(), 'tran2'));
% assert(isequal(lab2{1}.getName(), 'tran3'));
% assert(isequal(lab3{1}.getName(), 'tran5'));
% g = tran5.getGuard();
% gm = g.getMatrix();
% gv = g.getVector();
% assert(isequal(gm, [1 0 0; -1 0 0; 0 1 0; 0 0 1]));
% assert(isequal(gv, [550; -550; 20; 20]));
% r = tran5.getReset();
% rm = r.getMatrix(1);
% rv = r.getVector(1);
% assert(isequal(rm, eye(3)));
% assert(isequal(rv, [0; 0; 0]));
% test end


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

settings = struct('timeStep', 0.1, 'timeBound', 16, 'jumpDepth', 5);
reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(0);
%reach.settings();

tic;
flowpipes = reach.computeForwardReachability();
time = toc;
disp(['Time needed: ', num2str(time)]);
dim = [1 3];
reach.plot(flowpipes, dim);

end
