function completed = bouncing_ball

%set options---------------------------------------------------------------
options.x0 = [10.1; 0]; %initial state for simulation
options.R0 = zonotope([options.x0, diag([0.1, 0])]); %initial state for reachability analysis
options.startLoc = 1; %initial location
options.finalLoc = 0; %0: no final location
options.tStart = 0; %start time
options.tFinal = 10; %final time
options.timeStepLoc{1} = 0.1; %time step size for reachable set computation in location 1
options.taylorTerms = 10;
options.zonotopeOrder = 20;
options.polytopeOrder = 10;
options.errorOrder=2;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.guardIntersect = 'polytope';
options.enclosureEnables = [3 5]; %choose enclosure method(s)
options.originContained = 0;
%--------------------------------------------------------------------------


%specify hybrid automaton--------------------------------------------------
%specify linear system of bouncing ball
A = [0 1; 0 0];
B = zeros(2);
c = [0; -9.81];
linSys = linearSys('linearSys',A,B,c);

%invariant
inv = halfspace([-1 0], 0);
%guard sets
guardA = [1 0; -1 0; 0 -1];
guardb = [0;0;0];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);
%resets
reset.A = [1 0; 0 -0.75]; reset.b = zeros(2,1);
%transitions
trans{1} = transition(guard,reset,1,'a','b'); %--> next loc: 1; 'a', 'b' are dummies
%specify location
loc{1} = location('loc1',1,inv,trans,linSys); 
%specify hybrid automata
HA = hybridAutomaton(loc); % for "geometric intersection"
%--------------------------------------------------------------------------

%set input:
options.uLoc{1} = [0; 0]; %input for simulation
options.uLocTrans{1} = options.uLoc{1}; %input center for reachability analysis
options.Uloc{1} = zonotope(zeros(2,1)); %input deviation for reachability analysis

%simulate hybrid automaton
HA = simulate(HA,options); 

%compute reachable set
[HA] = reach(HA,options);

%choose projection and plot------------------------------------------------
figure 
hold on
options.projectedDimensions = [1 2];
options.plotType = 'b';
plot(HA,'reachableSet',options); %plot reachable set
plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
%plot(HA,'simulation',options); %plot simulation
%--------------------------------------------------------------------------

%example completed
completed = 1;

