function HA = filtered_oscillator_8_ha(~)
%------------------Component system.osc_w_4th_order_1----------------------
% vars: x,y,f4a_x1,f4a_x2,f4a_x3,f8_x1,f4b_x1,f4b_x2,f4b_x3,z
%-----------------State loc1---------------------

%% equation:
dynA = [-2 0 0 0 0 0 0 0 0 0;...
         0 -1 0 0 0 0 0 0 0 0;...
         5  0 -5 0 0 0 0 0 0 0;...
         0 0 5 -5 0 0 0 0 0 0;...
         0 0 0 5 -5 0 0 0 0 0;...
         0 0 0 0 5 -5 0 0 0 0;...
         0 0 0 0 0 5 -5 0 0 0;...
         0 0 0 0 0 0 5 -5 0 0;...
         0 0 0 0 0 0 0  5 -5 0;...
         0 0 0 0 0 0 0 0 5 -5];
dynB = zeros(10,1);
dync = [1.4;-0.7;0;0;0;0;0;0;0;0];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   x <= 0 & y+0.714286*x >= 0 
invA = [1,0,0,0,0,0,0,0,0,0;-0.714286,-1,0,0,0,0,0,0,0,0];
invb = [0;0];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%   dummy
resetA = eye(10);
resetb = zeros(10,1);
reset = struct('A', resetA, 'b', resetb);

%% equation:
%    x == 0 & 0.714286*x+y >= 0 
guardA = [1 0 0 0 0 0 0 0 0 0; -1 0 0 0 0 0 0 0 0 0; -0.714286 -1 0 0 0 0 0 0 0 0];
guardb = [0;0;0];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 3, 'dummy', 'names');

loc{1} = location('S1',1, inv, trans, dynamics);

%-----------------State loc2---------------------

%% equation:
dynA = [-2 0 0 0 0 0 0 0 0 0;...
         0 -1 0 0 0 0 0 0 0 0;...
         5  0 -5 0 0 0 0 0 0 0;...
         0 0 5 -5 0 0 0 0 0 0;...
         0 0 0 5 -5 0 0 0 0 0;...
         0 0 0 0 5 -5 0 0 0 0;...
         0 0 0 0 0 5 -5 0 0 0;...
         0 0 0 0 0 0 5 -5 0 0;...
         0 0 0 0 0 0 0  5 -5 0;...
         0 0 0 0 0 0 0 0 5 -5];
dynB = zeros(10,1);
dync = [-1.4;0.7;0;0;0;0;0;0;0;0];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   x <= 0 & y+0.714286*x <= 0 
invA = [1,0,0,0,0,0,0,0,0,0;0.7142869,1,0,0,0,0,0,0,0,0];
invb = [0;0];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
resetA = eye(10);
resetb = zeros(10,1);
reset = struct('A', resetA, 'b', resetb);

%% equation:
%    y+0.714286*x == 0 & x <= 0 
guardA = [1,0,0,0,0,0,0,0,0,0;-0.714286,-1,0,0,0,0,0,0,0,0;0.714286,1,0,0,0,0,0,0,0,0];
guardb = [0;0;0];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 1, 'dummy', 'names');

loc{2} = location('S2',2, inv, trans, dynamics);



%-----------------State loc3---------------------

%% equation:
dynA = [-2 0 0 0 0 0 0 0 0 0;...
         0 -1 0 0 0 0 0 0 0 0;...
         5  0 -5 0 0 0 0 0 0 0;...
         0 0 5 -5 0 0 0 0 0 0;...
         0 0 0 5 -5 0 0 0 0 0;...
         0 0 0 0 5 -5 0 0 0 0;...
         0 0 0 0 0 5 -5 0 0 0;...
         0 0 0 0 0 0 5 -5 0 0;...
         0 0 0 0 0 0 0  5 -5 0;...
         0 0 0 0 0 0 0 0 5 -5];
dynB = zeros(10,1);
dync = [1.4;-0.7;0;0;0;0;0;0;0;0];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   x >= 0 & y+0.714286*x >= 0 
invA = [-1,0,0,0,0,0,0,0,0,0;-0.714286,-1,0,0,0,0,0,0,0,0];
invb = [0;0];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
resetA = eye(10);
resetb = zeros(10,1);
reset = struct('A', resetA, 'b', resetb);

%% equation:
%    y+0.714286*x == 0 & x >= 0 
guardA = [-1 0 0 0 0 0 0 0 0 0; -0.714286 -1 0 0 0 0 0 0 0 0; 0.714286 1 0 0 0 0 0 0 0 0];
guardb = [0;0;0];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 4, 'dummy', 'names');

loc{3} = location('S3',3, inv, trans, dynamics);



%-----------------State loc4---------------------

%% equation:
dynA = [-2 0 0 0 0 0 0 0 0 0;...
         0 -1 0 0 0 0 0 0 0 0;...
         5  0 -5 0 0 0 0 0 0 0;...
         0 0 5 -5 0 0 0 0 0 0;...
         0 0 0 5 -5 0 0 0 0 0;...
         0 0 0 0 5 -5 0 0 0 0;...
         0 0 0 0 0 5 -5 0 0 0;...
         0 0 0 0 0 0 5 -5 0 0;...
         0 0 0 0 0 0 0  5 -5 0;...
         0 0 0 0 0 0 0 0 5 -5];
dynB = zeros(10,1);
dync = [-1.4;0.7;0;0;0;0;0;0;0;0];
dynamics = linearSys('linearSys', dynA, dynB, dync);

%% equation:
%   x >= 0 & y+0.714286*x <= 0 
invA = [-1 0 0 0 0 0 0 0 0 0; 0.714286 1 0 0 0 0 0 0 0 0];
invb = [0;0];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
resetA = eye(10);
resetb = zeros(10,1);
reset = struct('A', resetA, 'b', resetb);

%% equation:
%    x == 0 & 0.714286*x+y <= 0 
guardA = [-1 0 0 0 0 0 0 0 0 0; 1 0 0 0 0 0 0 0 0 0; 0.714286 1 0 0 0 0 0 0 0 0];
guardb = [-0;0;0];
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 2, 'dummy', 'names');

loc{4} = location('S4',4, inv, trans, dynamics);



HA = hybridAutomaton(loc);


end