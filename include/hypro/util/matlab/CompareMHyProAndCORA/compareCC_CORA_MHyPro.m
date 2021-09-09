function compareCC_CORA_MHyPro(mhStrat,cStrat, timeHorizon, saveFig, fname, savePath, diff)

% Comparison for cruise controll benchmark

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
dummy_reset.setMatrix(eye(4));
dummy_reset.setVector([0; 0; 0; 0]);

%-----------------------------------------------%
%              Location loc1
%-----------------------------------------------%
loc_1 = MHyProLocation();
loc_1.setName('loc1');

% Set flow: v' = -t -2.5 x' = 0 t' = 1 gc' = 1
flow_1 = [0 0 -1 0 -2.5;...
          0 0 0 0 0;...
          0 0 0 0 1;...
          0 0 0 0 1;...
          0 0 0 0 0];
loc_1.setFlow(flow_1);

% Set inv: v >= 15 & v <= 40 & t >= 0& t<= 2.5 & gc <= timeHorizon
inv_1 = MHyProCondition([-1 0 0 0;1 0 0 0; 0 0 -1 0; 0 0 1 0;0 0 0 1], [-15;40;0;2.5;timeHorizon]);
loc_1.setInvariant(inv_1);

%-----------------------------------------------%
%              Location loc2
%-----------------------------------------------%
loc_2 = MHyProLocation();
loc_2.setName('loc2');

% Set flow: v' = -5 x' = 0 t' = 0 gc' = 1
flow_2 = [0 0 0 0 -5;...
          0 0 0 0 0;...
          0 0 0 0 0;...
          0 0 0 0 1;...
          0 0 0 0 0];
loc_2.setFlow(flow_2);

% Set inv: v >= 15 & v <= 40 & gc <= timeHorizon
inv_2 = MHyProCondition([-1 0 0 0; 1 0 0 0;0 0 0 1], [-15;40;timeHorizon]);
loc_2.setInvariant(inv_2);

%-----------------------------------------------%
%              Location loc3
%-----------------------------------------------%
loc_3 = MHyProLocation();
loc_3.setName('loc3');

% Set flow: v' = -2.5 x' = 0 t' = 0 gc' = 1
flow_3 = [0 0 0 0 -2.5;...
          0 0 0 0 0;...
          0 0 0 0 0;...
          0 0 0 0 1;...
          0 0 0 0 0];
loc_3.setFlow(flow_3);

% Set inv: v >= 5 & v <= 20 & gc <= timeHorizon
inv_3 = MHyProCondition([-1 0 0 0;1 0 0 0; 0 0 0 1], [-5;20;timeHorizon]);
loc_3.setInvariant(inv_3);

%-----------------------------------------------%
%              Location loc4
%-----------------------------------------------%
loc_4 = MHyProLocation();
loc_4.setName('loc4');

% Set flow: v' = -t -1.2 x' = 0 t' = 0.5 gc' = 1
flow_4 = [0 0 -1 0 -1.2;...
          0 0 0 0 0;...
          0 0 0 0 0.5;...
          0 0 0 0 1;...
          0 0 0 0 0];
loc_4.setFlow(flow_4);

% Set inv: v >= 5 & v <= 20 & t >= 0& t<= 1.3 & gc <= timeHorizon
inv_4 = MHyProCondition([-1 0 0 0;1 0 0 0; 0 0 -1 0; 0 0 1 0; 0 0 0 1], [-5;20;0;1.3;timeHorizon]);
loc_4.setInvariant(inv_4);


%-----------------------------------------------%
%              Location loc5
%-----------------------------------------------%
loc_5 = MHyProLocation();
loc_5.setName('loc5');

% Set flow: v' = -0.001x - 0.052v x' = v t' = 0 gc' = 1
flow_5 = [-0.052 -0.001 0 0 0;...
          1 0 0 0 0;...
          0 0 0 0 0;...
          0 0 0 0 1;...
          0 0 0 0 0];
loc_5.setFlow(flow_5);

