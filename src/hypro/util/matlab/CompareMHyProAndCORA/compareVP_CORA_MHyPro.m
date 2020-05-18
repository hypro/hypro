function compareVP_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff)

% Comparison for vehicle platoon benchmark

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
disp('CORA')

HA = vehicle_platoon_ha();
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';
Zdelta = [0.1*ones(9,1);0];

% options
Zcenter = ones(10,1);
Zcenter(10) = 0;
options.R0 = zonotope([Zcenter,diag(Zdelta)]); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation

%options.intersectInvariant=1;

options.taylorTerms = tT;
options.zonotopeOrder = zO;
options.polytopeOrder = pO;
options.errorOrder=2;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.originContained = 0;

%set input:
for i = 1:2
    options.timeStepLoc{i} = timeStepC;
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

figure();
hold on;
options.projectedDimensions = [1 7];
options.plotType = 'b';
plot(HA,'reachableSet',options); %plot reachable set
set(gca,'FontSize',15);

%plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
if diff == 1
    y = [2;2;1.7;1.7];
    x = [1.8;0;0;1.8];
    pgon = polyshape([x,y], 'Simplify', false);
    plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
elseif diff == 2
    y = [-0.7;-0.7;-1;-1];
    x = [2.5;-1;-1;2.5];
    pgon = polyshape([x,y], 'Simplify', false);
    plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
elseif diff == 3
    y = [2;2;1.7;1.7];
    x = [1.8;0;0;1.8];
    pgon = polyshape([x,y], 'Simplify', false);
    plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
elseif diff == 4
    k = 0.8 : 1.8;
    spec1 = 0.855*k -0.05;
    upper = 0.6 + 0*k;
    hold on;
    k1 = [k, fliplr(k)];
    inBetweenUpper = [spec1, fliplr(upper)];
    fill(k1,inBetweenUpper,[0.831, 0, 0], 'FaceAlpha',0.5, 'EdgeColor','none');
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



% Create Automaton
automaton = MHyProHAutomaton();
dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(11));
dummy_reset.setVector(zeros(11,1));

%-----------------------------------------------%
%              Location qc
%-----------------------------------------------%
loc_qc = MHyProLocation();
loc_qc.setName('qc');

% [e1, e1prime, a1, e2, e2prime, a2, e3, e3prime, a3, t, gc]

% Set flow: x' = Ac * x & t' = 1 & gc' = 1
Ac = [0 1 0 0 0 0 0 0 0 0 0 0;...
        0 0 -1 0 0 0 0 0 0 0 0 0;...
        1.605 4.868 -3.5754 -0.8198 0.427 -0.045 -0.1942 0.3626 -0.0946 0 0 0;...
        0 0 0 0 1 0 0 0 0 0 0 0;...
        0 0 1 0 0 -1 0 0 0 0 0 0;...
        0.8718 3.814 -0.0754 1.1936 3.6258 -3.2396 -0.595 0.1294 -0.0796 0 0 0;...
        0 0 0 0 0 0 0 1 0 0 0 0;...
        0 0 0 0 0 1 0 0 -1 0 0 0;...
        0.7132 3.573 -0.0964 0.8472 3.2568 -0.0876 1.2726 3.072 -3.1356 0 0 0;...
        0 0 0 0 0 0 0 0 0 0 0 1;...
        0 0 0 0 0 0 0 0 0 0 0 1;...
        0 0 0 0 0 0 0 0 0 0 0 0];

loc_qc.setFlow(Ac);

% Set inv: t <= 2 & gc <= timeHorizon
inv_qc = MHyProCondition([0 0 0 0 0 0 0 0 0 1 0; 0 0 0 0 0 0 0 0 0 0 1], [2;timeHorizon]);
loc_qc.setInvariant(inv_qc);

%-----------------------------------------------%
%              Location qn
%-----------------------------------------------%
loc_qn = MHyProLocation();
loc_qn.setName('qn');

