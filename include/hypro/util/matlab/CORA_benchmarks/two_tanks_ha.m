function HA = two_tanks_ha(~)

%-----------------------Component system.switch_1--------------------------
% vars = [x1,x2]

%-------------------------------State q1-----------------------------------

%% equation:
%   x1' == -x1 - 2 + [-0.01,0.01]
%       x2' == x1 + [-0.01,0.01]

dynA = [-1 0; 1 0];
dynB = zeros(2);
dync = [-2;0];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   x1 >= -1 & x2 <= 1
invA = [-1 0; 0 1];
invb = [1;1];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%   
resetA = eye(2);
resetb = [0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   x1 == -1
guardA = [-1 0;1 0];
guardb = [1;-1];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 2, 'dummy', 'names');

%% equation:
%   
resetA = eye(2);
resetb = [0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   x2 == 1
guardA = [0 -1;0 1];
guardb = [-1;1];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{2} = transition(guard, reset, 3, 'dummy', 'names');

loc{1} = location('S1',1, inv, trans, dynamics);



%-------------------------------State q2-----------------------------------

%% equation:
%    x1' == -x1 + 3 + [-0.01,0.01]
%    x2' == x1 + [-0.01,0.01]

dynA = [-1 0; 1 0];
dynB = zeros(2);
dync = [3;0];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   x2 <= 1
invA = [0 1];
invb = 1;
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%   
resetA = eye(2);
resetb = [0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   x2 == 1
guardA = [0 -1;0 1];
guardb = [-1;1];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 3, 'dummy', 'names');

loc{2} = location('S2',2, inv, trans, dynamics);



%-------------------------------State q3-----------------------------------

%% equation:
%   x1' == -x1 - 2 + [-0.01,0.01]
%   x2' == x1 - x2 - 5 + [-0.01,0.01]

dynA = [-1 0; 1 -1];
dynB = zeros(2);
dync = [-2;-5];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   x1 >= -1 x2 >= 0
invA = [-1 0; 0 -1];
invb = [1;0];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%   
resetA = eye(2);
resetb = [0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   x2 == 0
guardA = [0 -1; 0 1];
guardb = [0;0];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 1, 'dummy', 'names');
%% equation:
%   x1 == -1
guardA = [-1 0; 1 0];
guardb = [1;-1];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{2} = transition(guard, reset, 4, 'dummy', 'names');

loc{3} = location('S3',3, inv, trans, dynamics);



%-------------------------------State q4-----------------------------------

%% equation:
%   x1' == -x1 + 3 + [-0.01,0.01]
%   x2' == x1 - x2 - 5 + [-0.01,0.01]

dynA =[-1 0; 1 -1];
dynB = zeros(2);
dync = [3;-5];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   x1 <= 1 x2 >= 0
invA = [1 0; 0 -1];
invb = [1; 0];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%   
resetA = eye(2);
resetb = [0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   x1 == 1
guardA = [-1 0;1 0];
guardb = [-1;1];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 3, 'dummy', 'names');

%% equation:
%   x2 == 0
guardA = [0 -1; 0 1];
guardb = [0;0];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{2} = transition(guard, reset, 2, 'dummy', 'names');

loc{4} = location('S4',4, inv, trans, dynamics);


HA = hybridAutomaton(loc);


end