% Set inv: v >= -15 & v <= 15 & x >= -500 & x <= 500 & gc <= timeHorizon
inv_5 = MHyProCondition([-1 0 0 0;1 0 0 0; 0 -1 0 0; 0 1 0 0; 0 0 0 1], [15;15;500;500;timeHorizon]);
loc_5.setInvariant(inv_5);

%-----------------------------------------------%
%              Location loc6
%-----------------------------------------------%
loc_6 = MHyProLocation();
loc_6.setName('loc6');

% Set flow: v' = 1.5 x' = 0 t' = 0 gc' = 1
flow_6 = [0 0 0 0 1.5;...
          0 0 0 0 0;...
          0 0 0 0 0;...
          0 0 0 0 1;...
          0 0 0 0 0];
loc_6.setFlow(flow_6);

% Set inv: v >= -20 & v <= -5 & gc <= timeHorizon
inv_6 = MHyProCondition([-1 0 0 0;1 0 0 0;0 0 0 1], [20;-5;timeHorizon]);
loc_6.setInvariant(inv_6);


%-----------------------------------------------%
%              Location sink
%-----------------------------------------------%
sink = MHyProLocation();
sink.setName('sink');

% Set flow: v' = 0 x' = 0 t' = 0 gc' = 0
flow_sink = zeros(5);
sink.setFlow(flow_sink);

%-----------------------------------------------%
%              Add locations to HA
%-----------------------------------------------%

l1 = automaton.addLocation(loc_1);
l2 = automaton.addLocation(loc_2);
l3 = automaton.addLocation(loc_3);
l4 = automaton.addLocation(loc_4);
l5 = automaton.addLocation(loc_5);
l6 = automaton.addLocation(loc_6);
s = automaton.addLocation(sink);

%-----------------------------------------------%
%              loc1 --> loc2
%-----------------------------------------------%
tran1 = MHyProTransition();
% Set guard: t = 2.5 & 15 <= v <= 40
guard1 = MHyProCondition();
guard1.setMatrix([0 0 -1 0; 0 0 1 0; 0 0 -1 0; 0 0 1 0]); 
guard1.setVector([-2.5;2.5;-15;40]);

tran1.setAggregation(aggr);
tran1.setGuard(guard1);
tran1.setSource(l1);
tran1.setTarget(l2);
tran1.setReset(dummy_reset);
tran1.setLabels({MHyProLabel('tran1')});

l1.addTransition(tran1);

%-----------------------------------------------%
%              loc1 --> loc4
%-----------------------------------------------%
tran2 = MHyProTransition();
% Set guard: 15 <= v <= 16 & 0 <= t <= 2.5
guard2 = MHyProCondition();
guard2.setMatrix([-1 0 0 0; 1 0 0 0; 0 0 -1 0; 0 0 1 0]); 
guard2.setVector([-15;16;0;2.5]);

tran2.setAggregation(aggr);
tran2.setGuard(guard2);
tran2.setSource(l1);
tran2.setTarget(l4);
reset2 = MHyProReset();
reset2.setMatrix([1 0 0 0; 0 1 0 0; 0 0 0 0; 0 0 0 1]);
reset2.setVector([0; 0; 0; 0]);
tran2.setReset(reset2);
tran2.setLabels({MHyProLabel('tran2')});

l1.addTransition(tran2);

%-----------------------------------------------%
%              loc1 --> sink
%-----------------------------------------------%
tran2s = MHyProTransition();
% Set guard: gc == timeHorizon
guard2s = MHyProCondition();
guard2s.setMatrix([0 0 0 -1; 0 0 0 1]); 
guard2s.setVector([-timeHorizon; timeHorizon]);

tran2s.setAggregation(0);
tran2s.setGuard(guard2s);
tran2s.setSource(l1);
tran2s.setTarget(s);
tran2s.setReset(dummy_reset);
tran2s.setLabels({MHyProLabel('tran2s')});

l1.addTransition(tran2s);

%-----------------------------------------------%
%              loc2 --> loc4
%-----------------------------------------------%
tran3 = MHyProTransition();
% Set guard: t = 2.5 & 15 <= v <= 16
guard3 = MHyProCondition();
guard3.setMatrix([-1 0 0 0; 1 0 0 0; 0 0 -1 0; 0 0 1 0]); 
guard3.setVector([-15;16;-2.5;2.5]);

