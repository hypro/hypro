function HA = car_ha()

%------------------------------acc---------------------------------

%% equation dynamics:
%    v' = 5 d' = 19.44 - v t' = 1
dynA = [0 0 0; -1 0 0 ; 0 0 0];
dynB = zeros(3,1);
dync = [5; 19.44; 1];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation invariant:
%   d >= 20
invA = [0 -1 0];
invb = -20;
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

%% equation guard (acc -> brake):
%   true (v <= inf)
guardA = [1 0 0];
guardb = inf;
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

%% dummy reset
%   v = v & d = d
resetA = eye(3);
resetb = ...
[0;0;0];
reset = struct('A', resetA, 'b', resetb);

trans1{1} = transition(guard, reset, 2, 'acc', 'brake');

loc{1} = location('acc',1, inv, trans1, dynamics);

%------------------------------brake---------------------------------

%% equation dynamics:
%    v' = -7 d' = 19.44 - v t' = 1
dynA = [0 0 0; -1 0 0; 0 0 0];
dynB = zeros(3,1);
dync = [-7; 19.44; 1];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation invariant:
%   v >= 0
invA = [-1 0 0];
invb = 0;
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

%% equation guard (brake -> acc):
%   d > 20
guardA = [0 -1 0];
guardb = -20;
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans2{1} = transition(guard, reset, 1, 'brake', 'acc');

%% equation guard (brake -> idle):
%   true (v <= inf)
guardA = [1 0 0];
guardb = inf;
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans2{2} = transition(guard, reset, 3, 'brake', 'acc');

loc{2} = location('brake', 2, inv, trans2, dynamics);

%------------------------------idle---------------------------------

%% equation dynamics:
%    v' = 0 d' = 19.44 - v t' = 1
dynA = [0 0 0; -1 0 0; 0 0 0];
dynB = zeros(3,1);
dync = [0;19.44;1];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation invariant:
%   d >= 20
invA = [0 -1 0];
invb = -20;
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

%% equation guard (idle -> acc):
%   d >= 20
guardA = [0 -1 0];
guardb = -20;
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans3{1} = transition(guard, reset, 1, 'idle', 'acc');

loc{3} = location('S1',3, inv, trans3, dynamics);

HA = hybridAutomaton(loc);
end