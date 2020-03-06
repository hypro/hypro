function leaking_tanks_zono_cora()

%------------------------------t1---------------------------------

tH = 3;

% equation dynamics:
%    h1' = 1.5 h2' = -1.5 t' = 1 gc' = 1
dynA = [0 0 0 0; 0 0 0 0; 0 0 0 0; 0 0 0 0];
dynB = zeros(4,1);
dync = [1.5; -1.5; 1;1];
dynamics = linearSys('linearSys', dynA, dynB, dync);

% equation invariant:
%   0 <= h1 <= 10 & 0 <= h2 & gc <= tH
invA = [-1 0 0 0; 1 0 0 0; 0 -1 0 0; 0 0 0 1];
invb = [0;10;0;tH];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

% equation guard (t1 -> t2):
%   t >= 0
guardA = [0 0 -1 0];
guardb = 0;
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

% dummy reset
%   t := 0
resetA = [1 0 0 0; 0 1 0 0; 0 0 0 0; 0 0 0 1];
resetb = [0;0;0;0];
reset = struct('A', resetA, 'b', resetb);
trans = {};
trans{1} = transition(guard, reset, 2, 't1', 't2');

loc{1} = location('t1',1, inv, trans, dynamics);

%------------------------------t2---------------------------------

% equation dynamics:
%    h1' = -2.5 h2' = 2.5 t' = 1 gc' = 1
dynA = [0 0 0 0; 0 0 0 0; 0 0 0 0; 0 0 0 0];
dynB = zeros(4,1);
dync = [-2.5; 2.5; 1;1];
dynamics = linearSys('linearSys', dynA, dynB, dync);

% equation invariant:
%   0 <= h1 & 0 <= h2 & gc <= tH
invA = [-1 0 0 0; 0 1 0 0; 0 -1 0 0; 0 0 0 1];
invb = [0;10;0;tH];
invOpt = struct('A', invA, 'b', invb);
inv = mptPolytope(invOpt);

% equation guard (t2 -> t1):
%   t >= 0
guardA = [0 0 -1 0];
guardb = 0;
guardOpt = struct('A', guardA, 'b', guardb);
guard = mptPolytope(guardOpt);

% dummy reset
%   t := 0
resetA = [1 0 0 0; 0 1 0 0; 0 0 0 0; 0 0 0 1];
resetb = [0;0;0;0];
reset = struct('A', resetA, 'b', resetb);
trans = {};
trans{1} = transition(guard, reset, 1, 't2', 't1');

loc{2} = location('t2',2, inv, trans, dynamics);

HA = hybridAutomaton(loc);

sim = 0;
reacha = 1;
vis = 1;

options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';
Zdelta = 0.01 * ones(4,1);

% options
Zcenter = [5;5;0;0];
options.R0 = zonotope([Zcenter,diag(Zdelta)]); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation

options.taylorTerms = 10;
options.zonotopeOrder = 20;
options.polytopeOrder = 10;
options.errorOrder=1e-12;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.originContained = 0;

%set input:
for i = 1:2
    options.timeStepLoc{i} = 0.1;
    options.uLoc{i} = 0;
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

% First location
options.startLoc = 1; %initial location
options.finalLoc = 0; %0: no final location
options.tStart = 0; %start time
options.tFinal = 3;

% Simulation --------------------------------------------------------------

if sim
    N = 1;
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
    options.projectedDimensions = [3 1];
    options.plotType = {'b','m','g'};
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    for i = 1:length(simRes)
       for j = 1:length(simRes{i}.x)
           plot(simRes{i}.x{j}(:,options.projectedDimensions(1)), ...
                simRes{i}.x{j}(:,options.projectedDimensions(2)),'k'); 
       end
    end
    xlabel('t');
    ylabel('h1');
    
    figure 
    hold on
    box on
    options.projectedDimensions = [3 1];
    options.plotType = {'b','m','g'};
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set

    for i = 1:length(simRes)
       for j = 1:length(simRes{i}.x)
           plot(simRes{i}.x{j}(:,options.projectedDimensions(1)), ...
                simRes{i}.x{j}(:,options.projectedDimensions(2)),'k'); 
       end
    end
    xlabel('t');
    ylabel('h1');
end


% Reachability ------------------------------------------------------------
if reacha
    tic;
    [HA] = reach(HA,options);
    toc;
    disp(['Time needed for the analysis: ', num2str(toc)]);
    
% Visualization -------------------------------------------------------
if vis    
    figure 
    hold on
    options.projectedDimensions = [3 1];

    options.plotType = 'b';
    plot(HA,'reachableSet',options); %plot reachable set
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    xlabel('t');
    ylabel('v');
    
    figure 
    hold on
    options.projectedDimensions = [3 2];

    options.plotType = 'b';
    plot(HA,'reachableSet',options); %plot reachable set
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    xlabel('t');
    ylabel('d');
end
end
end