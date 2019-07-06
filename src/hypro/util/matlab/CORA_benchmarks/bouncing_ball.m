function complete = bouncing_ball()

sim = 0;
reacha = 1;

HA = bouncing_ball_ha();
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';
Zdelta = [0.1;0];

% options
Zcenter = [10.1;0];
options.R0 = zonotope([Zcenter,diag(Zdelta)]); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation


options.taylorTerms = 1;
options.zonotopeOrder = 1;
options.polytopeOrder = 1;
options.errorOrder=2;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.originContained = 0;

%set input:
for i = 1:1
    options.timeStepLoc{i} = 0.01;
    options.uLoc{i} = [0;0];
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

% First location
options.startLoc = 1; %initial location
options.finalLoc = 0; %0: no final location
options.tStart = 0; %start time
options.tFinal = 4;

dim = 2;
vis = 1;

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
    options.projectedDimensions = [2 1];
    options.plotType = {'b','m','g'};
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    for i = 1:length(simRes)
       for j = 1:length(simRes{i}.x)
           plot(simRes{i}.x{j}(:,options.projectedDimensions(1)), ...
                simRes{i}.x{j}(:,options.projectedDimensions(2)),'k'); 
       end
    end
%     xlabel('t');
%     ylabel('v');
end


% Reachability ------------------------------------------------------------
if reacha
    tic;
    [HA] = reach(HA,options);
    toc;
    disp(['Time needed for the analysis: ', num2str(toc)]);
    
    % Verification --------------------------------------------------------
    
    %TODO
    
% Visualization -------------------------------------------------------
if vis    
    figure 
    hold on
    options.projectedDimensions = [2 1];

    options.plotType = 'b';
    plot(HA,'reachableSet',options); %plot reachable set
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    xlabel('v');
    ylabel('x');
end
end

complete = 1;