tran3.setAggregation(aggr);
tran3.setGuard(guard3);
tran3.setSource(l2);
tran3.setTarget(l4);
reset3 = MHyProReset();
reset3.setMatrix([1 0 0 0; 0 1 0 0; 0 0 0 0; 0 0 0 1]);
reset3.setVector([0; 0; 0; 0]);
tran3.setReset(reset3);
tran3.setLabels({MHyProLabel('tran3')});

l2.addTransition(tran3);

%-----------------------------------------------%
%              loc2 --> sink
%-----------------------------------------------%
tran3s = MHyProTransition();
% Set guard: gc == timeHorizon
guard3s = MHyProCondition();
guard3s.setMatrix([0 0 0 -1; 0 0 0 1]); 
guard3s.setVector([-timeHorizon; timeHorizon]);

tran3s.setAggregation(0);
tran3s.setGuard(guard3s);
tran3s.setSource(l2);
tran3s.setTarget(s);
tran3s.setReset(dummy_reset);
tran3s.setLabels({MHyProLabel('tran3s')});

l2.addTransition(tran3s);

%-----------------------------------------------%
%              loc3 --> loc1
%-----------------------------------------------%
tran4 = MHyProTransition();
% Set guard: t = 1.3 & 18 <= v <= 20
guard4 = MHyProCondition();
guard4.setMatrix([-1 0 0 0; 1 0 0 0; 0 0 -1 0; 0 0 1 0]); 
guard4.setVector([-18;20;-1.3;1.3]);

tran4.setAggregation(aggr);
tran4.setGuard(guard4);
tran4.setSource(l3);
tran4.setTarget(l1);
reset4 = MHyProReset();
reset4.setMatrix([1 0 0 0; 0 1 0 0; 0 0 0 0; 0 0 0 1]);
reset4.setVector([0; 0; 0; 0]);
tran4.setReset(reset4);
tran4.setLabels({MHyProLabel('tran4')});

l3.addTransition(tran4);

%-----------------------------------------------%
%              loc3 --> loc5
%-----------------------------------------------%
tran5 = MHyProTransition();
% Set guard: t = 1.3 & v = [5,11]
guard5 = MHyProCondition();
guard5.setMatrix([-1 0 0 0; 1 0 0 0; 0 0 -1 0; 0 0 1 0]); 
guard5.setVector([-1.3;1.3;-5;11]);

tran5.setAggregation(aggr);
tran5.setGuard(guard4);
tran5.setSource(l3);
tran5.setTarget(l5);
reset5 = MHyProReset();
reset5.setMatrix([1 0 0 0; 0 0 0 0; 0 0 1 0; 0 0 0 1]);
reset5.setVector([0; 0; 0; 0]);
tran5.setReset(reset5);
tran5.setLabels({MHyProLabel('tran5')});

l3.addTransition(tran5);

%-----------------------------------------------%
%              loc3 --> sink
%-----------------------------------------------%
tran5s = MHyProTransition();
% Set guard: gc == timeHorizon
guard5s = MHyProCondition();
guard5s.setMatrix([0 0 0 -1; 0 0 0 1]); 
guard5s.setVector([-timeHorizon; timeHorizon]);

tran5s.setAggregation(0);
tran5s.setGuard(guard5s);
tran5s.setSource(l3);
tran5s.setTarget(s);
tran5s.setReset(dummy_reset);
tran5s.setLabels({MHyProLabel('tran5s')});

l3.addTransition(tran5s);

%-----------------------------------------------%
%              loc4 --> loc1
%-----------------------------------------------%
tran6 = MHyProTransition();
% Set guard: 18 <= v <= 20 & 0 <= t <= 1.3
guard6 = MHyProCondition();
guard6.setMatrix([-1 0 0 0; 1 0 0 0; 0 0 -1 0; 0 0 1 0]); 
guard6.setVector([-18;20;0;1.3]);

