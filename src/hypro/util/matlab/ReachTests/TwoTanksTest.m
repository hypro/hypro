function TwoTanksTest

% Create Automaton
automaton = MHyProHAutomaton();
dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(2));
dummy_reset.setVector([0; 0]);

%-----------------------------------------------%
%              Location loc1
%-----------------------------------------------%
loc_off_off = MHyProLocation();
loc_off_off.setName('off_off');

% Set flow: x1' = -x1 - 2 , x2' = x1
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

% Set flow: x1' = -x1 + 3, x2' = x1
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

% Set flow: x1' = -x1 - 2, x2' = x1 - x2 - 5 
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

% Set flow: x1' = -x1 + 3, x2' = x1 - x2 - 5
flowOn_On = [-1 0 3; 1 -1 -5; 0 0 0];
loc_on_on.setFlow(flowOn_On);

% Set inv: x1 <= 1 & x2 >= 0
inv_on_on = MHyProCondition([1 0 ; 0 -1], [1; 0]);
loc_on_on.setInvariant(inv_on_on);


l_ff = automaton.addLocation(loc_off_off);
l_nf = automaton.addLocation(loc_on_off);
l_fn = automaton.addLocation(loc_off_on);
l_nn = automaton.addLocation(loc_on_on);

%-----------------------------------------------%
%              off_off --> on_off
%-----------------------------------------------%

tran1 = MHyProTransition();
% x1 = -1
guard1 = MHyProCondition();
guardVector = [-1; 1];
guardMatrix = [1 0; -1 0];
guard1.setMatrix(guardMatrix);
guard1.setVector(guardVector);
tran1.setAggregation(1);
tran1.setGuard(guard1);
tran1.setReset(dummy_reset);
tran1.setSource(l_ff);
tran1.setTarget(l_nf);
tran1.setLabels({MHyProLabel('tran1')});
l_ff.addTransition(tran1);


%-----------------------------------------------%
%              off_off --> off_on
%-----------------------------------------------%

tran2 = MHyProTransition();
% x2 = 1
guard2 = MHyProCondition();
guardVector = [1; -1];
guardMatrix = [0 1; 0 -1];
guard2.setMatrix(guardMatrix);
guard2.setVector(guardVector);
tran2.setAggregation(1);
tran2.setGuard(guard2);
tran2.setReset(dummy_reset);
tran2.setSource(l_ff);
tran2.setTarget(l_fn);
tran2.setLabels({MHyProLabel('tran2')});

l_ff.addTransition(tran2);

%-----------------------------------------------%
%              on_off --> off_on
%-----------------------------------------------%

tran3 = MHyProTransition();
% x2 = 1
guard3 = MHyProCondition();
guardVector = [1; -1];
guardMatrix = [0 1; 0 -1];
guard3.setMatrix(guardMatrix);
guard3.setVector(guardVector);
tran3.setAggregation(1);
tran3.setReset(dummy_reset);
tran3.setGuard(guard3);
tran3.setSource(l_nf);
tran3.setTarget(l_fn);
tran3.setLabels({MHyProLabel('tran3')});

l_nf.addTransition(tran3);

%-----------------------------------------------%
%              off_on --> off_off
%-----------------------------------------------%

tran4 = MHyProTransition();
% x2 = 0
guard4 = MHyProCondition();
guardVector = [0; 0];
guardMatrix = [0 1; 0 -1];
guard4.setMatrix(guardMatrix);
guard4.setVector(guardVector);

tran4.setAggregation(1);
tran4.setReset(dummy_reset);
tran4.setGuard(guard4);
tran4.setSource(l_fn);
tran4.setTarget(l_ff);
tran4.setLabels({MHyProLabel('tran4')});

l_fn.addTransition(tran4);

%-----------------------------------------------%
%              off_on --> on_on
%-----------------------------------------------%

tran5 = MHyProTransition();
% x1 = -1
guard5 = MHyProCondition();
guardVector = [-1; 1];
guardMatrix = [1 0; -1 0];
guard5.setMatrix(guardMatrix);
guard5.setVector(guardVector);
tran5.setAggregation(1);
tran5.setGuard(guard5);
tran5.setReset(dummy_reset);
tran5.setSource(l_fn);
tran5.setTarget(l_nn);
tran5.setLabels({MHyProLabel('tran5')});

l_fn.addTransition(tran5);

%-----------------------------------------------%
%              on_on --> off_on
%-----------------------------------------------%

tran6 = MHyProTransition();
% x1 = 1
guard6 = MHyProCondition();
guardVector = [1; -1];
guardMatrix = [1 0; -1 0];
guard6.setMatrix(guardMatrix);
guard6.setVector(guardVector);
tran6.setAggregation(1);
tran6.setGuard(guard6);
tran6.setReset(dummy_reset);
tran6.setSource(l_nn);
tran6.setTarget(l_fn);
tran6.setLabels({MHyProLabel('tran6')});

l_nn.addTransition(tran6);

%-----------------------------------------------%
%              on_on --> on_off
%-----------------------------------------------%

tran7 = MHyProTransition();
% x2 = 0
guard7 = MHyProCondition();
guardVector = [0; 0];
guardMatrix = [0 1; 0 -1];
guard7.setMatrix(guardMatrix); 
guard7.setVector(guardVector);
tran7.setAggregation(1);
tran7.setGuard(guard7);
tran7.setReset(dummy_reset);
tran7.setSource(l_nn);
tran7.setTarget(l_nf);
tran7.setLabels({MHyProLabel('tran7')});

l_nn.addTransition(tran7);

%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% x1 = [1.5, 2.5] x2 = [1, 1]
boxVector = [2.5; -1.5; 1; -1;];
boxMatrix = [1 0; -1 0; 0 1; 0 -1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(l_fn, initialCond);

%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

settings = struct('timeStep', 0.01, 'timeBound', 5, 'jumpDepth', 2);
reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(0);
reach.settings();

tic;
flowpipes = reach.computeForwardReachability();
time = toc;
disp(['Time needed: ', num2str(time)]);
dim = [1 2];
reach.plot(flowpipes, dim);

end




