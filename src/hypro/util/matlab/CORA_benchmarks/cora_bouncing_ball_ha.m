function HA = cora_bouncing_ball_ha(~)
% vars = [x v]

%% equation:
% x' = v v' = -9.81
dynA = [0 1; 0 0];
dynB = [0; 0]; % no inputs
dync = [0; -9.81];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   x >= 0
invA = [-1 0];
invb = 0;
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

% Icenter= [7.5;0];
% Idelta = [7.5;20];
% inv = zonotope([Icenter,diag(Idelta)]);
% inv = polytope(inv);

% syms a1 a2; % instantiate symbolic variables
% s = [7.5 + 0*a1; 0 + 0*a2]; % create symbolic function
% c = taylm(s, interval([0,-20],[15;20]), 6);  % generate Taylor model
% inv = zonotope(c);

% inv = interval([0; -1e3], [1e3; 1e3]);

% temp = halfspace([1,0],0); 
% inv = constrainedHyperplane(temp,[-1 0],0);


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

trans{1} = transition(guard,reset,1,'a','b'); %--> next loc: 1; 'a', 'b' are dummies
%specify location
loc{1} = location('loc1',1,inv,trans,dynamics); 
%specify hybrid automata
HA = hybridAutomaton(loc); % for "geometric intersection"


end