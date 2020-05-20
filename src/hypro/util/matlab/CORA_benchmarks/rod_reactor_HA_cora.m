function HA = rod_reactor_HA_cora(~)

%---------------Automaton created from Component 'system'------------------

% Interface Specification:
%   This section clarifies the meaning of state & input dimensions
%   by showing their mapping to SpaceEx variable names. 

% Component 1 (system.rod_reactor_1):
%  state x := [x; c1; c2]
%  input u := [uDummy]

%--------------------Component system.rod_reactor_1------------------------

%------------------------------State rod_1---------------------------------

% flow :
%   x' == 0.1*x - 56 &
%   c1' == 1 &
%   c2' == 1
%   gc' == 1
dynA = [0.1,0,0;0,0,0;0,0,0];
dynB = [0;0;0];
dync = [-56;1;1];
dynamics = linearSys('linearSys', dynA, dynB, dync);
% invariant:
%   x>=510
invA = [-1,0,0];
invb = -510;
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

% rod1 -> noRods
trans = {};
%% equation:
%   c1=0
resetA = [1,0,0;0,0,0;0,0,1];
resetb = [0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   x==510
guardA = [1 0 0; -1 0 0];
guardb = [510;-510];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 2, 'dummy', 'names');

loc{1} = location('S1',1, inv, trans, dynamics);

%-----------------------------State no_rods--------------------------------

% equation:
%   x' == 0.1*x - 50 &
%   c1' == 1 &
%   c2' == 1 &
%   gc' == 1
dynA = [0.1,0,0;0,0,0;0,0,0];
dynB = [0;0;0];
dync = [-50;1;1];
dynamics = linearSys('linearSys', dynA, dynB, dync);

% equation:
%   x<=550
invA = [1 0 0];
invb = 550;
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

%noRod -> rod1
trans = {};
% equation:
%   
resetA = eye(3);
resetb = [0;0;0];
reset = struct('A', resetA, 'b', resetb);

% equation:
%   x == 550 &
%   c1 >= 20
guardA = [1,0,0;-1,0,0;0,-1,0];
guardb = ...
[550;-550;-20];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 1, 'dummy', 'names');

%noRod -> rod2
% equation:
%   
resetA = eye(3);
resetb = [0;0;0];
reset = struct('A', resetA, 'b', resetb);

% equation:
%   x==550 &
%   c2>=20
guardA = [1,0,0;-1,0,0;0,0,-1];
guardb = [550;-550;-20];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{2} = transition(guard, reset, 3, 'dummy', 'names');

loc{2} = location('S2',2, inv, trans, dynamics);



%------------------------------State rod_2---------------------------------

% equation:
%   x' == 0.1*x - 60 &
%   c1' == 1 &
%   c2' == 1 &
%   gc' == 1
dynA = [0.1,0,0;0,0,0;0,0,0];
dynB = [0;0;0];
dync = [-60;1;1];
dynamics = linearSys('linearSys', dynA, dynB, dync);

% equation:
%   x>=510
invA = [-1,0,0];
invb = -510;
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

% rod2 -> noRod
trans = {};
%equation:
%   c2=0
resetA = [1,0,0;0,1,0;0,0,0];
resetb = [0;0;0];
reset = struct('A', resetA, 'b', resetb);

% equation:
%   x==510
guardA = [1 0 0; -1 0 0];
guardb = [510;-510];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 2, 'dummy', 'names');

loc{3} = location('S3',3, inv, trans, dynamics);

HA = hybridAutomaton(loc);


end