function complete = two_tanks()

sim = 0;
reacha = 1;

% Load model
HA = two_tanks_ha();
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';
Zdelta = [0.5;0];

% options
Zcenter = [2;1];
options.R0 = zonotope([Zcenter,diag(Zdelta)]); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation


options.taylorTerms = 10;
options.zonotopeOrder = 20;
options.polytopeOrder = 10;
options.errorOrder=2;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.originContained = 0;

%set input:
for i = 1:4
    options.timeStepLoc{i} = 0.5;
    options.uLoc{i} = 0;
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

% First location
options.startLoc = 3; %initial location
options.finalLoc = 0; %0: no final location
options.tStart = 0; %start time
options.tFinal = 2;

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
    options.projectedDimensions = [1 2];
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
    reachabilityT = toc;
    disp(['Time needed for the analysis: ', num2str(reachabilityT)]);
    
    % Verification --------------------------------------------------------
    Rset = get(HA, 'continuousReachableSet');
    Rset = Rset.OT;
    
    %easy: x2 >= -0.7
    spec = [0 -1 0.7];
    %medium: x2 >= -0.7
    spec = [0 -1 0.7];
    %hard: x2 >= -0.7
    spec = [0 -1 0.7];
    
    tic;
    safe = verifySafetyPropertiesCORA(spec, Rset);
    verificationT = toc;
    
    if safe
        disp('Verification result: SAFE');
    end
    
    disp(['Time needed for verification: ', num2str(verificationT)]);
    
    time = reachabilityT + verificationT;
    disp(['Time needed for reachability analysis + verification: ', num2str(time)]);
    
% Visualization -------------------------------------------------------
if vis    
    figure 
    hold on
    options.projectedDimensions = [1 2];

    options.plotType = 'b';
    plot(HA,'reachableSet',options); %plot reachable set
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
%     xlabel('t');
%     ylabel('v');
end
end

complete = 1;