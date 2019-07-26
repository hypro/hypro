function compareBB_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff)


% MHyPro
settings.timeStep = mhStrat.timeStep;
settings.clustering = mhStrat.clustering;
aggr = mhStrat.aggr;
setRepr = mhStrat.setRepr;

% CORA
timeStepC = cStrat.timeStep;
tT = cStrat.tT;
zO = cStrat.zO;
pO = cStrat.pO;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

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

% Set invariant x >= 0 & t <= 4
inv = MHyProCondition([-1 0 0; 0 0 1], [0; 4]);
loc.setInvariant(inv);

%-----------------------------------------------%
%                 loc sink
%-----------------------------------------------%

loc_sink = MHyProLocation();
loc_sink.setName('loc');

% Set flow:
% x' = 0 v' = 0 t' = 0
flowMatrix = zeros(4);
loc_sink.setFlow(flowMatrix);

% % Set invariant x >= 0 & t <= 4
% inv = MHyProCondition([-1 0 0; 0 0 1], [0; 4]);
% loc.setInvariant(inv);

l = automaton.addLocation(loc);
s = automaton.addLocation(loc_sink);

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
%                loc -> loc_sink
%-----------------------------------------------%
tran = MHyProTransition();
% Set guard:
% t == 4
guard = MHyProCondition();
guard.setMatrix([ 0 0 -1; 0 0 1]); % First set the matrix then the vector!?
guard.setVector([-4;4]);

% Set reset
reset = MHyProReset();
reset.setMatrix(eye(3));
reset.setVector([0;0;0]);

tran.setAggregation(0);
tran.setGuard(guard);
tran.setSource(l);
tran.setTarget(l);
tran.setReset(reset);
tran.setLabels({MHyProLabel('t1')});

s.addTransition(tran);


%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% Create initial set
% x = [10, 10.2] v = 0 t = 0 
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

reacher = MHyProReach(automaton);
reacher.setSettings(settings);
reacher.setRepresentationType(setRepr);

flowpipes = reacher.computeForwardReachability();

dim = [2 1];
labs = ["v", "x"];
fig = figure();
hold on
reacher.plotComparison(flowpipes, dim, labs);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

disp('CORA');

HA = cora_bouncing_ball_ha();
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
    options.timeStepLoc{i} = timeStepC;
    options.uLoc{i} = 0;
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

[HA] = reach(HA,options);

options.projectedDimensions = [2 1];
options.plotType = 'b';
plot(HA,'reachableSet',options); %plot reachable set
plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    if diff == 1
        x = [15;15;10.7;10.7];
        y = [15;-2;-2;15];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    elseif diff == 2
        x = [15;15;10.6569;10.6569];
        y = [15;-2;-2;15];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    elseif diff == 3
        x = [15;15;10.6138;10.6138];
        y = [15;-2;-2;15];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    end

if saveFig
    saveas(fig, fullfile(savePath,fname),'png');
end

end
