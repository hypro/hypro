function HA = cora_linear_switching_system_ha(~)


%% Generated on 02-Jul-2019

%---------------Automaton created from Component 'system'------------------

%% Interface Specification:
%   This section clarifies the meaning of state & input dimensions
%   by showing their mapping to SpaceEx variable names. 

% Component 1 (system.switch_1):
%  state x := [x1; x2; x3; x4; x5]
%  input u := [u]

%-----------------------Component system.switch_1--------------------------

%-------------------------------State q1-----------------------------------

%% equation:
%   x1' == -0.8047*x1 + 8.7420*x2 - 2.4591*x3 - 8.2714*x4 - 1.8640*x5 -0.0845*u &
%       x2' == -8.6329*x1 - 0.5860*x2 - 2.1006*x3 + 3.6035*x4 - 1.8423*x5 &
%       x3' == 2.4511*x1 + 2.2394*x2 - 0.7538*x3 - 3.6934*x4 + 2.4585*x5 &
%       x4' == 8.3858*x1 - 3.1739*x2 + 3.7822*x3 - 0.6249*x4 + 1.8829*x5 &
%       x5' == 1.8302*x1 + 1.9869*x2 - 2.4539*x3 - 1.7726*x4 - 0.7911*x5 -0.0845*u
dynA = ...
[-0.8047,8.7420,-2.4591,-8.2714,-1.8640;...
-8.6329,-0.58560,-2.1006,3.60345,-1.8423;...
2.4511,2.23948,-0.7538,-3.6934,2.4585;...
8.3858,-3.1739,3.7822,-0.6249,1.8829;...
1.8302,1.9869,-2.4539,-1.7726,-0.7911];
dynB = zeros(5,1);
dync = [0;0;0;0;0];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   x1 >= 3
invA = [-1,0,0,0,0];
invb = -3;
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%   
resetA = eye(5);
resetb = [0;0;0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   x1 == 3
guardA = [-1,0,0,0,0;1,0,0,0,0];
guardb = [-3;3];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 2, 'dummy', 'names');

loc{1} = location('S1',1, inv, trans, dynamics);



%-------------------------------State q2-----------------------------------

%% equation:
%    x1' == -0.8316*x1 + 8.7658*x2 - 2.4744*x3 - 8.2608*x4 - 1.9033*x5 -0.0845*u &
%       x2' == -0.8316*x1 - 0.5860*x2 - 2.1006*x3 + 3.6035*x4 - 1.8423*x5 &
%       x3' == 2.4511*x1 + 2.2394*x2 - 0.7538*x3 - 3.6934*x4 + 2.4585*x5 &
%       x4' == 8.3858*x1 - 3.1739*x2 + 3.7822*x3 - 0.6249*x4 + 1.8829*x5 &
%       x5' == 1.5964*x1 + 2.1936*x2 - 2.5872*x3 - 1.6812*x4 - 1.1324*x5 -0.7342*u
dynA = ...
[-0.8316,8.7658,-2.4744,-8.2608,-1.9033;...
-0.8316,-0.5860,-2.1006,3.6035,-1.8423;...
2.4511,2.2394,-0.7538,-3.6934,2.4585;...
8.3858,-3.1739,3.7822,-0.6249,1.8829;...
1.5964,2.1936,-2.5872,-1.6812,-1.1324];
dynB = zeros(5,1);
dync = [0;0;0;0;0];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   x1 >= 2
invA = [-1,0,0,0,0];
invb = -2;
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%   
resetA = eye(5);
resetb = [0;0;0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   x1 == 2
guardA = [-1,0,0,0,0;1,0,0,0,0];
guardb = [-2;2];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 3, 'dummy', 'names');

loc{2} = location('S2',2, inv, trans, dynamics);



%-------------------------------State q3-----------------------------------

