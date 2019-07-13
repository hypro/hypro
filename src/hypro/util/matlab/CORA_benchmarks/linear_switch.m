function log = linear_switch(saveFig,savePath,filename, diff, plot)

HA = linear_switch_ha();
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';
Zdelta = 1e-4*ones(5,1);

% options
Zcenter = [3.1;4;0;0;0];
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
    options.zonotopeOrder = 5;
    options.polytopeOrder = 1;
elseif diff == 1
    % easy
    options.taylorTerms = 1;
    options.zonotopeOrder = 5;
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
for i = 1:5
    options.timeStepLoc{i} = 0.001;
    options.uLoc{i} = 0;
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

% First location
options.startLoc = 1; %initial location
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
            %easy: x3 <= 1.5
            spec = [0 0 1 0 0 1.5];
        elseif diff == 2
            %medium: x3 <= 1.4945
            spec = [0 0 1 0 0 1.4945];
        else
            %hard: x3 <= 1.489
            spec = [0 0 1 0 0 1.489];
        end
        safe = verifySafetyPropertiesCORA(spec, Rset);
        verificationT = toc;
        time = reachabilityT + verificationT;
    end
log = ['switching_system ', num2str(diff), ' ',...
num2str(reachabilityT), ' ',  num2str(verificationT), ' ',...
num2str(time), ' ' num2str(safe)];

% Visualization -------------------------------------------------------
if plot   
    fig = figure(); 
    hold on
    options.projectedDimensions = [1 3];

    options.plotType = 'b';
    plot(HA,'reachableSet',options); %plot reachable set
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    xlabel('x1');
    ylabel('x3');
    if saveFig
        fname = strcat(filename,'.','png');
        saveas(fig, fullfile(savePath,fname),'png');
    end
end

end