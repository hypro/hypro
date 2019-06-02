% Two tanks benchmark

% Create Automaton
automaton = MHyProHAutomaton();

%-----------------------------------------------%
%              Location off_off
%-----------------------------------------------%
loc_off_off = MHyProLocation();
loc_off_off.setName('off_off');

% Set flow: x1' = -x1 - 2 + u, x2' = x1 + u
flowOff_Off = [-1 0 -2; 1 0 0; 0 0 0];
loc_off_off.setFlow(flowOff_Off);

% Set inv: x1 >= -1 & x2 <= 1
inv_off_off = MHyProCondition([-1 0; 0 1], [1; 1]);
loc_off_off.setInvariant(inv_off_off);

%-----------------------------------------------%
%              Location on_off
%-----------------------------------------------%
loc_on_off = MHyProLocation();
loc_on_off.setName('on_off');

% Set flow: x1' = -x1 + 3 + u, x2' = x1 + u
flowOn_Off = [-1 0 3; 1 0 0; 0 0 0];
loc_on_off.setFlow(flowOn_Off);

% Set inv: x2 <= 1
inv_on_off = MHyProCondition([0 1], 1);
loc_on_off.setInvariant(inv_on_off);

%-----------------------------------------------%
%              Location off_on
%-----------------------------------------------%
loc_off_on = MHyProLocation();
loc_off_on.setName('off_on');

% Set flow: x1' = -x1 - 2 + u, x2' = x1 - x2 - 5 + u
flowOff_On = [-1 0 -2; 1 -1 -5; 0 0 0];
loc_off_on.setFlow(flowOff_On);

% Set inv: x1 >= -1 & x2 >= 0
inv_off_on = MHyProCondition([-1 0 ; 0 -1], [1; 0]);
loc_off_on.setInvariant(inv_off_on);

%-----------------------------------------------%
%              Location on_on
%-----------------------------------------------%
loc_on_on = MHyProLocation();
loc_on_on.setName('on_on');

% Set flow: x1' = -x1 + 3 + u, x2' = x1 - x2 - 5 + u
flowOn_On = [-1 0 3; 1 -1 -5; 0 0 0];
loc_on_on.setFlow(flowOn_On);

% Set inv: x1 <= -1 & x2 >= 0
inv_on_on = MHyProCondition([1 0 ; 0 -1], [-1; 0]);
loc_on_on.setInvariant(inv_on_on);

%-----------------------------------------------%
%              Transitions
%-----------------------------------------------%

% off_off --> on_off
tran1 = MHyProTransition();
% x1 = -1
guard1 = MHyProCondition();
guardVector = [-1; 1];
guardMatrix = [1 0; -1 0];
guard1.setMatrix(guardMatrix); % First set the matrix then the vector!?
guard1.setVector(guardVector);

tran1.setAggregation(2);
tran1.setGuard(guard1);
tran1.setSource(loc_off_off);
tran1.setTarget(loc_on_off);
tran1.setLabels({MHyProLabel('tran1')});

loc_off_off.addTransition(tran1);

% off_off --> off_on
tran2 = MHyProTransition();
% x2 = 1
guard2 = MHyProCondition();
guardVector = [1; -1];
guardMatrix = [0 1; 0 -1];
guard2.setMatrix(guardMatrix); % First set the matrix then the vector!?
guard2.setVector(guardVector);

tran2.setAggregation(2);
tran2.setGuard(guard2);
tran2.setSource(loc_off_off);
tran2.setTarget(loc_off_on);
tran2.setLabels({MHyProLabel('tran2')});

loc_off_off.addTransition(tran2);

% on_off --> off_on
tran3 = MHyProTransition();
% x2 = 1
guard3 = MHyProCondition();
guardVector = [1; -1];
guardMatrix = [0 1; 0 -1];
guard3.setMatrix(guardMatrix); % First set the matrix then the vector!?
guard3.setVector(guardVector);

tran3.setAggregation(2);
tran3.setGuard(guard3);
tran3.setSource(loc_on_off);
tran3.setTarget(loc_off_on);
tran3.setLabels({MHyProLabel('tran3')});

loc_on_off.addTransition(tran3);

% off_on --> off_off
tran4 = MHyProTransition();
% x2 = 0
guard4 = MHyProCondition();
guardVector = [0; 0];
guardMatrix = [0 1; 0 -1];
guard4.setMatrix(guardMatrix); % First set the matrix then the vector!?
guard4.setVector(guardVector);

tran4.setAggregation(2);
tran4.setGuard(guard4);
tran4.setSource(loc_off_on);
tran4.setTarget(loc_off_off);
tran4.setLabels({MHyProLabel('tran4')});

loc_off_on.addTransition(tran4);

% off_on --> on_on
tran5 = MHyProTransition();
% x1 = -1
guard5 = MHyProCondition();
guardVector = [-1; 1];
guardMatrix = [1 0; -1 0];
guard5.setMatrix(guardMatrix); % First set the matrix then the vector!?
guard5.setVector(guardVector);

tran5.setAggregation(2);
tran5.setGuard(guard5);
tran5.setSource(loc_off_on);
tran5.setTarget(loc_on_on);
tran5.setLabels({MHyProLabel('tran5')});

loc_off_on.addTransition(tran5);

% on_on --> off_on
tran6 = MHyProTransition();
% x1 = 1
guard6 = MHyProCondition();
guardVector = [1; -1];
guardMatrix = [1 0; -1 0];
guard6.setMatrix(guardMatrix); % First set the matrix then the vector!?
guard6.setVector(guardVector);

tran6.setAggregation(2);
tran6.setGuard(guard6);
tran6.setSource(loc_on_on);
tran6.setTarget(loc_off_on);
tran6.setLabels({MHyProLabel('tran6')});

loc_on_on.addTransition(tran6);

% on_on --> on_off
tran7 = MHyProTransition();
% x2 = 0
guard7 = MHyProCondition();
guardVector = [0; 0];
guardMatrix = [0 1; 0 -1];
guard7.setMatrix(guardMatrix); % First set the matrix then the vector!?
guard7.setVector(guardVector);

tran7.setAggregation(2);
tran7.setGuard(guard7);
tran7.setSource(loc_on_on);
tran7.setTarget(loc_on_off);
tran7.setLabels({MHyProLabel('tran7')});

loc_on_on.addTransition(tran7);

%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% x1 = [1.5 2.5] x2 = [1 1]
boxVector = [2.5; -1.5; 1; -1];
boxMatrix = [1 0; -1 0; 0 1; 0 -1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(loc_off_off, initialCond);

automaton.addLocation(loc_off_off);
automaton.addLocation(loc_on_off);
automaton.addLocation(loc_off_on);
automaton.addLocation(loc_on_on);


%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

settings = struct('timeStep', 0.01, 'timeBound', 2, 'jumpDepth', 2);
reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(0);
reach.settings();

tic;
flowpipes = reach.computeForwardReachability();
time = toc;
disp(['Time needed: ', num2str(time)]);
dim = [1 2];
reach.plot(flowpipes, 0, dim);