%% equation:
%   x1' == -0.9275*x1 + 8.8628*x2 - 2.5428*x3 - 8.2329*x4 - 2.0324*x5 -0.0845*u &
%       x2' == -0.8316*x1 - 0.5860*x2 - 2.1006*x3 + 3.6035*x4 - 1.8423*x5 &
%       x3' == 2.4511*x1 + 2.2394*x2 - 0.7538*x3 - 3.6934*x4 + 2.4585*x5 &
%       x4' == 8.3858*x1 - 3.1739*x2 + 3.7822*x3 - 0.6249*x4 + 1.8829*x5 &
%       x5' == 0.7635*x1 + 3.0357*x2 - 3.1814*x3 - 1.4388*x4 - 2.2538*x5 -0.7342*u
dynA = ...
[-0.9275,8.8628,-2.5428,-8.2329,-2.0324;...
-0.8316,-0.5860,-2.1006,3.6035,-1.8423;...
2.4511,2.2394,-0.7538,-3.6934,2.4585;...
8.3858,-3.1739,3.7822,-0.6249,1.8829;...
0.7635,3.0357,-3.1814,-1.4388,-2.2538];
dynB = zeros(5,1);
dync = [0;0;0;0;0];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   x1 >= 1
invA = [-1,0,0,0,0];
invb = -1;
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%   
resetA = eye(5);
resetb = [0;0;0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   x1 == 1
guardA = [-1,0,0,0,0;1,0,0,0,0];
guardb = [-1;1];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 4, 'dummy', 'names');

loc{3} = location('S3',3, inv, trans, dynamics);



%-------------------------------State q4-----------------------------------

%% equation:
%   x1' == -1.4021*x1 + 10.1647*x2 - 3.3937*x3 - 8.5139*x4 - 2.9602*x5 -0.0845*u &
%       x2' == -0.8316*x1 - 0.5860*x2 - 2.1006*x3 + 3.6035*x4 - 1.8423*x5 &
%       x3' == 2.4511*x1 + 2.2394*x2 - 0.7538*x3 - 3.6934*x4 + 2.4585*x5 &
%       x4' == 8.3858*x1 - 3.1739*x2 + 3.7822*x3 - 0.6249*x4 + 1.8829*x5 &
%       x5' == -3.3585*x1 + 14.3426*x2 - 10.5703*x3 - 3.8785*x4 - 10.3111*x5 -0.7342*u
dynA = ...
[-1.4021,10.1647,-3.3937,-8.5139,-2.9602;...
-0.8316,-0.5860,-2.1006,3.6035,-1.8423;...
2.4511,2.2394,-0.7538,-3.6934,2.4585;
8.3858,-3.1739,3.7822,-0.6249,1.8829;...
-3.3585,14.3426,-10.5703,-3.8785,-10.3111];
dynB = zeros(5,1);
dync = [0;0;0;0;0];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   x1 >= 0
invA = [-1,0,0,0,0];
invb = 0;
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%   
resetA = eye(5);
resetb = [0;0;0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   x1 == 0
guardA = [-1,0,0,0,0;1,0,0,0,0];
guardb = [0;0];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 5, 'dummy', 'names');

loc{4} = location('S4',4, inv, trans, dynamics);



%-------------------------------State q5-----------------------------------

%% equation:
%   x1' == -1.4021*x1 + 10.1647*x2 - 3.3937*x3 - 8.5139*x4 - 2.9602*x5 - 0.0845*u &
%   x2' == -0.8316*x1 - 0.5860*x2 - 2.1006*x3 + 3.6035*x4 - 1.8423*x5 &
%   x3' == 2.4511*x1 + 2.2394*x2 - 0.7538*x3 - 3.6934*x4 +2.4585*x5 &
%   x4' == 8.3858*x1 - 3.1739*x2 + 3.7822*x3 - 0.6249*x4 +1.8829*x5 &
%   x5' == -3.3585*x1 + 14.3426*x2 - 10.5703*x3 - 3.8785*x4 - 10.3111*x5 - 0.7342*u
dynA = ...
[-1.4021,10.1647,-3.3937,-8.5139,-2.9602;...
-0.83160,-0.5860,-2.1006,3.6035,-1.8423;...
2.4511,2.2394,-0.7538,-3.6934,2.4585;...
8.3858,-3.1739,3.7822,-0.6249,1.8829;...
-3.3585,14.3426,-10.5703,-3.8785,-10.3111];
dynB = zeros(5,1);
dync = [0;0;0;0;0];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%    x1 <= 1
invA = [1,0,0,0,0];
invb = 1;
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
loc{5} = location('S5',5, inv, trans, dynamics);



HA = hybridAutomaton(loc);


end
