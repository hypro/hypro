function HA = bouncing_ball_ha(~)
% vars = [x v]

%% equation:
% x' = v v' = -9.81
dynA = [0 1; 0 0];
dynB = zeros(2);
dync = [0;-9.81];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   x >= 0
invA = [-1 0];
invb = 0;
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%     x:= x v:= -0.75v 
resetA = [1 0; 0 -0.75];
resetb = [0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%    x = 0 & v <= 0 
guardA = [-1 0; 1 0; 0 1];
guardb = [0;0;0];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 1, 'dummy', 'names');

loc{1} = location('S1',1, inv, trans, dynamics);

HA = hybridAutomaton(loc);


end