tran6.setAggregation(aggr);
tran6.setGuard(guard6);
tran6.setSource(l4);
tran6.setTarget(l1);
reset6 = MHyProReset();
reset6.setMatrix([1 0 0 0; 0 1 0 0; 0 0 0 0; 0 0 0 1]);
reset6.setVector([0; 0; 0; 0]);
tran6.setReset(reset6);
tran6.setLabels({MHyProLabel('tran6')});

l4.addTransition(tran6);

%-----------------------------------------------%
%              loc4 --> loc5
%-----------------------------------------------%
tran7 = MHyProTransition();
% Set guard:  5 <= v <= 11 & 0 <= t <= 1.3
guard7 = MHyProCondition();
guard7.setMatrix([-1 0 0 0; 1 0 0 0; 0 0 -1 0; 0 0 1 0]); 
guard7.setVector([-5;11;0;1.3]);

tran7.setAggregation(aggr);
tran7.setGuard(guard7);
tran7.setSource(l4);
tran7.setTarget(l5);
reset7 = MHyProReset();
reset7.setMatrix([1 0 0 0; 0 0 0 0; 0 0 1 0; 0 0 0 1]);
reset7.setVector([0; 0; 0; 0]);
tran7.setReset(reset7);
tran7.setLabels({MHyProLabel('tran7')});

l4.addTransition(tran7);

%-----------------------------------------------%
%              loc4 --> loc3
%-----------------------------------------------%
tran71 = MHyProTransition();
% Set guard: t = 1.3 & 5 <= v <= 20
guard71 = MHyProCondition();
guard71.setMatrix([-1 0 0 0; 1 0 0 0; 0 0 -1 0; 0 0 1 0]); 
guard71.setVector([-5;20;-1.3;1.3]);

tran71.setAggregation(aggr);
tran71.setGuard(guard71);
tran71.setSource(l4);
tran71.setTarget(l3);
tran71.setReset(dummy_reset);
tran71.setLabels({MHyProLabel('tran71')});

l4.addTransition(tran71);

%-----------------------------------------------%
%              loc4 --> sink
%-----------------------------------------------%
tran7s = MHyProTransition();
% Set guard: gc == timeHorizon
guard7s = MHyProCondition();
guard7s.setMatrix([0 0 0 -1; 0 0 0 1]); 
guard7s.setVector([-timeHorizon; timeHorizon]);

tran7s.setAggregation(0);
tran7s.setGuard(guard7s);
tran7s.setSource(l4);
tran7s.setTarget(s);
tran7s.setReset(dummy_reset);
tran7s.setLabels({MHyProLabel('tran7s')});

l4.addTransition(tran7s);

%-----------------------------------------------%
%              loc5 --> loc4
%-----------------------------------------------%
tran8 = MHyProTransition();
% Set guard: 13 <= v <= 15 & -500 <= x <= 500
guard8 = MHyProCondition();
guard8.setMatrix([-1 0 0 0; 1 0 0 0; 0 -1 0 0; 0 1 0 0]); 
guard8.setVector([-13;15; 500;500]);

tran8.setAggregation(aggr);
tran8.setGuard(guard8);
tran8.setSource(l5);
tran8.setTarget(l4);
reset8 = MHyProReset();
reset8.setMatrix([1 0 0 0; 0 1 0 0; 0 0 0 0; 0 0 0 1]);
reset8.setVector([0; 0; 0; 0]);
tran8.setReset(reset8);
tran8.setLabels({MHyProLabel('tran8')});

l5.addTransition(tran8);

%-----------------------------------------------%
%              loc5 --> loc6
%-----------------------------------------------%
tran9 = MHyProTransition();
% Set guard:  -15 <= v <= -14 & -500 <= x <= 500
guard9 = MHyProCondition();
guard9.setMatrix([-1 0 0 0; 1 0 0 0; 0 -1 0 0; 0 1 0 0]); 
guard9.setVector([15;-14;500;500]);

tran9.setAggregation(aggr);
tran9.setGuard(guard9);
tran9.setSource(l5);
tran9.setTarget(l6);
tran9.setReset(dummy_reset);
tran9.setLabels({MHyProLabel('tran9')});

l5.addTransition(tran9);

