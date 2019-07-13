function log = two_tanks(saveFig,savePath,filename, diff, plot)

HA = two_tanks_ha();
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';
Zdelta = [0.5;0];

% options
Zcenter = [2;1];
options.R0 = zonotope([Zcenter,diag(Zdelta)]); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation

if diff == 3
    %hard:
    options.taylorTerms = 100;
    options.zonotopeOrder = 200;
    options.polytopeOrder = 100;
elseif diff == 2
    %medium:
    options.taylorTerms = 1;
    options.zonotopeOrder = 1;
    options.polytopeOrder = 1;
elseif diff == 1
    % easy
    options.taylorTerms = 1;
    options.zonotopeOrder = 1;
    options.polytopeOrder = 1;
else
    options.taylorTerms = 10;
    options.zonotopeOrder = 20;
    options.polytopeOrder = 10;
end
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

    tic;
    [HA] = reach(HA,options);
    reachabilityT = toc;
    safe = 0;
    verificationT = 0;
    time = 0;
    % Verification --------------------------------------------------------
    if diff ~= 0
        tic;
        Rset = get(HA, 'continuousReachableSet');
        Rset = Rset.OT;
        if diff == 1
            %easy: x2 >= -0.7
            spec = [0 -1 0.7];
        elseif diff == 2
            %medium: x2 >= -0.7
            spec = [0 -1 0.7];
        else
            %hard: x2 >= -0.7
            spec = [0 -1 0.7];
        end

        safe = verifySafetyPropertiesCORA(spec, Rset);
        verificationT = toc;
        time = reachabilityT + verificationT;
    end
log = ['two_tanks ', num2str(diff), ' ',...
num2str(reachabilityT), ' ',  num2str(verificationT), ' ',...
num2str(time), ' ' num2str(safe)];

% Visualization -------------------------------------------------------
if plot    
    fig = figure(); 
    hold on
    options.projectedDimensions = [1 2];

    options.plotType = 'b';
    plot(HA,'reachableSet',options); %plot reachable set
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    xlabel('x1');
    ylabel('x2');
    if saveFig
        fname = strcat(filename,'.','png');
        saveas(fig, fullfile(savePath,fname),'png');
    end
end
end