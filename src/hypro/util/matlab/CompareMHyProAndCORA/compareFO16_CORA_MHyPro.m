function compareFO16_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff)

% Comparison for filtered oscillator 16 benchmark

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

% Create Automaton
automaton = MHyProHAutomaton();
dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(19));
dummy_reset.setVector(zeros(19,1));

%-----------------------------------------------%
%              Location loc1
%-----------------------------------------------%
loc1 = MHyProLocation();
loc1.setName('loc1');

% Set flow:
flow_loc1 = [-2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1.4;...
             0 -1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -0.7;...
             5  0 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
loc1.setFlow(flow_loc1);

% Set inv: x <= 0 & y + 0.714286x >= 0 & gc <= timeHorizon
invMat = [1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
    -0.714286 -1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
    0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1];
inv_loc1 = MHyProCondition(invMat, [0;0;timeHorizon]);
loc1.setInvariant(inv_loc1);


%-----------------------------------------------%
%              Location loc2
%-----------------------------------------------%
loc2 = MHyProLocation();
loc2.setName('loc2');

flow_loc2 = [-2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -1.4;...
             0 -1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0.7;...
             5  0 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
loc2.setFlow(flow_loc2);

% Set inv: x <= 0 & y + 0.714286x <= 0 & gc <= timeHorizon
invMat = [1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
    0.714286 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
    0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1];
inv_loc2 = MHyProCondition(invMat, [0;0;timeHorizon]);
loc2.setInvariant(inv_loc2);

%-----------------------------------------------%
%              Location loc3
%-----------------------------------------------%
loc3 = MHyProLocation();
loc3.setName('loc3');

% Set flow:
flow_loc3 = [-2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1.4;...
             0 -1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -0.7;...
             5  0 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0  5 -5 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
loc3.setFlow(flow_loc3);

% Set inv: x >= 0 & y + 0.714286x >= 0 & gc <= timeHorizon
invMat = [-1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
    -0.714286 -1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
    0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1];
inv_loc3 = MHyProCondition(invMat, [0;0;timeHorizon]);
loc3.setInvariant(inv_loc3);

%-----------------------------------------------%
%              Location loc4
%-----------------------------------------------%
loc4 = MHyProLocation();
loc4.setName('loc4');

% Set flow:
flow_loc4 = [-2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -1.4;...
             0 -1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0.7;...
             5  0 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0  5 -5 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1];
loc4.setFlow(flow_loc4);

% Set inv: x >= 0 & y + 0.714286x <= 0 & gc <= timeHorizon
invMat = [-1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
    0.714286 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
    0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1];
inv_loc4 = MHyProCondition(invMat, [0;0;timeHorizon]);
loc4.setInvariant(inv_loc4);

%-----------------------------------------------%
%              Location sink
%-----------------------------------------------%
sink = MHyProLocation();
sink.setName('sink');
sink.setFlow(zeros(19));

l1 = automaton.addLocation(loc1);
l2 = automaton.addLocation(loc2);
l3 = automaton.addLocation(loc3);
l4 = automaton.addLocation(loc4);
s = automaton.addLocation(sink);

%-----------------------------------------------%
%              loc1 -> loc3
%-----------------------------------------------%

tran1 = MHyProTransition();
% Set guard: x = 0 & 0.714286x + y >= 0
guardMatrix = [1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
    -1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0; -0.714286 -1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
guard1 = MHyProCondition();
guard1.setMatrix(guardMatrix);
guard1.setVector([0;0;0]);

tran1.setAggregation(aggr);
tran1.setGuard(guard1);
tran1.setSource(l1);
tran1.setTarget(l3);
tran1.setReset(dummy_reset);
tran1.setLabels({MHyProLabel('tran1')});

l1.addTransition(tran1);

%-----------------------------------------------%
%              loc3 -> loc4
%-----------------------------------------------%

tran2 = MHyProTransition();
% Set guard: x >= 0 & 0.714286x + y = 0
guardMatrix = [-1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
    -0.714286 -1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
    0.714286 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
guard2 = MHyProCondition();
guard2.setMatrix(guardMatrix);
guard2.setVector([0;0;0]);

tran2.setAggregation(aggr);
tran2.setGuard(guard2);
tran2.setSource(l3);
tran2.setTarget(l4);
tran2.setReset(dummy_reset);
tran2.setLabels({MHyProLabel('tran2')});

l3.addTransition(tran2);

%-----------------------------------------------%
%              loc4 -> loc2
%-----------------------------------------------%

tran3 = MHyProTransition();
% Set guard: x = 0 & 0.714286x + y <= 0
guardMatrix = [-1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
                1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
                0.714286 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
guard3 = MHyProCondition();
guard3.setMatrix(guardMatrix);
guard3.setVector([0;0;0]);

tran3.setAggregation(aggr);
tran3.setGuard(guard3);
tran3.setSource(l4);
tran3.setTarget(l2);
tran3.setReset(dummy_reset);
tran3.setLabels({MHyProLabel('tran3')});

l4.addTransition(tran3);

%-----------------------------------------------%
%              loc2 -> loc1
%-----------------------------------------------%

tran4 = MHyProTransition();
% Set guard: x <= 0 & 0.714286x + y = 0
guardMatrix = [1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
        0.714286 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
        -0.714286 -1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
guard4 = MHyProCondition();
guard4.setMatrix(guardMatrix);
guard4.setVector([0;0;0]);

tran4.setAggregation(aggr);
tran4.setGuard(guard4);
tran4.setSource(l2);
tran4.setTarget(l1);
tran4.setReset(dummy_reset);
tran4.setLabels({MHyProLabel('tran4')});

l2.addTransition(tran4);

%-----------------------------------------------%
%              loc1 -> sink
%-----------------------------------------------%


% Set guard: gc == timeHorizon
guardMatrix = [0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -1;...
        0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1];
sink_guard = MHyProCondition();
sink_guard.setMatrix(guardMatrix);
sink_guard.setVector([-timeHorizon;timeHorizon]);

tran1s = MHyProTransition();
tran1s.setAggregation(0);
tran1s.setGuard(sink_guard);
tran1s.setSource(l1);
tran1s.setTarget(s);
tran1s.setReset(dummy_reset);
tran1s.setLabels({MHyProLabel('tran1s')});

l1.addTransition(tran1s);

%-----------------------------------------------%
%              loc2 -> sink
%-----------------------------------------------%

tran2s = MHyProTransition();
tran2s.setAggregation(0);
tran2s.setGuard(sink_guard);
tran2s.setSource(l2);
tran2s.setTarget(s);
tran2s.setReset(dummy_reset);
tran2s.setLabels({MHyProLabel('tran2s')});

l2.addTransition(tran2s);

%-----------------------------------------------%
%              loc3 -> sink
%-----------------------------------------------%

tran3s = MHyProTransition();
tran3s.setAggregation(0);
tran3s.setGuard(sink_guard);
tran3s.setSource(l3);
tran3s.setTarget(s);
tran3s.setReset(dummy_reset);
tran3s.setLabels({MHyProLabel('tran3s')});

l3.addTransition(tran3s);

%-----------------------------------------------%
%              loc4 -> sink
%-----------------------------------------------%

tran4s = MHyProTransition();
tran4s.setAggregation(0);
tran4s.setGuard(sink_guard);
tran4s.setSource(l4);
tran4s.setTarget(s);
tran4s.setReset(dummy_reset);
tran4s.setLabels({MHyProLabel('tran4s')});

l4.addTransition(tran4s);

%-----------------------------------------------%
%              Initial Set
%-----------------------------------------------%
%
boxVector = [0.3; 0.1;zeros(17,1); -0.2; 0.1; zeros(17,1)];
boxMatrix = [eye(19); -1*eye(19)];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(l3, initialCond);

%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

% Add basic settings
settings.timeBound = timeHorizon;
settings.jumpDepth = 5;

reacher = MHyProReach(automaton);
reacher.setSettings(settings);
reacher.setRepresentationType(setRepr);

flowpipes = reacher.computeForwardReachability();

fig = figure();
dim = [1 6];
labs = ["x", "f8x1"];
reacher.plotComparison(flowpipes, dim, labs);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

HA = filtered_oscillator_16_ha();
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';
Zdelta = [0.05;0.1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0];

% options
Zcenter = [0.25;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0];
options.R0 = zonotope([Zcenter,diag(Zdelta)]); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation

options.taylorTerms = tT;
options.zonotopeOrder = zO;
options.polytopeOrder = pO;

%options.intersectInvariant=1;
    
options.errorOrder=2;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.originContained = 0;

%set input:
for i = 1:4
    options.timeStepLoc{i} = timeStepC;
    options.uLoc{i} = 0;
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

% First location
options.startLoc = 3; %initial location
options.finalLoc = 0; %0: no final location
options.tStart = 0; %start time
options.tFinal = timeHorizon;

[HA] = reach(HA,options);

options.projectedDimensions = [6 2];

options.plotType = 'b';
plot(HA,'reachableSet',options); %plot reachable set
plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
set(gca,'FontSize',15);
if diff == 1
    y = [0.8;0.8;0.5;0.5];
    x = [1;-1;-1;1];
    pgon = polyshape([x,y], 'Simplify', false);
    plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
elseif diff == 2
    y = [0.8;0.8;0.48205;0.48205];
    x = [1;-1;-1;1];
    pgon = polyshape([x,y], 'Simplify', false);
    plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
elseif diff == 3
    y = [0.8;0.8;0.4641;0.4641];
    x = [1;-1;-1;1];
    pgon = polyshape([x,y], 'Simplify', false);
    plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
end
xlabel('f8x1');
ylabel('y');

if saveFig
    saveas(fig, fullfile(savePath,fname),'eps');
end
end
