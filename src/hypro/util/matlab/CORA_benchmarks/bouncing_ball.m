function res = bouncing_ball()

%set options---------------------------------------------------------------
options.x0 = [10.1; 0.0];
options.R0 = zonotope([options.x0, 0.1 * eye(2)]);
options.taylorTerms = 10;
options.zonotopeOrder = 20;
options.polytopeOrder = 10;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.guardIntersect = 'polytope';
options.enclosureEnables = 5;
options.originContained = 0;
options.startLoc = 1;
options.finalLoc = 0;
options.tStart = 0;
options.tFinal = 10;
options.timeStepLoc{1}= 0.1;

%define flows--------------------------------------------------------------

A1 = [0 1 ; 0 0 ];
B1 = zeros(2, 1);
c1 = [0 ;  -9.81 ];
flow1 = linearSys('linearSys1', A1, B1, c1);


%define invariants---------------------------------------------------------

inv_l =  mptPolytope(struct('A', [-1 0 ], 'b', [- 0]));

%define transitions--------------------------------------------------------

%  l -> l
guard =  mptPolytope(struct('A', [0 0 ], 'b', [ 0]));
%    v := -0.75*v 
reset.A = [1 0 ; 0 -0.75 ];
reset.b = [0; 0];
trans_l{1} = transition(guard, reset, 1, 'l', 'l');

%define locations----------------------------------------------------------

options.uLoc{1} = 0;
options.uLocTrans{1} = 0;
options.Uloc{1} = zonotope(0);


loc{1} = location('l', 1, inv_l, trans_l, flow1);

%define hybrid automaton---------------------------------------------------

HA = hybridAutomaton(loc);
[HA] = reach(HA, options);

figure
hold on
options.projectedDimensions = [1 2];
options.plotType = 'b';
plot(HA,'reachableSet',options); %plot reachable set
plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set

res = 1;
