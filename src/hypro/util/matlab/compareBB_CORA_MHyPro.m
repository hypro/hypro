function compareBB_CORA_MHyPro()

timeStep =0.03;
timeHorizon = 4;
tT = 10;
zO = 20;
pO = 10;


disp("MHyPro")
aggr = 2;
setRepr = 2;
clustering = 5;

% Create Automaton
automaton = MHyProHAutomaton();

%-----------------------------------------------%
%                 loc loc_1
%-----------------------------------------------%
loc = MHyProLocation();
loc.setName('loc');

% Set flow:
% x' = v v' = -9.81 t' = 1
flowMatrix = [0 1 0 0; 0 0 0 -9.81;0 0 0 1; 0 0 0 0];
loc.setFlow(flowMatrix);

% Set invariant x >= 0
inv = MHyProCondition([-1 0 0], 0);
loc.setInvariant(inv);

l = automaton.addLocation(loc);

%-----------------------------------------------%
%                loc -> loc
%-----------------------------------------------%
tran = MHyProTransition();
% Set guard:
% x = 0 & v <= 0
guard = MHyProCondition();
guard.setMatrix([ -1 0 0; 1 0 0; 0 1 0]); % First set the matrix then the vector!?
guard.setVector([0;0;0]);

% Set reset
% x:= x v:= -0.75v
reset = MHyProReset();
reset.setMatrix([1 0 0; 0 -0.75 0; 0 0 1]);
reset.setVector([0;0;0]);

tran.setAggregation(aggr);
tran.setGuard(guard);
tran.setSource(l);
tran.setTarget(l);
tran.setReset(reset);
tran.setLabels({MHyProLabel('t1')});

l.addTransition(tran);


%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% Create initial set
% x = [10, 10.2] v = 0
boxVector = [-10; 10.2; 0; 0; 0; 0];
boxMatrix = [-1 0 0; 1 0 0; 0 1 0; 0 -1 0; 0 0 -1; 0 0 1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(l, initialCond);

%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

% Add basic settings
settings.timeBound = timeHorizon;
settings.jumpDepth = 2;
settings.timeStep = timeStep;
settings.clustering = clustering;

reacher = MHyProReach(automaton);
reacher.setSettings(settings);
reacher.setRepresentationType(setRepr);

flowpipes = reacher.computeForwardReachability();

dim = [2 1];
labs = ["v", "x"];
reacher.plotComparison(flowpipes, dim, labs);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

disp('CORA');

HA = bouncing_ball_ha();
Zdelta = [0.1;0];


% options
Zcenter = [10.1;0];
options.R0 = zonotope([Zcenter,diag(Zdelta)]); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation

% First location
options.startLoc = 1; %initial location
options.finalLoc = 0; %0: no final location
options.tStart = 0; %start time
options.tFinal = timeHorizon;

options.taylorTerms = tT;
options.zonotopeOrder = zO;
options.polytopeOrder = pO;

options.errorOrder=2;
options.maxProjectionError=0.1;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';
options.originContained = 0;

%set input:
for i = 1:1
    options.timeStepLoc{i} = timeStep;
    options.uLoc{i} = [0;0];
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

[HA] = reach(HA,options);

options.projectedDimensions = [2 1];
options.plotType = 'b';
plot(HA,'reachableSet',options); %plot reachable set
plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set


