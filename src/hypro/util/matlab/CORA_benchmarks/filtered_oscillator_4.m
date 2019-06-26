function res = filtered_oscillator_4()

%set options---------------------------------------------------------------
options.x0 = [0.25; 0.0; 0.0; 0.0; 0.0; 0.0];
options.R0 = zonotope([options.x0, 0.05 * eye(6)]);
options.taylorTerms = 10;
options.zonotopeOrder = 20;
options.polytopeOrder = 10;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.guardIntersect = 'polytope';
options.enclosureEnables = 5;
options.originContained = 0;
options.startLoc = 3;
options.finalLoc = 0;
options.tStart = 0;
options.tFinal = 4;
options.timeStepLoc{1}= 0.05;
options.timeStepLoc{2}= 0.05;
options.timeStepLoc{3}= 0.05;
options.timeStepLoc{4}= 0.05;

%define flows--------------------------------------------------------------

A1 = [-2 0 0 0 0 0 ; ...
0 -1 0 0 0 0 ; ...
5 0 -5 0 0 0 ; ...
0 0 5 -5 0 0 ; ...
0 0 0 5 -5 0 ; ...
0 0 0 0 5 -5 ];
B1 = zeros(6, 1);
c1 = [1.4 ; ...
-0.7 ; ...
0 ; ...
0 ; ...
0 ; ...
0 ];
flow1 = linearSys('linearSys1', A1, B1, c1);

A2 = [-2 0 0 0 0 0 ; ...
0 -1 0 0 0 0 ; ...
5 0 -5 0 0 0 ; ...
0 0 5 -5 0 0 ; ...
0 0 0 5 -5 0 ; ...
0 0 0 0 5 -5 ];
B2 = zeros(6, 1);
c2 = [-1.4 ; ...
0.7 ; ...
0 ; ...
0 ; ...
0 ; ...
0 ];
flow2 = linearSys('linearSys2', A2, B2, c2);

A3 = [-2 0 0 0 0 0 ; ...
0 -1 0 0 0 0 ; ...
5 0 -5 0 0 0 ; ...
0 0 5 -5 0 0 ; ...
0 0 0 5 -5 0 ; ...
0 0 0 0 5 -5 ];
B3 = zeros(6, 1);
c3 = [1.4 ; ...
-0.7 ; ...
0 ; ...
0 ; ...
0 ; ...
0 ];
flow3 = linearSys('linearSys3', A3, B3, c3);

A4 = [-2 0 0 0 0 0 ; ...
0 -1 0 0 0 0 ; ...
5 0 -5 0 0 0 ; ...
0 0 5 -5 0 0 ; ...
0 0 0 5 -5 0 ; ...
0 0 0 0 5 -5 ];
B4 = zeros(6, 1);
c4 = [-1.4 ; ...
0.7 ; ...
0 ; ...
0 ; ...
0 ; ...
0 ];
flow4 = linearSys('linearSys4', A4, B4, c4);


%define invariants---------------------------------------------------------

inv_l1 =  mptPolytope(struct('A', [1 0 0 0 0 0 ; -0.714286 -1 0 0 0 0 ], 'b', [ 0; - 0]));
inv_l2 =  mptPolytope(struct('A', [1 0 0 0 0 0 ; 0.714286 1 0 0 0 0 ], 'b', [ 0;  0]));
inv_l3 =  mptPolytope(struct('A', [-1 0 0 0 0 0 ; -0.714286 -1 0 0 0 0 ], 'b', [- 0; - 0]));
inv_l4 =  mptPolytope(struct('A', [-1 0 0 0 0 0 ; 0.714286 1 0 0 0 0 ], 'b', [- 0;  0]));

%define transitions--------------------------------------------------------

%  l3 -> l4 
guard =  mptPolytope(struct('A', [0.714286 1 0 0 0 0 ; -1 0 0 0 0 0 ; -0.714286 -1 0 0 0 0 ], 'b', [ 0; - 0  ; - 0]));
reset.A = eye(6);
reset.b = zeros(6, 1);
trans_l3{1} = transition(guard, reset, 4, 'l3', 'l4');

%  l4 -> l2 
guard =  mptPolytope(struct('A', [1 0 0 0 0 0 ; 0.714286 1 0 0 0 0 ; -1 0 0 0 0 0 ], 'b', [ 0;  0  ; - 0]));
reset.A = eye(6);
reset.b = zeros(6, 1);
trans_l4{1} = transition(guard, reset, 2, 'l4', 'l2');

%  l2 -> l1 
guard =  mptPolytope(struct('A', [0.714286 1 0 0 0 0 ; 1 0 0 0 0 0 ; -0.714286 -1 0 0 0 0 ], 'b', [ 0;  0 ; - 0]));
reset.A = eye(6);
reset.b = zeros(6, 1);
trans_l2{1} = transition(guard, reset, 1, 'l2', 'l1');

%  l1 -> l3 
guard =  mptPolytope(struct('A', [-x=00.714286 -1 0 0 0 0 ], 'b', [- 0  ]));
reset.A = eye(6);
reset.b = zeros(6, 1);
trans_l1{1} = transition(guard, reset, 3, 'l1', 'l3');

%define locations----------------------------------------------------------

options.uLoc{1} = 0;
options.uLocTrans{1} = 0;
options.Uloc{1} = zonotope(0);

options.uLoc{2} = 0;
options.uLocTrans{2} = 0;
options.Uloc{2} = zonotope(0);

options.uLoc{3} = 0;
options.uLocTrans{3} = 0;
options.Uloc{3} = zonotope(0);

options.uLoc{4} = 0;
options.uLocTrans{4} = 0;
options.Uloc{4} = zonotope(0);


loc{1} = location('l1', 1, inv_l1, trans_l1, flow1);
loc{2} = location('l2', 2, inv_l2, trans_l2, flow2);
loc{3} = location('l3', 3, inv_l3, trans_l3, flow3);
loc{4} = location('l4', 4, inv_l4, trans_l4, flow4);

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
