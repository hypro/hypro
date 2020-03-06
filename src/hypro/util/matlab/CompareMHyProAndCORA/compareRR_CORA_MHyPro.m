function compareRR_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff)

% Comparison for rod reactor benchmark

% SETTINGS:

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

HA = rod_reactor_HA_cora();
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';

% options
Zcenter = interval([510;20;20],[520;20;20]);
options.R0 = zonotope(Zcenter); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation

%options.intersectInvariant=1;

options.taylorTerms = tT;
options.zonotopeOrder = zO;
options.polytopeOrder = pO;
options.errorOrder=0;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.originContained = 0;

%set input:
for i = 1:3
    options.timeStepLoc{i} = timeStepC;
    options.uLoc{i} = 0;
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

% First location
options.startLoc = 2; %initial location
options.finalLoc = 0; %0: no final location
options.tStart = 0; %start time
options.tFinal = timeHorizon;

[HA] = reach(HA,options);

options.projectedDimensions = [1 3];
fig = figure();
hold on
options.plotType = 'b';
plot(HA,'reachableSet',options); %plot reachable set
plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Create Automaton
automaton = MHyProHAutomaton();
dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(4));
dummy_reset.setVector([0; 0; 0; 0]);

%-----------------------------------------------%
%              Location rod1
%-----------------------------------------------%
loc_rod1 = MHyProLocation();
loc_rod1.setName('rod1');

% Set flow: x' = 0.1x - 56 c1' = 1 c2' = 1 gc' = 1
flow_rod1 = [0.1 0 0 0 -56; 0 0 0 0 1; 0 0 0 0 1; 0 0 0 0 1; 0 0 0 0 0];
loc_rod1.setFlow(flow_rod1);

% Set inv: x >= 510 & gc <= timeHorizon
inv_rod1 = MHyProCondition([-1 0 0 0; 0 0 0 1], [-510;timeHorizon]);
loc_rod1.setInvariant(inv_rod1);

%-----------------------------------------------%
%              Location noRods
%-----------------------------------------------%
loc_no = MHyProLocation();
loc_no.setName('noRods');

% Set flow: x' = 0.1x - 50 c1' = 1 c2' = 1 gc' = 1
flow_no = [0.1 0 0 0 -50; 0 0 0 0 1; 0 0 0 0 1; 0 0 0 0 1; 0 0 0 0 0];
loc_no.setFlow(flow_no);

% Set inv: x <= 550 & gc <= timeHorizon
inv_no = MHyProCondition([1 0 0 0; 0 0 0 1], [550;timeHorizon]);
loc_no.setInvariant(inv_no);

%-----------------------------------------------%
%              Location rod2
%-----------------------------------------------%
loc_rod2 = MHyProLocation();
loc_rod2.setName('rod2');

% Set flow: x' = 0.1x - 60 c1' = 1 c2' = 1 gc' = 1
flow_rod2 = [0.1 0 0 0 -60; 0 0 0 0 1; 0 0 0 0 1; 0 0 0 0 1; 0 0 0 0 0];
loc_rod2.setFlow(flow_rod2);

% Set inv: x >= 510 & gc <= timeHorizon
inv_rod2 = MHyProCondition([-1 0 0 0; 0 0 0 1], [-510;timeHorizon]);
loc_rod2.setInvariant(inv_rod2);

%-----------------------------------------------%
%              Location sink
%-----------------------------------------------%
sink = MHyProLocation();
sink.setName('sink');
sink.setFlow(zeros(4));


%-----------------------------------------------%
%              Add locations to HA
%-----------------------------------------------%

rod1 = automaton.addLocation(loc_rod1);
rod2 = automaton.addLocation(loc_rod2);
noRod = automaton.addLocation(loc_no);
s = automaton.addLocation(sink);

%-----------------------------------------------%
%              rod1 --> noRods
%-----------------------------------------------%
tran1 = MHyProTransition();
% Set guard: x = 510
guard1 = MHyProCondition();
guard1.setMatrix([1 0 0 0; -1 0 0 0]);
guard1.setVector([510; -510]);
% Set reset: c1 := 0
reset1 = MHyProReset();
reset1.setMatrix([1 0 0 0; 0 0 0 0; 0 0 1 0; 0 0 0 1]);
reset1.setVector([0; 0; 0; 0]);

