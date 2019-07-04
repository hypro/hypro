function VehiclePlatoonTest()

% Create Automaton
automaton = MHyProHAutomaton();
dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(10));
dummy_reset.setVector(zeros(10,1));

%-----------------------------------------------%
%              Location qc
%-----------------------------------------------%
loc_qc = MHyProLocation();
loc_qc.setName('qc');

% [e1, e1prime, a1, e2, e2prime, a2, e3, e3prime, a3, t]

% Set flow: x' = Ac * x & t' = 1
Ac = [0 1 0 0 0 0 0 0 0 0;...
        0 0 -1 0 0 0 0 0 0 0;...
        1.605 4.868 -3.5754 -0.8198 0.427 -0.045 -0.1942 0.3626 -0.0946 0;...
        0 0 0 0 1 0 0 0 0 0;...
        0 0 1 0 0 -1 0 0 0 0;...
        0.8718 3.814 -0.0754 1.1936 3.6258 -3.2396 -0.595 0.1294 -0.0796 0;...
        0 0 0 0 0 0 0 1 0 0;...
        0 0 0 0 0 1 0 0 -1 0;...
        0.7132 3.573 -0.0964 0.8472 3.2568 -0.0876 1.2726 3.072 -3.1356 0;...
        0 0 0 0 0 0 0 0 0 1];

loc_qc.setFlow(Ac);

% Set inv: t <= 2 
inv_qc = MHyProCondition([0 0 0 0 0 0 0 0 0 1], 2);
loc_qc.setInvariant(inv_qc);

%-----------------------------------------------%
%              Location qn
%-----------------------------------------------%
loc_qn = MHyProLocation();
loc_qn.setName('qn');

% Set flow: x' = An * x & t' = 1
% [e1, e1prime, a1, e2, e2prime, a2, e3, e3prime, a3, t]
An  = [0 1 0 0 0 0 0 0 0 0;...
        0 0 -1 0 0 0 0 0 0 0;...
        1.605 4.868 -3.5754 0 0 0 0 0 0 0;...
        0 0 0 0 1 0 0 0 0 0;...
        0 0 1 0 0 -1 0 0 0 0;...
        0 0 0 1.1936 3.6258 -3.2396 0 0 0 0;...
        0 0 0 0 0 0 0 1 0 0;...
        0 0 0 0 0 1 0 0 -1 0;...
        0.7132 3.573 -0.0964 0.8472 3.2568 -0.0876 1.2726 3.072 -3.1356 0;
        0 0 0 0 0 0 0 0 0 1];

loc_qn.setFlow(An);

% Set inv: t <= 2 
inv_qn = MHyProCondition([0 0 0 0 0 0 0 0 0 1], 2);
loc_qn.setInvariant(inv_qn);


qc = automaton.addLocation(loc_qc);
qn = automaton.addLocation(loc_qn);

%-----------------------------------------------%
%              Transitions
%-----------------------------------------------%

% qc --> qn
tran1 = MHyProTransition();
% Set guard: t >= 2
guard1 = MHyProCondition();
guard1.setMatrix([0 0 0 0 0 0 0 0 0 -1]); % First set the matrix then the vector!?
guard1.setVector(-2);
% Set reset: t := 0
reset = MHyProReset();
temp = eye(10);
temp(10,10) = 0;
reset.setMatrix(temp);
reset.setVector(zeros(10,1));

tran1.setAggregation(1);
tran1.setGuard(guard1);
tran1.setSource(qc);
tran1.setTarget(qn);
tran1.setReset(reset);
tran1.setLabels({MHyProLabel('tran1')});

qc.addTransition(tran1);

% qn --> qc
tran2 = MHyProTransition();
% Set guard: t >= 2
guard2 = MHyProCondition();
guard2.setMatrix([0 0 0 0 0 0 0 0 0 -1]);
guard2.setVector(-2);

tran2.setAggregation(1);
tran2.setGuard(guard2);
tran2.setSource(qn);
tran2.setTarget(qc);
tran2.setReset(reset);
tran2.setLabels({MHyProLabel('tran2')});

qn.addTransition(tran2);

%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% e1 = [0.9 1.1] e1prime = [0.9 1.1] a1 = [0.9 1.1] e2 = [0.9 1.1] e2prime
% =[0.9 1.1] a2 = [0.9 1.1] e3 = [0.9 1.1] e3prime = [0.9 1.1] a3 = [ 0.9 1.1]
% t = [0 0]
boxVector = [-0.9 * ones(9,1);0; 1.1*ones(9,1);0];
boxMatrix = [-1*eye(10); eye(10)];
         
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(qc, initialCond);

%-----------------------------------------------%
%                 Bad States
%-----------------------------------------------%

% unsafe: e1 >= 1.7 in qc and qn

% badState = MHyProCondition();
% badState.setMatrix([-1 0 0 0 0 0 0 0 0 0]); % First set the matrix then the vector!?
% badState.setVector(-1.7);
% badStates(1).loc = qc;
% badStates(1).cond = badState;
% badStates(2).loc = qn;
% badStates(2).cond = badState;
% 
% badState.setMatrix([1 0 0 0 0 0 0 0 0 0]); % First set the matrix then the vector!?
% badState.setVector(-1.7);
% 
% badStates(3).loc = qc;
% badStates(3).cond = badState;
% automaton.setLocalBadStates(badStates);


%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

settings = struct('timeStep', 0.02, 'timeBound', 12, 'jumpDepth', 2);
reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(0);
%reach.settings();

tic;
flowpipes = reach.computeForwardReachability();
time = toc;
disp(['Time needed: ', num2str(time)]);
dim = [4 7];
labs = ["e2", "e3"];
reach.plot(flowpipes, dim,labs);

end

