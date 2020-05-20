function HA = cora_bouncing_ball_ha(~)
% vars = [x v]

%% equation:
% x' = v v' = -9.81 t' = 1
dynA = [0 1 0; 0 0 0; 0 0 0];
dynB = [0; 0;0]; % no inputs
dync = [0; -9.81;1];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   x >= 0
invA = [-1 0 0];
invb = 0;
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);
% 
% Icenter= [7.5;0;0];
% Idelta = [7.5;20;0];
% inv = zonotope([Icenter,diag(Idelta)]);
% inv = polytope(inv);

% syms a1 a2; % instantiate symbolic variables
% s = [7.5 + 0*a1; 0 + 0*a2]; % create symbolic function
% c = taylm(s, interval([0,-20],[15;20]), 6);  % generate Taylor model
% inv = zonotope(c);

% inv = interval([0; -1e3;0], [1e3; 1e3;0]);
% 
% inv = halfspace([1,0,0],0); % Is not recognized by hybridAutomaton
% inv = constrainedHyperplane(temp,[-1 0],0);


trans = {};
%% equation:
%     x:= x v:= -0.75v 
resetA = [1 0 0; 0 -0.75 0; 0 0 1];
resetb = [0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%    x = 0 & v <= 0 
guardA = [-1 0 0; 1 0 0; 0 1 0];
guardb = [0;0;0];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);


trans{1} = transition(guard, reset, 1, 'dummy', 'names');

loc{1} = location('S1',1, inv, trans, dynamics);

HA = hybridAutomaton(loc);

end