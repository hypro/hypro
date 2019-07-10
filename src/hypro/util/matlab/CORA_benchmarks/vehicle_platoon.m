function complete = vehicle_platoon()

sim = 0;
reacha = 1;
diff = 3;

% Load model
HA = vehicle_platoon_ha();
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';
Zdelta = [0.1*ones(9,1);0];

% options
Zcenter = ones(10,1);
options.R0 = zonotope([Zcenter,diag(Zdelta)]); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation

if diff == 3
    %hard:
    options.taylorTerms = 3;
    options.zonotopeOrder = 3;
    options.polytopeOrder = 1;
elseif diff == 2
    %medium:
    options.taylorTerms = 1;
    options.zonotopeOrder = 3;
    options.polytopeOrder = 1;
elseif diff == 1
    % easy
    options.taylorTerms = 1;
    options.zonotopeOrder = 3;
    options.polytopeOrder = 1;
else
    options.taylorTerms = 1;
    options.zonotopeOrder = 1;
    options.polytopeOrder = 1;
end
options.errorOrder=2;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.originContained = 0;

%set input:
for i = 1:2
    options.timeStepLoc{i} = 0.02;
    options.uLoc{i} = 0;
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

% First location
options.startLoc = 1; %initial location
options.finalLoc = 0; %0: no final location
options.tStart = 0; %start time
options.tFinal = 12;

dim = 10;
vis = 0;

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
    if diff ~= 0
        Rset = get(HA, 'continuousReachableSet');
        Rset = Rset.OT;
        
        if diff == 1
            %easy: e1 <= 1.7
            spec = [1 0 0 0 0 0 0 0 0 0 1.7];
        elseif diff == 2
            %medium: e1 <= 1.671
            spec = [1 0 0 0 0 0 0 0 0 0 1.671];
        else
            %hard: e1 <= 1.642
            spec = [1 0 0 0 0 0 0 0 0 0 1.642];
        end

        tic;
        safe = verifySafetyPropertiesCORA(spec, Rset);
        verificationT = toc;

        if safe
            disp('Verification result: SAFE');
        end

        disp(['Time needed for verification: ', num2str(verificationT)]);

        time = reachabilityT + verificationT;
        disp(['Time needed for reachability analysis + verification: ', num2str(time)]);
    end
% Visualization -------------------------------------------------------
if vis    
    figure 
    hold on
    options.projectedDimensions = [4 7];

    options.plotType = 'b';
    plot(HA,'reachableSet',options); %plot reachable set
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    xlabel('e2');
    ylabel('e7');
end
end

complete = 1;