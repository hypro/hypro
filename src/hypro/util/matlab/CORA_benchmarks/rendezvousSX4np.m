function rendezvousSX4np()
% example_linear_reach_ARCH18_rendezvousSX4np - example of linear 
% reachability analysis from the ARCH18 friendly competition 
% (instance of rendevouz example)
%
% Syntax:  
%    example_linear_reach_ARCH18_rendezvousSX4np
%
% Inputs:
%    no
%
% Outputs:
%
% References: 
%   [1] N. Chan et al. "Verifying safety of an autonomous spacecraft 
%       rendezvous mission (Benchmark proposal)"

% Author:       Matthias Althoff
% Written:      20-April-2018
% Last update:  ---
% Last revision:---


%------------- BEGIN CODE --------------

% x_1 = v_x
% x_2 = v_y
% x_3 = s_x 
% x_4 = s_y
% x_5 = t


% Options -----------------------------------------------------------------
sim = 0;
reacha = 1;
vis = 1;


% debugging mode
options.debug = 0;

% initial set
R0 = zonotope([[-900; -400; 0; 0; 0],diag([25;25;0;0;0])]);

% initial set
options.x0=center(R0); % initial state for simulation
options.R0=R0; % initial state for reachability analysis

% other
options.startLoc = 1; % initial location
options.finalLoc = -inf; % no final location
options.tStart=0; % start time
options.tFinal=20; % final time
options.intermediateOrder = 2;
options.originContained = 0;

options.zonotopeOrder=40; % zonotope order
options.polytopeOrder=3; % polytope order
options.taylorTerms=3;
options.reductionTechnique = 'girard';
options.isHyperplaneMap=0;
options.enclosureEnables = [3, 5]; % choose enclosure method(s)
options.filterLength = [5,7];
options.guardIntersect = 'polytope';
options.errorOrder = 2;

% specify hybrid automata
HA = rendezvousSX4np_ha(); % automatically converted from SpaceEx

for i = 1:5
    options.timeStepLoc{i} = 0.01;
    options.uLoc{i} = 0;
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

% Simulation --------------------------------------------------------------

if sim
    N = 50;
    tic;
    for i=1:N
        %set initial state, input
        if i == 1
            %simulate center
            options.x0 = center(options.R0);
        elseif i < 5
            % simulate extreme points
            options.x0 = randPointExtreme(options.R0);
        else
            % simulate random points
            options.x0 = randPoint(options.R0);
        end 

        %simulate hybrid automaton
        HAsim = simulate(HA,options);
        simRes{i} = get(HAsim,'trajectory');
    end
    toc;
    disp(['Time needed for the simulation: ', num2str(toc)]);

    % Visualization -------------------------------------------------------
    figure 
    hold on
    box on
    options.projectedDimensions = [3 4];
    options.plotType = {'b','m','g'};
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    for i = 1:length(simRes)
       for j = 1:length(simRes{i}.x)
           plot(simRes{i}.x{j}(:,options.projectedDimensions(1)), ...
                simRes{i}.x{j}(:,options.projectedDimensions(2)),'k'); 
       end
    end
    xlabel('vx');
    ylabel('vy');
end


% Reachability ------------------------------------------------------------
if reacha
    tic;
    [HA] = reach(HA,options);
    toc;
    disp(['Time needed for the analysis: ', num2str(toc)]);
    
    % Verification --------------------------------------------------------
    
    spacecraft = interval([-0.1;-0.1;0;0;0],[0.1;0.1;0;0;0]);

% feasible velocity region as polytope
C = [0 0 1 0 0;0 0 -1 0 0;0 0 0 1 0;0 0 0 -1 0;0 0 1 1 0;0 0 1 -1 0;0 0 -1 1 0;0 0 -1 -1 0];
d = [3;3;3;3;4.2;4.2;4.2;4.2];

% line-of-sight as polytope
Cl = [-1 0 0 0 0;tan(pi/6) -1 0 0 0;tan(pi/6) 1 0 0 0];
dl = [100;0;0];

% passive mode -> check if the spacecraft was hit
for i = 1:length(Rcont{3})    
    if isIntersecting(interval(Rcont{3}{i}),spacecraft)
       verificationCollision = 0;
       break;
    end
end

% randezvous attempt -> check if spacecraft inside line-of-sight
for i = 2:length(Rcont{2})  

    temp = interval(Cl*Rcont{2}{i})-dl;

    if any(supremum(temp) > 0)
       verificationLOS = 0;
       break;
    end
end

% randezvous attempt -> check if velocity inside feasible region
for i = 1:length(Rcont{2})  

    temp = interval(C*Rcont{2}{i})-d;

    if any(supremum(temp) > 0)
       verificationVelocity = 0;
       break;
    end
end
    
% Visualization -------------------------------------------------------
if vis    
    figure 
    hold on
    options.projectedDimensions = [3 4];

    options.plotType = 'b';
    plot(HA,'reachableSet',options); %plot reachable set
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    xlabel('vx');
    ylabel('vy');
end
end


%------------- END OF CODE --------------