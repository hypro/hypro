function log = cora_cruise_control(saveFig,savePath,filename, diff, show, timeStep, tTerms, zOrder, pOrder, strategy)


sim = 1;

% Load model
HA = cora_cruise_control_ha();
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';

% options
% v = [15, 40] x = [0, 0]  t =[0, 2.5]
Zcenter = interval([15;0;0],[40;0;2.5]);
options.R0 = zonotope(Zcenter); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation

options.taylorTerms = tTerms;
options.zonotopeOrder = zOrder;
options.polytopeOrder = pOrder;

options.errorOrder=1e-12;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.originContained = 0;

%set input:
for i = 1:6
    options.timeStepLoc{i} = timeStep;
    options.uLoc{i} = [0;0;0];
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

% First location
options.startLoc = 1; %initial location
options.finalLoc = 0; %0: no final location
options.tStart = 0; %start time
options.tFinal = 100;

% Simulation --------------------------------------------------------------

if sim
    N = 10;
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
    options.projectedDimensions = [1 3];
    options.plotType = {'b','m','g'};
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    for i = 1:length(simRes)
       for j = 1:length(simRes{i}.x)
           plot(simRes{i}.x{j}(:,options.projectedDimensions(1)), ...
                simRes{i}.x{j}(:,options.projectedDimensions(2)),'k'); 
       end
    end
    %axis([-4 12 0 160]);
    xlabel('v');
    ylabel('t');
end


% Reachability ------------------------------------------------------------
    tic;
    [HA] = reach(HA,options);
    reachabilityT = toc;
    safe = 0;
    verificationT=0;
    time = 0;
    % Verification --------------------------------------------------------
    if diff ~= 0
        tic;
        Rset = get(HA, 'reachableSet');
        Rset = Rset.OT;
        
%         maxValue =findSafetyProperties([-1 0 0], Rset);

        if diff == 3
            %hard: v >= -2
            spec = [-1 0 0 2];
        elseif diff == 2
            %medium: v >= -2
            spec = [-1 0 0 2];
        else
            %easy: v >= -2
            spec = [-1 0 0 2];
        end
        
        safe = verifySafetyPropertiesCORA(spec, Rset);
        verificationT = toc;
        time = reachabilityT + verificationT;
    end
    
    log = ['cruise_control ', num2str(diff), ' ',...
num2str(reachabilityT), ' ',  num2str(verificationT), ' ',...
num2str(time), ' ' num2str(safe), ' ' num2str(strategy)];

if show 
    fig = figure(); 
    hold on
    options.projectedDimensions = [1 2];
    options.plotType = 'b';
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    plot(HA,'reachableSet',options); %plot reachable set
    if diff == 1
        x = [20;-10;-10;20];
        y = [-2;-2;-20;-20];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    elseif diff == 2
        x = [20;-10;-10;20];
        y = [-2;-2;-20;-20];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    elseif diff == 3
        x = [20;-10;-10;20];
        y = [-2;-2;-20;-20];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    end
    xlabel('v');
    ylabel('x');
    if saveFig
        fname = strcat(filename,'.','png');
        saveas(fig, fullfile(savePath,fname),'png');
    end
end


end