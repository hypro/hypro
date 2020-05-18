function HA = vehicle_platoon_ha(~)

%-----------------------Component system.switch_1--------------------------
% vars = [e1, e1prime, a1, e2, e2prime, a2, e3, e3prime, a3, t]

%-------------------------------State l1-----------------------------------

%% equation:
% e1' = e1prime
% e1prime' = -a1
% a1' = 1.605*e1 + 4.868*e1prime - 3.5754*a1 - 0.8198*e2 + 0.427*e2prime - 0.045*a2 - 0.1942*e3 + 0.3626*e3prime - 0.0946*a3
% e2' = e2prime
% e2prime' = a1 - a2
% a2' = 0.8718*e1 + 3.814*e1prime - 0.0754*a1 + 1.1936*e2 + 3.6258*e2prime - 3.2396*a2 - 0.595*e3 + 0.1294*e3prime - 0.0796*a3
% e3' = e3prime
% e3prime' = a2 - a3
% a3' = 0.7132*e1 + 3.573*e1prime - 0.0964*a1 + 0.8472*e2 + 3.2568*e2prime - 0.0876*a2 + 1.2726*e3 + 3.072*e3prime - 3.1356*a3
% t' = 1
Ac = [...
        0    1.0000         0         0         0         0         0         0         0 0;...
        0         0   -1.0000         0         0         0         0         0         0 0;...
        1.6050    4.8680   -3.5754   -0.8198    0.4270   -0.0450   -0.1942    0.3626   -0.0946 0;...
        0         0         0         0    1.0000         0         0         0         0 0;...
        0         0    1.0000         0         0   -1.0000         0         0         0 0;...
        0.8718    3.8140   -0.0754    1.1936    3.6258   -3.2396   -0.5950    0.1294   -0.0796 0;...
        0         0         0         0         0         0         0    1.0000         0 0;...
        0         0         0         0         0    1.0000         0         0   -1.0000 0;...
        0.7132    3.5730   -0.0964    0.8472    3.2568   -0.0876    1.2726    3.0720   -3.1356 0;...
        0         0         0         0         0          0        0         0          0 0]; 

An = [...
        0    1.0000         0         0         0         0         0         0         0 0;...
        0         0   -1.0000         0         0         0         0         0         0 0;...
        1.6050    4.8680   -3.5754         0         0         0         0         0         0 0;...
        0         0         0         0    1.0000         0         0         0         0 0;...
        0         0    1.0000         0         0   -1.0000         0         0         0 0;...
        0         0         0    1.1936    3.6258   -3.2396         0         0         0 0;...
        0         0         0         0         0         0         0    1.0000         0 0;...
        0         0         0         0         0    1.0000         0         0   -1.0000 0;...
        0.7132    3.5730   -0.0964    0.8472    3.2568   -0.0876    1.2726    3.0720   -3.1356 0;...
        0         0         0         0         0          0        0         0          0 0]; 
    
dynB = [0;0;0;0;0;0;0;0;0;0];
dync = [0;0;0;0;0;0;0;0;0;1];
dynamics = linearSys('linearSys', Ac, dynB,dync);

%% equation:
%   t <= 2
invA = [0 0 0 0 0 0 0 0 0 1];
invb = 2;
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%   
resetA = eye(10);
resetA(10,10) = 0;
resetb = zeros(10,1);
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   t >= 2
guardA = [0 0 0 0 0 0 0 0 0 -1];
guardb = -2;
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 2, 'dummy', 'names');

loc{1} = location('S1',1, inv, trans, dynamics);


%-------------------------------State ql2-----------------------------------

%% equation:
% e1' = e1prime
% e1prime' = -a1
% a1' = 1.605*e1 + 4.868*e1prime - 3.5754*a1
% e2' = e2prime
% e2prime' = a1 - a2
% a2' = 1.1936*e2 + 3.6258*e2prime - 3.2396*a2
% e3' = e3prime
% e3prime' = a2 - a3
% a3' = 0.7132*e1 + 3.573*e1prime - 0.0964*a1 + 0.8472*e2 + 3.2568*e2prime - 0.0876*a2 + 1.2726*e3 + 3.072*e3prime - 3.1356*a3
% t' = 1

dynB = [0;0;0;0;0;0;0;0;0;0];
dynamics = linearSys('linearSys', An, dynB,dync);

%% equation:
%   t <= 2
invA = [0 0 0 0 0 0 0 0 0 1];
invb = 2;
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

trans = {};
%% equation:
%   
resetA = eye(10);
resetA(10,10) = 0;
resetb = zeros(10,1);
reset = struct('A', resetA, 'b', resetb);

%% equation:
%   t >= 2
guardA = [0 0 0 0 0 0 0 0 0 -1];
guardb = -2;
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

trans{1} = transition(guard, reset, 1, 'dummy', 'names');


loc{2} = location('S2',2, inv, trans, dynamics);

HA = hybridAutomaton(loc);

end