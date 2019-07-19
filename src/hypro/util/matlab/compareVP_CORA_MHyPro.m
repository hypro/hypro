function compareVP_CORA_MHyPro()

timeStep =0.02;
timeHorizon = 0.5;
tT = 10;
zO = 20;
pO = 10;


disp("MHyPro")
aggr = 2;
setRepr = 2;
clustering = -1;


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
guard1.setMatrix([0 0 0 0 0 0 0 0 0 -1]);
guard1.setVector(-2);
% Set reset: t := 0
reset = MHyProReset();
temp = eye(10);
temp(10,10) = 0;
reset.setMatrix(temp);
reset.setVector(zeros(10,1));

tran1.setAggregation(aggr);
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

tran2.setAggregation(aggr);
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
%                 Reachability
%-----------------------------------------------%

% Add basic settings
settings.timeBound = timeHorizon;
settings.jumpDepth = 5;
settings.timeStep = timeStep;
settings.clustering = clustering;

reacher = MHyProReach(automaton);
reacher.setSettings(settings);
reacher.setRepresentationType(setRepr);

flowpipes = reacher.computeForwardReachability();

dim = [1 7];
labs = ["e1", "e3"];
ext = 'png';
reacher.plotComparison(flowpipes, dim, labs,0,'','','');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

disp('CORA')

HA = vehicle_platoon_ha();
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';
Zdelta = [0.1*ones(9,1);0];

% options
Zcenter = ones(10,1);
options.R0 = zonotope([Zcenter,diag(Zdelta)]); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation

options.taylorTerms = tT;
options.zonotopeOrder = zO;
options.polytopeOrder = pO;
options.errorOrder=2;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.originContained = 0;

%set input:
for i = 1:2
    options.timeStepLoc{i} = timeStep;
    options.uLoc{i} = 0;
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

% First location
options.startLoc = 1; %initial location
options.finalLoc = 0; %0: no final location
options.tStart = 0; %start time
options.tFinal = timeHorizon;

[HA] = reach(HA,options);


options.projectedDimensions = [1 7];
options.plotType = 'b';
plot(HA,'reachableSet',options); %plot reachable set
%plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
xlabel('e1');
ylabel('e3');


end

