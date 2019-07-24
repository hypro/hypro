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
% invA = [-1 0];
% invb = 0;
% invOpt = struct('A', invA, 'b', invb);
% inv = mptPolytope(invOpt);
% 
% trans = {};
% %% equation:
% %     x:= x v:= -0.75v 
% resetA = [1 0; 0 -0.75];
% resetb = [0;0];
% reset = struct('A', resetA, 'b', resetb);
% 
% %% equation:
% %    x = 0 & v <= 0 
% guardA = [-1 0; 1 0; 0 1];
% guardb = [0;0;0];
% guardOpt = struct('A', guardA, 'b', guardb);
% guard = mptPolytope(guardOpt);

%define large and small distance
dist = 1e3;
eps = 1e-6;
alpha = -0.75; %rebound factor

%invariant
inv = interval([-2*eps; -dist], [dist; dist]);
%guard sets
guard = interval([-eps; -dist], [0; -eps]); 
%resets
reset.A = [0, 0; 0, alpha]; reset.b = zeros(2,1);

% trans{1} = transition(guard, reset, 1, 'dummy', 'names');
% 
% loc{1} = location('S1',1, inv, trans, dynamics);
% 
% HA = hybridAutomaton(loc);

trans{1} = transition(guard,reset,1,'a','b'); %--> next loc: 1; 'a', 'b' are dummies
%specify location
loc{1} = location('loc1',1,inv,trans,dynamics); 
%specify hybrid automata
HA = hybridAutomaton(loc); % for "geometric intersection"


end