%-----------------------------------------------%
%              loc5 --> sink
%-----------------------------------------------%
tran9s = MHyProTransition();
% Set guard: gc == timeHorizon
guard9s = MHyProCondition();
guard9s.setMatrix([0 0 0 -1; 0 0 0 1]); 
guard9s.setVector([-timeHorizon; timeHorizon]);

tran9s.setAggregation(0);
tran9s.setGuard(guard9s);
tran9s.setSource(l5);
tran9s.setTarget(s);
tran9s.setReset(dummy_reset);
tran9s.setLabels({MHyProLabel('tran9s')});

l5.addTransition(tran9s);

%-----------------------------------------------%
%              loc6 --> loc5
%-----------------------------------------------%
tran10 = MHyProTransition();
% Set guard:-6 <= v <= -5 & -500 <= x <= 500
guard10 = MHyProCondition();
guard10.setMatrix([-1 0 0 0; 1 0 0 0; 0 -1 0 0; 0 1 0 0]); 
guard10.setVector([6;-5; 500;500]);

tran10.setAggregation(aggr);
tran10.setGuard(guard10);
tran10.setSource(l6);
tran10.setTarget(l5);
reset10 = MHyProReset();
reset10.setMatrix([1 0 0 0; 0 0 0 0; 0 0 1 0; 0 0 0 1]);
reset10.setVector([0; 0; 0; 0]);
tran10.setReset(reset10);
tran10.setLabels({MHyProLabel('tran10')});

l6.addTransition(tran10);

%-----------------------------------------------%
%              loc6 --> sink
%-----------------------------------------------%
tran10s = MHyProTransition();
% Set guard: gc == timeHorizon
guard10s = MHyProCondition();
guard10s.setMatrix([0 0 0 -1; 0 0 0 1]); 
guard10s.setVector([-timeHorizon; timeHorizon]);

tran10s.setAggregation(0);
tran10s.setGuard(guard10s);
tran10s.setSource(l6);
tran10s.setTarget(s);
tran10s.setReset(dummy_reset);
tran10s.setLabels({MHyProLabel('tran10s')});

l6.addTransition(tran10s);

%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% v = [15, 40] x = [0, 0]  t =[0, 2.5] gc = [0, 0]
boxVector = [40; -15; 0; 0; 2.5; 0; 0; 0];
boxMatrix = [1 0 0 0; -1 0 0 0; 0 1 0 0; 0 -1 0 0; 0 0 1 0; 0 0 -1 0; 0 0 0 1; 0 0 0 -1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(l1, initialCond);

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
fig = figure();
dim = [1 2];
labs = ["v", "x"];
reacher.plotComparison(flowpipes, dim, labs);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

disp('CORA');

% Load model
HA = cora_cruise_control_ha();
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';

% options
% v = [15, 40] x = [0, 0]  t =[0, 2.5]
Zcenter = interval([15;0;0],[40;0.1;2.5]);
options.R0 = zonotope(Zcenter); %initial state for reachability analysis
% options.x0 = center(options.R0); %initial state for simulation

options.taylorTerms = tT;
options.zonotopeOrder = zO;
options.polytopeOrder = pO;

options.errorOrder=1e-12;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.originContained = 0;

%set input:
for i = 1:6
    options.timeStepLoc{i} = timeStepC;
    options.uLoc{i} = [0;0;0];
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

% First location
options.startLoc = 1; %initial location
options.finalLoc = 0; %0: no final location
options.tStart = 0; %start time
options.tFinal = timeHorizon;

tic;
[HA] = reach(HA,options);
options.projectedDimensions = [3 1];
options.plotType = 'b';
%plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
plot(HA,'reachableSet',options); %plot reachable set
set(gca,'FontSize',15);
xlabel('t');
ylabel('v');

 if diff == 1
        x = [20;-10;-10;20];
        y = [-2;-2;-20;-20];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    elseif diff == 2
        x = [20;-10;-10;20];
        y = [-2;-2;-20;-20];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    else
        x = [20;-10;-10;20];
        y = [-2;-2;-20;-20];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
 end

if saveFig
    saveas(fig, fullfile(savePath,fname),'eps');
end

end
