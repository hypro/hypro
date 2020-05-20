function  sr_param_experiments()

timeHorizon = 20;

% Create Automaton
automaton = MHyProHAutomaton();
dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(6));
dummy_reset.setVector([0; 0; 0; 0; 0; 0]);

% Variables: [x; y; vx; vy; t; gc]

% Add basic settings
settings.timeBound = 20;
settings.jumpDepth = 10;
%settings.uniformBloating = false;
settings.clustering = 0;
settings.timeStep = 0.01;
setRepr = 0;
aggr = 1;

%-----------------------------------------------%
%              Location p2
%-----------------------------------------------%

loc_p2 = MHyProLocation();
loc_p2.setName('p2');

% Set flow:
% x'==vx & y'==vy &
% vx'==-0.057599765881773*x+0.000200959896519766*y-2.89995083970656*vx+0.00877200894463775*vy &
% vy'==-0.000174031357370456*x-0.0665123984901026*y-0.00875351105536225*vx-2.90300269286856*vy
% t'==1 
% gc' == 1

flow_p2 = [0,0,1,0,0,0,0;...
           0,0,0,1,0,0,0;...
           -0.05759976588,0.0002009598965,-2.89995084,0.008772008945,0,0,0;...
           -0.0001740313574,-0.06651239849,-0.008753511055,-2.903002693,0,0,0;...
           0,0,0,0,0,0,1;...
           0,0,0,0,0,0,1;...
           0,0,0,0,0,0,0];

loc_p2.setFlow(flow_p2);

% Set invariant: x <= -100 & gc <= timeHorizon

inv_p2 = MHyProCondition([1 0 0 0 0 0; 0 0 0 0 0 1], [-100;timeHorizon]);
loc_p2.setInvariant(inv_p2);

%-----------------------------------------------%
%              Location p3
%-----------------------------------------------%

loc_p3 = MHyProLocation();
loc_p3.setName('p3');

% Set flow: 
% x'==vx & y'==vy &
% vx'==-0.575999943070835*x+0.000262486079431672*y-19.2299795908647*vx+0.00876275931760007*vy &
% vy'==-0.000262486080737868*x-0.575999940191886*y-0.00876276068239993*vx-19.2299765959399*vy
% t' ==1
% gc'==1

flow_p3 = [0,0,1,0,0,0,0;...
           0,0,0,1,0,0,0;...
          -0.5759999431,0.0002624860794,-19.22997959,0.008762759318,0,0,0;...
          -0.0002624860807,-0.5759999402,-0.008762760682,-19.2299766,0,0,0;...
          0,0,0,0,0,0,1;...
          0,0,0,0,0,0,1;...
          0,0,0,0,0,0,0];
      
loc_p3.setFlow(flow_p3);

% Set invariant: y>=-100 & x+y>=-141.1 & x>=-100 & y-x<=141.1 & y<=100 &
%     x+y<=141.1 & x<=100 & y-x>=-141.1 & gc <= timeHorizon
invMatrix = [0,-1,0,0,0,0;...
            -1,-1,0,0,0,0;...
            -1,0,0,0,0,0;...
            -1,1,0,0,0,0;...
            0,1,0,0,0,0;...
            1,1,0,0,0,0;...
            1,0,0,0,0,0;...
            1,-1,0,0,0,0;...
            0,0,0,0,0,1];
invVec = [100;141.1;100;141.1;100;141.1;100;141.1;timeHorizon];

inv_p3 = MHyProCondition(invMatrix, invVec);
loc_p3.setInvariant(inv_p3);

%-----------------------------------------------%
%              Location sink
%-----------------------------------------------%

sink = MHyProLocation();
sink.setName('sink');
sink.setFlow(zeros(6));

p2 = automaton.addLocation(loc_p2);
p3 = automaton.addLocation(loc_p3);
s = automaton.addLocation(sink);

%-----------------------------------------------%
%              p2 -> p3
%-----------------------------------------------%

tran = MHyProTransition();
% Set guard: y>=-100 & x+y >=-141.1 & x>=-100 & y-x<=141.1 & y<=100 &
%            x+y<=141.1 & x<=100 & y-x>=-141.1
guardMatrix = [0,-1,0,0,0,0;-1,-1,0,0,0,0;-1,0,0,0,0,0;-1,1,0,0,0,0;0,1,0,0,0,0;1,1,0,0,0,0;1,0,0,...
0,0,0;1,-1,0,0,0,0];
guardVector = [100;141.1;100;141.1;100;141.1;100;141.1];
guard = MHyProCondition();
guard.setMatrix(guardMatrix); % First set the matrix then the vector!?
guard.setVector(guardVector);

dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(6));
dummy_reset.setVector([0;0;0;0;0;0]);

tran.setAggregation(aggr);
tran.setGuard(guard);
tran.setSource(p2);
tran.setTarget(p3);
tran.setReset(dummy_reset);
tran.setLabels({MHyProLabel('tran')});

p2.addTransition(tran);

%-----------------------------------------------%
%              p2 -> sink
%-----------------------------------------------%

guardMatrix = [0 0 0 0 0 0 -1;0 0 0 0 0 0 1];
sink_guard = MHyProCondition();
sink_guard.setMatrix(guardMatrix);
sink_guard.setVector([-timeHorizon;timeHorizon]);

tran1s = MHyProTransition();
tran1s.setAggregation(0);
tran1s.setGuard(sink_guard);
tran1s.setSource(p2);
tran1s.setTarget(s);
tran1s.setReset(dummy_reset);
tran1s.setLabels({MHyProLabel('tran1s')});

p2.addTransition(tran1s);

%-----------------------------------------------%
%              p3 -> sink
%-----------------------------------------------%

tran2s = MHyProTransition();
tran2s.setAggregation(0);
tran2s.setGuard(sink_guard);
tran2s.setSource(p3);
tran2s.setTarget(s);
tran2s.setReset(dummy_reset);
tran2s.setLabels({MHyProLabel('tran2s')});

p3.addTransition(tran2s);


%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% x = [-925; -875] y = [-425; -375] vx,vy,t,gc = 0
boxVector = [-875; -375; 0; 0 ;0;0; 925; 425; 0; 0; 0;0];
boxMatrix = [eye(6);-1*eye(6)];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(p2, initialCond);


%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%



reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(setRepr);

tic;
flowpipes = reach.computeForwardReachability();
reachabilityTime = toc;
disp(['Time neede for reachability: ', num2str(reachabilityTime)]);
dim = [3 4];
labs = ["vx", "vy"];
reach.plotColor(flowpipes, dim, labs,0,' ',' ',' ',[0.094, 0.725, 0.219]);
set(gca,'FontSize',15);


end