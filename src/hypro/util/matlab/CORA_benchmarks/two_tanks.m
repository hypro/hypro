function res = two_tanks()

%set options---------------------------------------------------------------
options.x0 = [2.0; 1.0];
options.R0 = zonotope([options.x0, 0.01 * eye(2)]);
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
options.tFinal = 2;
options.timeStepLoc{1}= 0.01;
options.timeStepLoc{2}= 0.01;
options.timeStepLoc{3}= 0.01;
options.timeStepLoc{4}= 0.01;

%define flows--------------------------------------------------------------

A1 = [-1 0 ; 1 0 ];
B1 = zeros(2, 1);
c1 = [-2 ; 0 ];
options.uTrans = [0.0; 0.0];
options.U = 0.5 * zonotope([zeros(2, 1), diag([0.02; 0.02])]);
flow1 = linearSys('linearSys1', A1, B1, c1);

A2 = [-1 0 ; 1 0 ];
B2 = zeros(2, 1);
c2 = [3 ; 0 ];
options.uTrans = [0.0; 0.0];
options.U = 0.5 * zonotope([zeros(2, 1), diag([0.02; 0.02])]);
flow2 = linearSys('linearSys2', A2, B2, c2);

A3 = [-1 0 ; 1 -1 ];
B3 = zeros(2, 1);
c3 = [-2 ; -5 ];
options.uTrans = [0.0; 0.0];
options.U = 0.5 * zonotope([zeros(2, 1), diag([0.02; 0.02])]);
flow3 = linearSys('linearSys3', A3, B3, c3);

A4 = [-1 0 ; 1 -1 ];
B4 = zeros(2, 1);
c4 = [3 ; -5 ];
options.uTrans = [0.0; 0.0];
options.U = 0.5 * zonotope([zeros(2, 1), diag([0.02; 0.02])]);
flow4 = linearSys('linearSys4', A4, B4, c4);


%define invariants---------------------------------------------------------

inv_q1 =  mptPolytope(struct('A', [-1 0 ; 0 1 ], 'b', [- -1;  1]));
inv_q2 =  mptPolytope(struct('A', [0 1 ], 'b', [ 1]));
inv_q3 =  mptPolytope(struct('A', [-1 0 ; 0 -1 ], 'b', [- -1; - 0]));
inv_q4 =  mptPolytope(struct('A', [1 0 ; 0 -1 ], 'b', [ 1; - 0]));

%define transitions--------------------------------------------------------

%  q1 -> q2
guard =  mptPolytope(struct('A', [1 0 ; -1 0 ], 'b', [-1; --1]));
%   
reset.A = [];
reset.b = [0; 0];
trans_q1{1} = transition(guard, reset, 2, 'q1', 'q2');

%  q2 -> q3
guard =  mptPolytope(struct('A', [0 1 ; 0 -1 ], 'b', [1; -1]));
%   
reset.A = [];
reset.b = [0; 0];
trans_q2{1} = transition(guard, reset, 3, 'q2', 'q3');

%  q3 -> q1
guard =  mptPolytope(struct('A', [0 1 ; 0 -1 ], 'b', [0; 0]));
%   
reset.A = [];
reset.b = [0; 0];
trans_q3{1} = transition(guard, reset, 1, 'q3', 'q1');

%  q1 -> q3
guard =  mptPolytope(struct('A', [0 1 ; 0 -1 ], 'b', [1; -1]));
%   
reset.A = [];
reset.b = [0; 0];
trans_q1{2} = transition(guard, reset, 3, 'q1', 'q3');

%  q3 -> q4
guard =  mptPolytope(struct('A', [1 0 ; -1 0 ], 'b', [-1; --1]));
%   
reset.A = [];
reset.b = [0; 0];
trans_q3{2} = transition(guard, reset, 4, 'q3', 'q4');

%  q4 -> q3
guard =  mptPolytope(struct('A', [1 0 ; -1 0 ], 'b', [1; -1]));
%   
reset.A = [];
reset.b = [0; 0];
trans_q4{1} = transition(guard, reset, 3, 'q4', 'q3');

%  q4 -> q2
guard =  mptPolytope(struct('A', [0 1 ; 0 -1 ], 'b', [0; 0]));
%   
reset.A = [];
reset.b = [0; 0];
trans_q4{2} = transition(guard, reset, 2, 'q4', 'q2');

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


loc{1} = location('q1', 1, inv_q1, trans_q1, flow1);
loc{2} = location('q2', 2, inv_q2, trans_q2, flow2);
loc{3} = location('q3', 3, inv_q3, trans_q3, flow3);
loc{4} = location('q4', 4, inv_q4, trans_q4, flow4);

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