% Set flow: x' = An * x & t' = 1 & gc' = 1
% [e1, e1prime, a1, e2, e2prime, a2, e3, e3prime, a3, t]
An  = [0 1 0 0 0 0 0 0 0 0 0 0;...
        0 0 -1 0 0 0 0 0 0 0 0 0;...
        1.605 4.868 -3.5754 0 0 0 0 0 0 0 0 0;...
        0 0 0 0 1 0 0 0 0 0 0 0;...
        0 0 1 0 0 -1 0 0 0 0 0 0;...
        0 0 0 1.1936 3.6258 -3.2396 0 0 0 0 0 0;...
        0 0 0 0 0 0 0 1 0 0 0 0;...
        0 0 0 0 0 1 0 0 -1 0 0 0;...
        0.7132 3.573 -0.0964 0.8472 3.2568 -0.0876 1.2726 3.072 -3.1356 0 0 0;
        0 0 0 0 0 0 0 0 0 0 0 1;...
        0 0 0 0 0 0 0 0 0 0 0 1;...
        0 0 0 0 0 0 0 0 0 0 0 0];

loc_qn.setFlow(An);

% Set inv: t <= 2  & gc <= timeHorizon
inv_qn = MHyProCondition([0 0 0 0 0 0 0 0 0 1 0; 0 0 0 0 0 0 0 0 0 0 1], [2;timeHorizon]);
loc_qn.setInvariant(inv_qn);

%-----------------------------------------------%
%              Location sink
%-----------------------------------------------%
sink = MHyProLocation();
sink.setName('sink');
sink.setFlow(zeros(11));


qc = automaton.addLocation(loc_qc);
qn = automaton.addLocation(loc_qn);
s = automaton.addLocation(sink);

%-----------------------------------------------%
%              Transitions
%-----------------------------------------------%

% qc --> qn
tran1 = MHyProTransition();
% Set guard: t >= 2
guard1 = MHyProCondition();
guard1.setMatrix([0 0 0 0 0 0 0 0 0 -1 0]);
guard1.setVector(-2);
% Set reset: t := 0
reset = MHyProReset();
temp = eye(11);
temp(10,10) = 0;
reset.setMatrix(temp);
reset.setVector(zeros(11,1));

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
guard2.setMatrix([0 0 0 0 0 0 0 0 0 -1 0]);
guard2.setVector(-2);

tran2.setAggregation(aggr);
tran2.setGuard(guard2);
tran2.setSource(qn);
tran2.setTarget(qc);
tran2.setReset(reset);
tran2.setLabels({MHyProLabel('tran2')});
qn.addTransition(tran2);

% qn --> sink

sink_guard = MHyProCondition();
sink_guard.setMatrix([0 0 0 0 0 0 0 0 0 0 -1; 0 0 0 0 0 0 0 0 0 0 1]);
sink_guard.setVector([-timeHorizon;timeHorizon]);

tran1s = MHyProTransition();
tran1s.setAggregation(0);
tran1s.setGuard(sink_guard);
tran1s.setSource(qn);
tran1s.setTarget(s);
tran1s.setReset(dummy_reset);
tran1s.setLabels({MHyProLabel('tran1s')});
qn.addTransition(tran1s);

% qc --> sink

tran2s = MHyProTransition();
tran2s.setAggregation(0);
tran2s.setGuard(sink_guard);
tran2s.setSource(qc);
tran2s.setTarget(s);
tran2s.setReset(dummy_reset);
tran2s.setLabels({MHyProLabel('tran2s')});
qc.addTransition(tran2s);

%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% e1 = [0.9 1.1] e1prime = [0.9 1.1] a1 = [0.9 1.1] e2 = [0.9 1.1] e2prime
% =[0.9 1.1] a2 = [0.9 1.1] e3 = [0.9 1.1] e3prime = [0.9 1.1] a3 = [ 0.9 1.1]
% t = [0 0] gc = [0 0]
boxVector = [-0.9 * ones(9,1);0; 0; 1.1*ones(9,1);0;0];
boxMatrix = [-1*eye(11); eye(11)];
         
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(qc, initialCond);

%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

% Add basic settings
settings.timeBound = 12;
settings.jumpDepth = 20;

reacher = MHyProReach(automaton);
reacher.setSettings(settings);
reacher.setRepresentationType(setRepr);

flowpipes = reacher.computeForwardReachability();


dim = [1 7];
labs = ["e1", "e3"];
reacher.plotComparison(flowpipes, dim, labs);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


if saveFig
    saveas(fig, fullfile(savePath,fname),'eps');
end
end

