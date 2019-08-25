function HA = boost_v1_ha_cora(~)


%% Generated on 17-Jun-2019

%-------------Automaton created from Component 'buckboost'-----------------

%% Interface Specification:
%   This section clarifies the meaning of state & input dimensions
%   by showing their mapping to SpaceEx variable names. 

% Component 1 (buckboost.buckboost_template_1):
%  state x := [il; t; gt; vc]
%  input u := [Vs]

%---------------Component buckboost.buckboost_template_1-------------------

%----------------------------State charging--------------------------------

%% equation:
%   il' == (a00c * il + a01c * vc + b0c * Vs) & vc' == (a10c * il + a11c * vc + b1c * Vs) & t' == 1 & gt' == 1
dynA = ...
[0,0,0,0;0,0,0,0;0,0,0,0;0,0,0,-40000];
dynB = ...
[20000;0;0;0];
dync = ...
[0;1;1;0];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   t >= 0 & t <= D*T & gt >= 0 & gt <= tmax & D >= 0 & D <= 1 & il >= -bounds & il <= bounds & vc >= -bounds & vc <= bounds
invA = ...
[0,-1,0,0;...
0,1,0,0;...
0,0,-1,0;...
0,0,1,0;...
0,0,0,0;...
0,0,0,0;...
-1,0,0,0;...
1,0,0,0;...
0,0,0,-1;...
0,0,0,1];
invb = ...
[-0;3.333E-06;-0;...
0.00025;...
0.3333;0.6666;...
1000;1000;1000;1000];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%   t' == 0 & gt' == gt & vc' == vc & il' == il
resetA = ...
[1,0,0,0;0,0,0,0;0,0,1,0;0,0,0,1];
resetb = ...
[0;0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   t >= D*T
guardA = ...
[0,-1,0,0];
guardb = ...
[-3.3333E-06];
guard = halfspace(guardA,guardb); 

trans{1} = transition(guard, reset, 2, 'dummy', 'names');
loc{1} = location('S1',1, inv, trans, dynamics);

%---------------------------State discharging------------------------------

%% equation:
%   il' == (a00o * il + a01o * vc + b0o * Vs) & vc' == (a10o * il + a11o * vc + b1o * Vs) & t' == 1 & gt' == 1
dynA = ...
[0,0,0,-20000;0,0,0,0;0,0,0,0;40000,0,0,-40000];
dynB = ...
[20000;0;0;0];
dync = ...
[0;1;1;0];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   t >= 0 & t <= (1-D)*T & gt >= 0 & gt <= tmax & D >= 0 & D <= 1 & vc >= -bounds & vc <= bounds & il >= -bounds & il <= bounds
invA = ...
[0,-1,0,0;0,1,0,0;0,0,-1,0;0,0,1,0;0,0,0,0;0,0,0,0;0,0,0,-1;0,0,0,1;-1,...
0,0,0;1,0,0,0];
invb = ...
[-0;6.6667E-06;-0;...
0.00025;...
0.3333;0.6666;...
1000;1000;1000;1000];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%   t' == 0 & gt' == gt & vc' == vc & il' == il
resetA = ...
[1,0,0,0;0,0,0,0;0,0,1,0;0,0,0,1];
resetb = ...
[0;0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   t >= (1-D)*T
guardA = ...
[0,-1,0,0];
guardb = ...
[-6.6667E-06];
guard = halfspace(guardA,guardb); 


trans{1} = transition(guard, reset, 1, 'dummy', 'names');

loc{2} = location('S2',2, inv, trans, dynamics);



HA = hybridAutomaton(loc);


end