function HA = non_aligned_ha(~)


%------------------------------State loc1---------------------------------
% flow :
%   x' == x + 50
%   t' == 1 
dynA = [1 0; 0 0];
dynB = [0;0];
dync = [50;1];
dynamics = linearSys('linearSys', dynA, dynB, dync);
% invariant:
%   x <= 23 t <= 5
invA = [1 0; 0 1];
invb = [23;5];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

% loc1 -> loc2
trans = {};
%% equation:
resetA = [1 0; 0 1];
resetb = [0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   22 <= x <= 23
guardA = [ -1 0; 1 0];
guardb = [-22; 23];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 2, 'dummy', 'names');

loc{1} = location('S1',1, inv, trans, dynamics);

%------------------------------State loc2---------------------------------
% flow :
%   x' == -1&
%   y' == 1 
dynA = [-1 0; 0 0];
dynB = [0;0];
dync = [0;1];
dynamics = linearSys('linearSys', dynA, dynB, dync);
% invariant: x >= 17
invA = [-1 0; 0 1];
invb = [-17;5];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
resetA = [1 0; 0 1];
resetb = [0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   17 <= x <= 18
guardA = [-1 0; 1 0];
guardb = [-17; 18];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 1, 'dummy', 'names');

loc{2} = location('S2',2, inv, trans, dynamics);

HA = hybridAutomaton(loc);

