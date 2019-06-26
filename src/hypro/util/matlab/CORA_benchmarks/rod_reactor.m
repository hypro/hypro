function res = rod_reactor()

%set options---------------------------------------------------------------
options.x0 = [515.0; 20.0; 20.0];
options.R0 = zonotope([options.x0, 0.1 * eye(3)]);
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
options.tFinal = 50;
options.timeStepLoc{1}= 0.1;
options.timeStepLoc{2}= 0.1;
options.timeStepLoc{3}= 0.1;
options.timeStepLoc{4}= 0.1;

%define flows--------------------------------------------------------------

A1 = [0.1 0 0 ; 0 0 0 ; 0 0 0 ];
B1 = zeros(3, 1);
c1 = [-56 ;  1 ;  1 ];
flow1 = linearSys('linearSys1', A1, B1, c1);

A2 = [0.1 0 0 ; 0 0 0 ; 0 0 0 ];
B2 = zeros(3, 1);
c2 = [-60 ;  1 ;  1 ];
flow2 = linearSys('linearSys2', A2, B2, c2);

A3 = [0.1 0 0 ; 0 0 0 ; 0 0 0 ];
B3 = zeros(3, 1);
c3 = [-50 ;  1 ;  1 ];
flow3 = linearSys('linearSys3', A3, B3, c3);

A4 = [0 0 0 ; 0 0 0 ; 0 0 0 ];
B4 = zeros(3, 1);
c4 = [ 0 ;  0 ;  0 ];
flow4 = linearSys('linearSys4', A4, B4, c4);


%define invariants---------------------------------------------------------

inv_rod1 =  mptPolytope(struct('A', [-1 0 0 ], 'b', [- 510]));
inv_rod2 =  mptPolytope(struct('A', [-1 0 0 ], 'b', [- 510]));
inv_norod =  mptPolytope(struct('A', [1 0 0 ], 'b', [ 550]));
inv_shutdown =  mptPolytope(struct('A', [], 'b', []));

%define transitions--------------------------------------------------------

%  norod -> rod1
guard =  mptPolytope(struct('A', [0 0 0 ], 'b', [- 20 ]));
reset.A = eye(3);
reset.b = zeros(3, 1);
trans_norod{1} = transition(guard, reset, 1, 'norod', 'rod1');

%  norod -> rod2
guard =  mptPolytope(struct('A', [0 0 0 ], 'b', [- 20 ]));
reset.A = eye(3);
reset.b = zeros(3, 1);
trans_norod{2} = transition(guard, reset, 2, 'norod', 'rod2');

%  rod1 -> norod
guard =  mptPolytope(struct('A', [1 0 0 ; -1 0 0 ], 'b', [510; -510]));
%    c1 := 0 
reset.A = [1 0 0 ; 0 0 0 ; 0 0 1 ];
reset.b = [0; 0; 0];
trans_rod1{1} = transition(guard, reset, 3, 'rod1', 'norod');

%  rod2 -> norod
guard =  mptPolytope(struct('A', [1 0 0 ; -1 0 0 ], 'b', [510; -510]));
%    c2 := 0 
reset.A = [1 0 0 ; 0 1 0 ; 0 0 0 ];
reset.b = [0; 0; 0];
trans_rod2{1} = transition(guard, reset, 3, 'rod2', 'norod');

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


loc{1} = location('rod1', 1, inv_rod1, trans_rod1, flow1);
loc{2} = location('rod2', 2, inv_rod2, trans_rod2, flow2);
loc{3} = location('norod', 3, inv_norod, trans_norod, flow3);
loc{4} = location('shutdown', 4, inv_shutdown, {}, flow4);

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