tran1.setAggregation(aggr);
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
guard2.setMatrix([1 0 0 0; -1 0 0 0; 0 -1 0 0]);
guard2.setVector([550; -550; -20]);

tran2.setAggregation(aggr);
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
guard3.setMatrix([1 0 0 0; -1 0 0 0; 0 0 -1 0]);
guard3.setVector([550; -550; -20]);

tran3.setAggregation(aggr);
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
guard4.setMatrix([1 0 0 0; -1 0 0 0]); % First set the matrix then the vector!?
guard4.setVector([510; -510]);
% Set reset: c2 := 0
reset4 = MHyProReset();
reset4.setMatrix([1 0 0 0; 0 1 0 0; 0 0 0 0; 0 0 0 1]);
reset4.setVector([0; 0; 0; 0]);

tran4.setAggregation(aggr);
tran4.setGuard(guard4);
tran4.setSource(rod2);
tran4.setTarget(noRod);
tran4.setReset(reset4);
tran4.setLabels({MHyProLabel('tran4')});

rod2.addTransition(tran4);

%-----------------------------------------------%
%              rod1 --> sink
%-----------------------------------------------%

% Set guard: gc == timeHorizon
sink_guard = MHyProCondition();
sink_guard.setMatrix([0 0 0 -1; 0 0 0 1]); % First set the matrix then the vector!?
sink_guard.setVector([-timeHorizon;timeHorizon]);


tran1s = MHyProTransition();
tran1s.setAggregation(0);
tran1s.setGuard(sink_guard);
tran1s.setSource(rod1);
tran1s.setTarget(s);
tran1s.setReset(dummy_reset);
tran1s.setLabels({MHyProLabel('tran1s')});

rod1.addTransition(tran1s);

%-----------------------------------------------%
%              rod2 --> sink
%-----------------------------------------------%

tran2s = MHyProTransition();
tran2s.setAggregation(0);
tran2s.setGuard(sink_guard);
tran2s.setSource(rod2);
tran2s.setTarget(s);
tran2s.setReset(dummy_reset);
tran2s.setLabels({MHyProLabel('tran2s')});

rod2.addTransition(tran2s);

%-----------------------------------------------%
%              noRod --> sink
%-----------------------------------------------%

tran3s = MHyProTransition();
tran3s.setAggregation(0);
tran3s.setGuard(sink_guard);
tran3s.setSource(noRod);
tran3s.setTarget(s);
tran3s.setReset(dummy_reset);
tran3s.setLabels({MHyProLabel('tran3s')});

noRod.addTransition(tran3s);
noRod.addTransition(tran3s);

%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% x = [510 520] c1 = [20 20] c2 =[20 20] gc = [0 0]
boxVector = [520; -510; 20; -20; 20; -20; 0; 0];
boxMatrix = [1 0 0 0; -1 0 0 0; 0 1 0 0; 0 -1 0 0; 0 0 1 0; 0 0 -1 0; 0 0 0 1; 0 0 0 -1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(noRod, initialCond);


%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

% Add basic settings
settings.timeBound = timeHorizon;
settings.jumpDepth = 20;

reacher = MHyProReach(automaton);
reacher.setSettings(settings);
reacher.setRepresentationType(setRepr);

flowpipes = reacher.computeForwardReachability();

% fig = figure();
dim = [1 3];
labs = ["x", "c2"];
reacher.plotComparison(flowpipes, dim, labs);
set(gca,'FontSize',15);
if diff == 2
    y = [60;60;41.1;41.1];
    x = [600;500;500;600];
    pgon = polyshape([x,y], 'Simplify', false);
    plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
elseif diff == 3
    y = [60;60;34.93;34.93];
    x = [600;500;500;600];
    pgon = polyshape([x,y], 'Simplify', false);
    plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
elseif diff == 4
    y = [60;60;40.86;40.86];
    x = [600;500;500;600];
    pgon = polyshape([x,y], 'Simplify', false);
    plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
elseif diff == 5
    k = 550 : 600;
    spec1 = 0*k + 50;
    upper = 15 + 0*k;
    k1 = [k, fliplr(k)];
    inBetweenUpper = [spec1, fliplr(upper)];
    fill(k1,inBetweenUpper,[0.831, 0, 0], 'FaceAlpha',0.5, 'EdgeColor','none');
end

% x=[550,550];
% y=[20,40];
% plot(x,y,'m')

if saveFig
    saveas(fig, fullfile(savePath,fname),'eps');
end
end