function compareREND_CORA_MHyPro()

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
dummy_reset.setMatrix(eye(5));
dummy_reset.setVector([0; 0; 0; 0; 0]);

% Variables: [x; y; vx; vy; t]

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

flow_p2 = [0,0,1,0,0,0;...
           0,0,0,1,0,0;...
           -0.05759976588,0.0002009598965,-2.89995084,0.008772008945,0,0;...
           -0.0001740313574,-0.06651239849,-0.008753511055,-2.903002693,0,0;...
           0,0,0,0,0,1];

loc_p2.setFlow(flow_p2);

% Set invariant: x <= -100

inv_p2 = MHyProCondition([1 0 0 0 0], -100);
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

flow_p3 = [0,0,1,0,0,0;...
           0,0,0,1,0,0;...
          -0.5759999431,0.0002624860794,-19.22997959,0.008762759318,0,0;...
          -0.0002624860807,-0.5759999402,-0.008762760682,-19.2299766,0,0;...
          0,0,0,0,0,1];
      
loc_p3.setFlow(flow_p3);

% Set invariant: y>=-100 & x+y>=-141.1 & x>=-100 & y-x<=141.1 & y<=100 &
%     x+y<=141.1 & x<=100 & y-x>=-141.1
invMatrix = [0,-1,0,0,0;...
            -1,-1,0,0,0;...
            -1,0,0,0,0;...
            -1,1,0,0,0;...
            0,1,0,0,0;...
            1,1,0,0,0;...
            1,0,0,0,0;...
            1,-1,0,0,0];
invVec = [100;141.1;100;141.1;100;141.1;100;141.1];

inv_p3 = MHyProCondition(invMatrix, invVec);
loc_p3.setInvariant(inv_p3);


p2 = automaton.addLocation(loc_p2);
p3 = automaton.addLocation(loc_p3);

%-----------------------------------------------%
%              p2 -> p3
%-----------------------------------------------%

tran = MHyProTransition();
% Set guard: y>=-100 & x+y >=-141.1 & x>=-100 & y-x<=141.1 & y<=100 &
%            x+y<=141.1 & x<=100 & y-x>=-141.1
guardMatrix = [0,-1,0,0,0;-1,-1,0,0,0;-1,0,0,0,0;-1,1,0,0,0;0,1,0,0,0;1,1,0,0,0;1,0,0,...
0,0;1,-1,0,0,0];
guardVector = [100;141.1;100;141.1;100;141.1;100;141.1];
guard = MHyProCondition();
guard.setMatrix(guardMatrix); % First set the matrix then the vector!?
guard.setVector(guardVector);

dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(5));
dummy_reset.setVector([0; 0; 0;0;0]);

tran.setAggregation(aggr);
tran.setGuard(guard);
tran.setSource(p2);
tran.setTarget(p3);
tran.setReset(dummy_reset);
tran.setLabels({MHyProLabel('tran')});

p2.addTransition(tran);

%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% x = [-925; -875] y = [-425; -375] vx,vy,t = 0
boxVector = [-875; -375; 0; 0 ;0; 925; 425; 0; 0; 0];
boxMatrix = [eye(5);-1*eye(5)];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(p2, initialCond);


%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%


% Add basic settings
settings.timeBound = timeHorizon;
settings.jumpDepth = 10;
settings.timeStep = timeStep;
settings.clustering = clustering;

reacher = MHyProReach(automaton);
reacher.setSettings(settings);
reacher.setRepresentationType(setRepr);

flowpipes = reacher.computeForwardReachability();
dim = [3 4];
labs = ["vx", "vy"];
reacher.plotComparison(flowpipes, dim, labs);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

R0 = zonotope([[-900; -400; 0; 0; 0],diag([25;25;0;0;0])]);

% initial set
options.x0=center(R0); % initial state for simulation
options.R0=R0; % initial state for reachability analysis

% other
options.startLoc = 1; % initial location
options.finalLoc = -inf; % no final location
options.tStart=0; % start time
options.tFinal=timeHorizon; % final time
options.intermediateOrder = 2;
options.originContained = 0;


options.taylorTerms = tT;
options.zonotopeOrder = zO;
options.polytopeOrder = pO;
    
options.reductionTechnique = 'girard';
options.isHyperplaneMap=0;
options.enclosureEnables = [3, 5]; % choose enclosure method(s)
options.filterLength = [5,7];
options.guardIntersect = 'polytope';
options.errorOrder = 2;

% specify hybrid automata
HA = rendezvousSX4np_ha(); % automatically converted from SpaceEx

for i = 1:5
    options.timeStepLoc{i} = timeStep;
    options.uLoc{i} = 0;
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

[HA] = reach(HA,options);
options.projectedDimensions = [3 4];
options.plotType = 'b';
plot(HA,'reachableSet',options); %plot reachable set
plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set

end
