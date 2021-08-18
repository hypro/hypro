function HA = intersectInvariant_experiments_ha(~)


%------------------------------State loc1---------------------------------
% flow :
%   x' == 1
%   t' == 1 
dynA = [0 0; 0 0];
dynB = [0;0];
dync = [1;1];
dynamics = linearSys('linearSys', dynA, dynB, dync);
% invariant:
%   0 <= x <= 10.02
%   0 <= t <= 10.02
invA = [-1 0; 1 0; 0 -1; 0 1];
invb = [0;10.02;0;10.02];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

% loc1 -> loc2
trans = {};
%% equation:
resetA = [1 0; 0 1];
resetb = [0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
% t <= 10.08
guardA = [0 1];
guardb = 10.1;

%   t == 10
% guardA = [0 -1; 0 1];
% guardb = [-10;10];

%   t <= 6.99
% guardA = [0 1];
% guardb = 6.99;
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 2, 'dummy', 'names');

loc{1} = location('S1',1, inv, trans, dynamics);

%------------------------------State loc2---------------------------------
% flow :
%   x' == -1&
%   t' == 1 
dynA = [0 0; 0 0];
dynB = [0;0];
dync = [-1;1];
dynamics = linearSys('linearSys', dynA, dynB, dync);
% invariant: x <= 20 t <= 20
invA = [1 0; 0 1];
invb = [20; 20];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};

loc{2} = location('S2',2, inv, trans, dynamics);

HA = hybridAutomaton(loc);

