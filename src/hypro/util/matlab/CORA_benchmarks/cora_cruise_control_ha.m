function HA = cora_cruise_control_ha(~)


%% Generated on 01-Jul-2019

%---------------Automaton created from Component 'system'------------------

%% Interface Specification:
%   This section clarifies the meaning of state & input dimensions
%   by showing their mapping to SpaceEx variable names. 

% Component 1 (system.cruise_control_1):
%  state x := [v; x; t]
%  input u := [uDummy]

%-------------------Component system.cruise_control_1----------------------

%-------------------------------State q1-----------------------------------

%% equation:
%   v' == -t - 2.5 &
%   x' == 0 &
%   t' == 1
dynA = [0,0,-1;0,0,0;0,0,0];
dynB = zeros(3);
dync = [-2.5;0;1];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   v >= 15 & v <= 40 &
%    t >= 0 & t<= 2.5
invA = [-1,0,0;1,0,0;0,0,-1;0,0,1];
invb = [-15;40;0;2.5];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%   
resetA = eye(3);
resetb = [0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   t == 2.5 & v >= 15 & v <= 40
guardA = [-1,0,0;1,0,0;0,0,-1;0,0,1];
guardb = [-15;40;-2.5;2.5];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 2, 'dummy', 'names');

%% equation:
%   t := 0
resetA = [1,0,0;0,1,0;0,0,0];
resetb = [0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   t >= 0 & t <= 2.5 &
%   v >= 15 & v <= 16
guardA = [0,0,-1;0,0,1;-1,0,0;1,0,0];
guardb = [0;2.5;-15;16];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{2} = transition(guard, reset, 4, 'dummy', 'names');

loc{1} = location('S1',1, inv, trans, dynamics);



%-------------------------------State q2-----------------------------------

%% equation:
%   v' == -5 &
%   x' == 0 &
%   t' ==0
dynA = [0,0,0;0,0,0;0,0,0];
dynB = zeros(3);
dync = [-5;0;0];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   v >= 15 & v <= 40
invA = [-1,0,0;1,0,0];
invb = [-15;40];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%   t := 0
resetA = [1,0,0;0,1,0;0,0,0];
resetb = [0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   t == 2.5 & v >= 15 & v <= 16
guardA = [-1,0,0;1,0,0;0,0,-1;0,0,1];
guardb = [-15;16;-2.5;2.5];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 4, 'dummy', 'names');

loc{2} = location('S2',2, inv, trans, dynamics);


%-------------------------------State q3-----------------------------------

%% equation:
%   v' == -2.5 &
%   x' == 0 &
%   t' == 0
dynA = [0,0,0;0,0,0;0,0,0];
dynB = zeros(3);
dync = [-2.5;0;0];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   v >= 5 & v <= 20
invA = [-1,0,0;1,0,0];
invb = [-5;20];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%   t := 0
resetA = [1,0,0;0,1,0;0,0,0];
resetb = [0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   t == 1.3 & v >= 18 & v <= 20
guardA = [-1,0,0;1,0,0;0,0,-1;0,0,1];
guardb = [-18;20;-1.3;1.3];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 1, 'dummy', 'names');

%% equation:
%   x := 0
resetA = [1,0,0;0,0,0;0,0,1];
resetb = [0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   t == 1.3 & v >= 5 & v <= 11
guardA = [-1,0,0;1,0,0;0,0,-1;0,0,1];
guardb = [-5;11;-1.3;1.3];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{2} = transition(guard, reset, 5, 'dummy', 'names');

loc{3} = location('S3',3, inv, trans, dynamics);



%-------------------------------State q4-----------------------------------

%% equation:
%   v' == -t - 1.2 &
%   x' == 0 &
%   t' == 0.5
dynA = [0,0,-1;0,0,0;0,0,0];
dynB = zeros(3);
dync = [-1.2;0;0.5];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   v >= 5 & v <= 20 &
%   t >= 0 & t <= 1.3
invA = [-1,0,0;1,0,0;0,0,-1;0,0,1];
invb = [-5;20;0;1.3];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%   t := 0
resetA = [1,0,0;0,1,0;0,0,0];
resetb = [0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   0 <= t <= 1.3 & v >= 18 & v <= 20
guardA = [-1,0,0;1,0,0;0,0,-1;0,0,1];
guardb = [-18;20;0;1.3];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 1, 'dummy', 'names');

%% equation:
%   x := 0
resetA = [1,0,0;0,0,0;0,0,1];
resetb = [0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   t >= 0 & t <= 1.3 &
%   v >= 5 & v <= 11
guardA = [0,0,-1;0,0,1;-1,0,0;1,0,0];
guardb = [0;1.3;-5;11];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{2} = transition(guard, reset, 5, 'dummy', 'names');

%% equation:
%
resetA = [1,0,0;0,1,0;0,0,1];
resetb = [0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   t == 1.3 & 
%   v >= 5 & v <= 20
guardA = [0,0,-1;0,0,1;-1,0,0;1,0,0];
guardb = [-1.3;1.3;-5;20];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{3} = transition(guard, reset, 3, 'dummy', 'names');

loc{4} = location('S4',4, inv, trans, dynamics);



%-------------------------------State q5-----------------------------------

%% equation:
%   v' == -0.001*x - 0.052*v &
%   x' == v &
%   t' == 0
dynA = [-0.052,-0.001,0;1,0,0;0,0,0];
dynB = zeros(3);
dync = [0;0;0];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   v >= -15 & v <= 15 &
%   x >= -500 & x <= 500
invA = [-1,0,0;1,0,0;0,-1,0;0,1,0];
invb = [15;15;500;500];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%   t := 0
resetA = [1,0,0;0,1,0;0,0,0];
resetb = [0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   v >= 13 & v <= 15 &
%   x >= -500 & x <= 500
guardA = [-1,0,0;1,0,0;0,-1,0;0,1,0];
guardb = [-13;15;500;500];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 4, 'dummy', 'names');

%% equation:
%   
resetA = [1,0,0;0,1,0;0,0,1];
resetb = [0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   v >= -15 & v <= -14 &
%   x >= -500 & x <= 500
guardA = [-1,0,0;1,0,0;0,-1,0;0,1,0];
guardb = [15;-14;500;500];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{2} = transition(guard, reset, 6, 'dummy', 'names');

loc{5} = location('S5',5, inv, trans, dynamics);



%-------------------------------State q6-----------------------------------

%% equation:
%   v' == 1.5 &
%   x' == 0 &
%   t' == 0
dynA = [0,0,0;0,0,0;0,0,0];
dynB = zeros(3);
dync = [1.5;0;0];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   v >= -20 & v <= -5
invA = [-1,0,0;1,0,0];
invb = [20;-5];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%   x := 0
resetA = [1,0,0;0,0,0;0,0,1];
resetb = [0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   v >= -6 & v <= -5 &
%   x >= -500 & x <= 500
guardA = [-1,0,0;1,0,0;0,-1,0;0,1,0];
guardb = [6;-5;500;500];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 5, 'dummy', 'names');

loc{6} = location('S6',6, inv, trans, dynamics);

HA = hybridAutomaton(loc);


end