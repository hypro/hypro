function log = rod_reactor_cora(saveFig,savePath,filename, diff, show, timeStep, tTerms, zOrder, pOrder, strategy)

HA = rod_reactor_HA();
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';

% options
Zcenter = interval([510;20;20],[520;20;20]);
options.R0 = zonotope(Zcenter); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation

% if diff == 3
%     %hard:
%     options.taylorTerms = 100;
%     options.zonotopeOrder = 200;
%     options.polytopeOrder = 100;
% elseif diff == 2
%     %medium:
%     options.taylorTerms = 1;
%     options.zonotopeOrder = 1;
%     options.polytopeOrder = 1;
% elseif diff == 1
%     % easy
%     options.taylorTerms = 1;
%     options.zonotopeOrder = 1;
%     options.polytopeOrder = 1;
% else
%     options.taylorTerms = 1;
%     options.zonotopeOrder = 1;
%     options.polytopeOrder = 1;
% end

options.taylorTerms = tTerms;
options.zonotopeOrder = zOrder;
options.polytopeOrder = pOrder;
options.errorOrder=0;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.originContained = 0;

%set input:
for i = 1:3
%     options.timeStepLoc{i} = 0.01;
    options.timeStepLoc{i} = timeStep;
    options.uLoc{i} = 0;
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

% First location
options.startLoc = 3; %initial location
options.finalLoc = 0; %0: no final location
options.tStart = 0; %start time
options.tFinal = 12;

    tic;
    [HA] = reach(HA,options);
    reachabilityT = toc;
    safe = 0;
    verificationT = 0;
    time = 0;
    % Verification --------------------------------------------------------
    if diff ~= 0
        tic;
        Rset = get(HA, 'reachableSet');
        Rset = Rset.OT;
        
        maxValue = findSafetyProperties([0 -1 0; 0 0 -1], Rset);
        
        if diff == 1
            %easy: c1 >= 35 & c2 >= 35
            spec = [0 -1 0 -35; 0 0 -1 -35];
        elseif diff == 2
            %medium: c1 >= 34.93 & c2 >= 34.93
            spec = [0 -1 0 -34.93; 0 0 -1 -34.93];
        else
            %hard: c1 >= 34.861 & c2 >= 34.861
            spec = [0 -1 0 -34.861; 0 0 -1 -34.861];
        end

        safe = verifySafetyPropertiesCORA(spec, Rset);
        verificationT = toc;
        time = reachabilityT + verificationT;
    end
log = ['rod_reactor ', num2str(diff), ' ',...
num2str(reachabilityT), ' ',  num2str(verificationT), ' ',...
num2str(time), ' ' num2str(safe), ' ' num2str(strategy), ' ', num2str(maxValue(1)),...
    ' ', num2str(maxValue(2))];

% Visualization -------------------------------------------------------
if show    
    fig = figure(); 
    hold on
    options.projectedDimensions = [1 3];

    options.plotType = 'b';
    plot(HA,'reachableSet',options); %plot reachable set
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    xlabel('x');
    ylabel('c2');
    if saveFig
        fname = strcat(filename,'.','png');
        saveas(fig, fullfile(savePath,fname),'png');
    end
end
end