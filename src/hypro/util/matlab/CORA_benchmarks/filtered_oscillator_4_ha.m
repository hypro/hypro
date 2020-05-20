function HA = filtered_oscillator_4_ha(~)


%% Generated on 01-Jul-2019

%---------------Automaton created from Component 'system'------------------

%% Interface Specification:
%   This section clarifies the meaning of state & input dimensions
%   by showing their mapping to SpaceEx variable names. 

% Component 1 (system.osc_w_4th_order_1):
%  state  [x; y; x1; x2; x3; z]
%  input u := [uDummy]

%------------------Component system.osc_w_4th_order_1----------------------

%-----------------State np---------------------

%% equation:
%   x' == -2*x+1.4 & y' == -y-0.7 & x1' == 5*x-5*x1 & x2' == 5*x1-5*x2 & x3' == 5*x2-5*x3 & z' == 5*x3-5*z 
dynA = [-2,0,0,0,0,0;...
        0,-1,0,0,0,0;...
        5,0,-5,0,0,0;...
        0,0,5,-5,0,0;...
        0,0,0,5,-5,0;...
        0,0,0,0,5,-5];
dynB = [0;0;0;0;0;0];
dync = [1.4;-0.7;0;0;0;0];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   x <= 0 & y+0.714286*x >= 0 
invA = [1,0,0,0,0,0;-0.714286,-1,0,0,0,0];
invb = [0;0];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%    x' == x & y' == y & x1' == x1 & x2' == x2 & x3' == x3 & z' == z 
resetA = eye(6);
resetb = [0;0;0;0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%    x == 0 & 0.714286*x+y >= 0 
guardA = [-0.714286,-1,0,0,0,0; 1 0 0 0 0 0; -1 0 0 0 0 0];
guardb = [0;0;0];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 3, 'dummy', 'names');

loc{1} = location('S1',1, inv, trans, dynamics);



%-----------------State nn~always~always~always~always---------------------

%% equation:
%   x' == -2*x-1.4 & y' == -y+0.7 & x1' == 5*x-5*x1 & x2' == 5*x1-5*x2 & x3' == 5*x2-5*x3 & z' == 5*x3-5*z 
dynA = [-2,0,0,0,0,0;...
        0,-1,0,0,0,0;...
        5,0,-5,0,0,0;...
        0,0,5,-5,0,0;...
        0,0,0,5,-5,0;...
        0,0,0,0,5,-5];
dynB = [0;0;0;0;0;0];
dync = [-1.4;0.7;0;0;0;0];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   x <= 0 & y+0.714286*x <= 0 
invA = [1,0,0,0,0,0;0.7142869,1,0,0,0,0];
invb = [0;0];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%    x' == x & y' == y & x1' == x1 & x2' == x2 & x3' == x3 & z' == z 
resetA = eye(6);
resetb = [0;0;0;0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%    y+0.714286*x == 0 & x <= 0 
guardA = [1,0,0,0,0,0;-0.714286,-1,0,0,0,0;0.714286,1,0,0,0,0];
guardb = [0;0;0];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 1, 'dummy', 'names');

loc{2} = location('S2',2, inv, trans, dynamics);



%-----------------State pp---------------------

%% equation:
%   x' == -2*x+1.4 & y' == -y-0.7 & x1' == 5*x-5*x1 & x2' == 5*x1-5*x2 & x3' == 5*x2-5*x3 & z' == 5*x3-5*z 
dynA = [-2,0,0,0,0,0;...
        0,-1,0,0,0,0;...
        5,0,-5,0,0,0;...
        0,0,5,-5,0,0;...
        0,0,0,5,-5,0;...
        0,0,0,0,5,-5];
dynB = [0;0;0;0;0;0];
dync = [1.4;-0.7;0;0;0;0];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   x >= 0 & y+0.714286*x >= 0 
invA = [-1,0,0,0,0,0;-0.714286,-1,0,0,0,0];
invb = [0;0];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%    x' == x & y' == y & x1' == x1 & x2' == x2 & x3' == x3 & z' == z 
resetA = eye(6);
resetb = [0;0;0;0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%    y+0.714286*x == 0 & x >= 0 
guardA = [-1,0,0,0,0,0;-0.714286,-1,0,0,0,0;0.714286,1,0,0,0,0];
guardb = [0;0;0];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 4, 'dummy', 'names');

loc{3} = location('S3',3, inv, trans, dynamics);



%-----------------State pn~always~always~always~always---------------------

%% equation:
%   x' == -2*x-1.4 & y' == -y+0.7 & x1' == 5*x-5*x1 & x2' == 5*x1-5*x2 & x3' == 5*x2-5*x3 & z' == 5*x3-5*z 
dynA = [-2,0,0,0,0,0;...
        0,-1,0,0,0,0;...
        5,0,-5,0,0,0;...
        0,0,5,-5,0,0;...
        0,0,0,5,-5,0;...
        0,0,0,0,5,-5];
dynB = [0;0;0;0;0;0];
dync = [-1.4;0.7;0;0;0;0];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   x >= 0 & y+0.714286*x <= 0 
invA = [-1,0,0,0,0,0;0.714286,1,0,0,0,0];
invb = [0;0];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%    x' == x & y' == y & x1' == x1 & x2' == x2 & x3' == x3 & z' == z 
resetA = eye(6);
resetb = [0;0;0;0;0;0];
reset = struct('A', resetA, 'b', resetb);

%% equation:
%    x == 0 & 0.714286*x+y <= 0 
guardA = [0.714286,1,0,0,0,0;-1,0,0,0,0,0;1,0,0,0,0,0];
guardb = [-0;0;0];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 2, 'dummy', 'names');

loc{4} = location('S4',4, inv, trans, dynamics);



HA = hybridAutomaton(loc);


end