function carMHyProTest

% Create Automaton
automaton = MHyProHAutomaton();

%-----------------------------------------------%
%              Location acc
%-----------------------------------------------%
loc_acc = MHyProLocation();
loc_acc.setName('acc');

% Set flow: v' = 5 d' = 19.44 - v t' = 1
dynAcc = [0 0 0 5; -1 0 0 19.44; 0 0 0 1; 0 0 0 0];
loc_acc.setFlow(dynAcc);

% Set inv: d >= 20
invAcc = MHyProCondition([0 -1 0], -20);
loc_acc.setInvariant(invAcc);

% test
f = loc_acc.getLinearFlow();
fm = f.getFlowMatrix();
assert(isequal(dynAcc, fm));
i = loc_acc.getInvariant();
im = i.getMatrix();
iv = i.getVector();
assert(isequal(im, [0 -1 0]));
assert(isequal(iv, -20));
% test end


%-----------------------------------------------%
%              Location brake
%-----------------------------------------------%
loc_brake = MHyProLocation();
loc_brake.setName('brake');

% Set flow: v' = -7 d' = 19.44 - v t' = 1
dynBrake = [0 0 0 -7; -1 0 0 19.44; 0 0 0 1; 0 0 0 0];
loc_brake.setFlow(dynBrake);

% Set inv: v >= 0
invBrake = MHyProCondition([-1 0 0], 0);
loc_brake.setInvariant(invBrake);

% test
f = loc_brake.getLinearFlow();
fm = f.getFlowMatrix();
assert(isequal(dynBrake, fm));
i = loc_brake.getInvariant();
im = i.getMatrix();
iv = i.getVector();
assert(isequal(im, [-1 0 0]));
assert(isequal(iv, 0));
% test end


%-----------------------------------------------%
%              Location idle
%-----------------------------------------------%
loc_idle = MHyProLocation();
loc_idle.setName('idle');

% Set flow: v' = 0 d' = 19.44 - v t' = 1
dynIdle = [0 0 0 0; -1 0 0 19.44; 0 0 0 1; 0 0 0 0];
loc_idle.setFlow(dynIdle);

% Set inv: d >= 20
invIdle = MHyProCondition([0 -1 0], -20);
loc_idle.setInvariant(invIdle);

% test
f = loc_idle.getLinearFlow();
fm = f.getFlowMatrix();
assert(isequal(dynIdle, fm));
i = loc_idle.getInvariant();
im = i.getMatrix();
iv = i.getVector();
assert(isequal(im, [0 -1 0]));
assert(isequal(iv, -20));
% test end

lAcc = automaton.addLocation(loc_acc);
lBrake = automaton.addLocation(loc_brake);
lIdle = automaton.addLocation(loc_idle);

%-----------------------------------------------%
%              acc -> brake
%-----------------------------------------------%

tran1 = MHyProTransition();
tran1.setAggregation(1);
tran1.setSource(lAcc);
tran1.setTarget(lBrake);
tran1.setLabels({MHyProLabel('tran1')});
lAcc.addTransition(tran1);

% test
locT = lAcc.getTransitions();
assert(length(locT) == 1);
lab1 = locT{1}.getLabels();
assert(isequal(lab1{1}.getName(), 'tran1'));
% test end


%-----------------------------------------------%
%              brake -> acc
%-----------------------------------------------%

tran2 = MHyProTransition();
% d >= 20
guard2 = MHyProCondition();
guard2.setMatrix([0 -1 0]);
guard2.setVector(-20);
tran2.setGuard(guard2);
tran2.setAggregation(1);
tran2.setSource(lBrake);
tran2.setTarget(lAcc);
tran2.setLabels({MHyProLabel('tran2')});
lBrake.addTransition(tran2);

% test
locT = lBrake.getTransitions();
assert(length(locT) == 1);
lab1 = locT{1}.getLabels();
assert(isequal(lab1{1}.getName(), 'tran2'));
g = tran2.getGuard();
assert(g == guard2);
s = tran2.getSource();
t = tran2.getTarget();
assert(s == lBrake);
assert(t == lAcc);
% test end

%-----------------------------------------------%
%              brake -> idle
%-----------------------------------------------%

tran3 = MHyProTransition();
tran3.setAggregation(1);
tran3.setSource(lBrake);
tran3.setTarget(lIdle);
tran3.setLabels({MHyProLabel('tran3')});
lBrake.addTransition(tran3);

% test
locT = lBrake.getTransitions();
assert(length(locT) == 2);
lab1 = locT{1}.getLabels();
lab2 = locT{2}.getLabels();
assert(isequal(lab1{1}.getName(), 'tran2'));
assert(isequal(lab2{1}.getName(), 'tran3'));
s = tran3.getSource();
t = tran3.getTarget();
assert(s == loc_brake);
assert(t == loc_idle);
% test end

%-----------------------------------------------%
%              idle -> acc
%-----------------------------------------------%

tran4 = MHyProTransition();
% d >= 20
guard4 = MHyProCondition();
guard4.setMatrix([0 -1 0]);
guard4.setVector(-20);
tran4.setGuard(guard4);
tran4.setAggregation(1);
tran4.setSource(lIdle);
tran4.setTarget(lAcc);
tran4.setLabels({MHyProLabel('tran4')});
lIdle.addTransition(tran4);

% test
locT = lIdle.getTransitions();
assert(length(locT) == 1);
lab1 = locT{1}.getLabels();
assert(isequal(lab1{1}.getName(), 'tran4'));
s = tran4.getSource();
t = tran4.getTarget();
assert(s == loc_idle);
assert(t == loc_acc);
% test end



%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% v = 13.88 d = 50 t = 0
boxVector = [13.88; -13.88; 50; -50; 0; 0];
boxMatrix = [1 0 0; -1 0 0; 0 1 0; 0 -1 0; 0 0 1; 0 0 -1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(lAcc, initialCond);

%test
locs = automaton.getLocations();
assert(length(locs) == 3);
assert(isequal(locs{1}.getName(), 'acc'));
assert(isequal(locs{2}.getName(), 'brake'));
assert(isequal(locs{3}.getName(), 'idle'));
initialMapping = automaton.getInitialStates();
assert(length(initialMapping) == 1);
iCond = initialMapping(1).cond;
assert(iCond == initialCond);
iLoc = initialMapping(1).loc;
assert(iLoc == loc_acc);
%test end

%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

settings = struct('timeStep', 0.1, 'timeBound', 10, 'jumpDepth', 10);
reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(0);
reach.settings();

tic;
flowpipes = reach.computeForwardReachability();
time = toc;
disp(['Time needed: ', num2str(time)]);
dim = [3 2];
reach.plot(flowpipes, dim);

end