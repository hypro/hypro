function HA = cora_zeno_ha(~)


%-----------------State 1---------------------
% h1' = 2 h2' = -2 t' = 1
dynA = [0 0 0;0 0 0; 0 0 0];
dynB = [0;0;0];
dync = [2;-2;1];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   0<=h1<=max
%  0<=h2
invA = [1 0 0; -1 0 0; 0 -1 0];
invb = [5;0;0];   
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%    t := 0
resetA = [1 0 0; 0 1 0; 0 0 0];
resetb = [0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%  t >= 0
guardA = [0 0 -1];
guardb = [0];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 2, 'dummy', 'names');

loc{1} = location('S1',1, inv, trans, dynamics);



%-----------------State 2---------------------

%% equation:
% h1' = -1 h2'= 1 t' = 1 
dynA = [0 0 0; 0 0 0; 0 0 0];
dynB = [0;0;0];
dync = [-1;1;1];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   0 <= h1 0 <= h2 <= max
invA = [-1 0 0; 0 1 0; 0 -1 0];
invb = [0;5;0];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%    t := 0
resetA = [1 0 0; 0 1 0; 0 0 0];
resetb = [0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%    t >= 0
guardA = [0 0 -1];
guardb = [0];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 1, 'dummy', 'names');

loc{2} = location('S2',2, inv, trans, dynamics);

HA = hybridAutomaton(loc);


end