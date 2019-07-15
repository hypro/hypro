function log = bouncing_ball(saveFig,savePath,filename, diff, show, timeStep, tTerms, zOrder, pOrder, strategy)

HA = bouncing_ball_ha();
Zdelta = [0.1;0];


% options
Zcenter = [10.1;0];
options.R0 = zonotope([Zcenter,diag(Zdelta)]); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation

% if diff == 1 || diff == 0
%     options.taylorTerms = 10;
%     options.zonotopeOrder = 20;
%     options.polytopeOrder = 10;
% elseif diff == 2
%     options.taylorTerms = 10;
%     options.zonotopeOrder = 20;
%     options.polytopeOrder = 10;
% else
%     options.taylorTerms = 200;
%     options.zonotopeOrder = 2;
%     options.polytopeOrder = 200;
% end

% First location
options.startLoc = 1; %initial location
options.finalLoc = 0; %0: no final location
options.tStart = 0; %start time
options.tFinal = 4;

options.taylorTerms = tTerms;
options.zonotopeOrder = zOrder;
options.polytopeOrder = pOrder;

options.errorOrder=2;
options.maxProjectionError=0.1;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';
options.originContained = 0;

%set input:
for i = 1:1
    %options.timeStepLoc{i} = 0.01;
    options.timeStepLoc{i} = timeStep;
    options.uLoc{i} = [0;0];
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end



% Reachability ------------------------------------------------------------
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
        
        %maxValue = findSafetyProperties([0 1], Rset)
        
        if diff == 3
            %hard: v <= 10.6138
            spec = [0 1 10.6138];
        elseif diff == 2
            %medium: v <= 10.6569
            spec = [0 1 10.6569];
        else
            %easy: v <= 10.7
            spec = [0 1 10.7];
        end
        
        safe = verifySafetyPropertiesCORA(spec, Rset);
        verificationT = toc;
        time = reachabilityT + verificationT;
    end
    
    log = ['bouncing_ball ', num2str(diff), ' ',...
    num2str(reachabilityT), ' ',  num2str(verificationT), ' ',...
    num2str(time), ' ' num2str(safe), ' ', num2str(strategy)];
    
% Visualization -------------------------------------------------------
if show    
    fig = figure(); 
    hold on
    options.projectedDimensions = [2 1];

    options.plotType = 'b';
    plot(HA,'reachableSet',options); %plot reachable set
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    xlabel('v');
    ylabel('x');
    
    if saveFig
        fname = strcat(filename,'.','png');
        saveas(fig, fullfile(savePath,fname),'png');
    end
end
end