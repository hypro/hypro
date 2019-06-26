function res = switching_5()

%set options---------------------------------------------------------------
options.x0 = [3.1; 4.0; 0.0; 0.0; 0.0];
options.R0 = zonotope([options.x0, 0.01 * eye(5)]);
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
options.tFinal = 1;
options.timeStepLoc{1}= 0.01;
options.timeStepLoc{2}= 0.01;
options.timeStepLoc{3}= 0.01;
options.timeStepLoc{4}= 0.01;
options.timeStepLoc{5}= 0.01;

%define flows--------------------------------------------------------------

A1 = [-0.8047 8.7420 -2.4591 -8.2714 -1.8640 ; -8.6329 -0.5860 -2.1006 3.6035 -1.8423 ; 2.4511 2.2394 -0.7538 -3.6934 2.4585 ; 8.3858 -3.1739 3.7822 -0.6249 1.8829 ; 1.8302 1.9869 -2.4539 -1.7726 -0.7911 ];
B1 = zeros(5, 1);
c1 = [0 ; 0 ; 0 ; 0 ; 0 ];
options.uTrans = [0.0; 0.0; 0.0; 0.0; 0.0];
options.U = 0.5 * zonotope([zeros(5, 1), diag([0.169; 0; 0; 0; 1.4684])]);
flow1 = linearSys('linearSys1', A1, B1, c1);

A2 = [-0.8316 8.7658 -2.4744 -8.2608 -1.9033 ; -0.8316 -0.5860 -2.1006 3.6035 -1.8423 ; 2.4511 2.2394 -0.7538 -3.6934 2.4585 ; 8.3858 -3.1739 3.7822 -0.6249 1.8829 ; 1.5964 2.1936 -2.5872 -1.6812 -1.1324 ];
B2 = zeros(5, 1);
c2 = [0 ; 0 ; 0 ; 0 ; 0 ];
options.uTrans = [0.0; 0.0; 0.0; 0.0; 0.0];
options.U = 0.5 * zonotope([zeros(5, 1), diag([0.169; 0; 0; 0; 1.4684])]);
flow2 = linearSys('linearSys2', A2, B2, c2);

A3 = [-0.9275 8.8628 -2.5428 -8.2329 -2.0324 ; -0.8316 -0.5860 -2.1006 3.6035 -1.8423 ; 2.4511 2.2394 -0.7538 -3.6934 2.4585 ; 8.3858 -3.1739 3.7822 -0.6249 1.8829 ; 0.7635 3.0357 -3.1814 -1.4388 -2.2538 ];
B3 = zeros(5, 1);
c3 = [0 ; 0 ; 0 ; 0 ; 0 ];
options.uTrans = [0.0; 0.0; 0.0; 0.0; 0.0];
options.U = 0.5 * zonotope([zeros(5, 1), diag([0.169; 0; 0; 0; 1.4684])]);
flow3 = linearSys('linearSys3', A3, B3, c3);

A4 = [-1.0145 8.9701 -2.6207 -8.2199 -2.1469 ; -0.8316 -0.5860 -2.1006 3.6035 -1.8423 ; 2.4511 2.2394 -0.7538 -3.6934 2.4585 ; 8.3858 -3.1739 3.7822 -0.6249 1.8829 ; 0.0076 3.9682 -3.8578 -1.3253 -3.2477 ];
B4 = zeros(5, 1);
c4 = [0 ; 0 ; 0 ; 0 ; 0 ];
options.uTrans = [0.0; 0.0; 0.0; 0.0; 0.0];
options.U = 0.5 * zonotope([zeros(5, 1), diag([0.169; 0; 0; 0; 1.4684])]);
flow4 = linearSys('linearSys4', A4, B4, c4);

A5 = [-1.4021 10.1647 -3.3937 -8.5139 -2.9602 ; -0.8316 -0.5860 -2.1006 3.6035 -1.8423 ; 2.4511 2.2394 -0.7538 -3.6934 2.4585 ; 8.3858 -3.1739 3.7822 -0.6249 1.8829 ; -3.3585 14.3426 -10.5703 -3.8785 -10.3111 ];
B5 = zeros(5, 1);
c5 = [0 ; 0 ; 0 ; 0 ; 0 ];
options.uTrans = [0.0; 0.0; 0.0; 0.0; 0.0];
options.U = 0.5 * zonotope([zeros(5, 1), diag([0.169; 0; 0; 0; 1.4684])]);
flow5 = linearSys('linearSys5', A5, B5, c5);


%define invariants---------------------------------------------------------

inv_l1 =  mptPolytope(struct('A', [-1 0 0 0 0 ], 'b', [- 3]));
inv_l2 =  mptPolytope(struct('A', [-1 0 0 0 0 ], 'b', [- 2]));
inv_l3 =  mptPolytope(struct('A', [-1 0 0 0 0 ], 'b', [- 1]));
inv_l4 =  mptPolytope(struct('A', [-1 0 0 0 0 ], 'b', [- 0]));
inv_l5 =  mptPolytope(struct('A', [1 0 0 0 0 ], 'b', [ 1]));

%define transitions--------------------------------------------------------

%  l1 -> l2 
guard =  mptPolytope(struct('A', [1 0 0 0 0 ; -1 0 0 0 0 ], 'b', [3; -3]));
reset.A = eye(5);
reset.b = zeros(5, 1);
trans_l1{1} = transition(guard, reset, 2, 'l1', 'l2');

%  l2 -> l3 
guard =  mptPolytope(struct('A', [1 0 0 0 0 ; -1 0 0 0 0 ], 'b', [2; -2]));
reset.A = eye(5);
reset.b = zeros(5, 1);
trans_l2{1} = transition(guard, reset, 3, 'l2', 'l3');

%  l3 -> l4 
guard =  mptPolytope(struct('A', [1 0 0 0 0 ; -1 0 0 0 0 ], 'b', [1; -1]));
reset.A = eye(5);
reset.b = zeros(5, 1);
trans_l3{1} = transition(guard, reset, 4, 'l3', 'l4');

%  l4 -> l5 
guard =  mptPolytope(struct('A', [1 0 0 0 0 ; -1 0 0 0 0 ], 'b', [0; 0]));
reset.A = eye(5);
reset.b = zeros(5, 1);
trans_l4{1} = transition(guard, reset, 5, 'l4', 'l5');

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

options.uLoc{5} = 0;
options.uLocTrans{5} = 0;
options.Uloc{5} = zonotope(0);


loc{1} = location('l1', 1, inv_l1, trans_l1, flow1);
loc{2} = location('l2', 2, inv_l2, trans_l2, flow2);
loc{3} = location('l3', 3, inv_l3, trans_l3, flow3);
loc{4} = location('l4', 4, inv_l4, trans_l4, flow4);
loc{5} = location('l5', 5, inv_l5, {}, flow5);

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
