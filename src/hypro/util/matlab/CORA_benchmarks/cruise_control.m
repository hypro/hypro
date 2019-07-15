function log = cruise_control(saveFig,savePath,filename, diff, show, timeStep, tTerms, zOrder, pOrder, strategy)

% Load model
HA = cruise_control_ha();
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';

% options
% v = [15, 40] x = [0, 0]  t =[0, 2.5]
Zcenter = interval([15;0;0],[40;0.0001;2.5]);
options.R0 = zonotope(Zcenter); %initial state for reachability analysis
% options.x0 = center(options.R0); %initial state for simulation

% if diff == 1 || diff == 0
%     options.taylorTerms = 10;
%     options.zonotopeOrder = 20;
%     options.polytopeOrder = 10;
% elseif diff == 2
%     options.taylorTerms = 10;
%     options.zonotopeOrder = 20;
%     options.polytopeOrder = 10;
% else
%     options.taylorTerms = 100;
%     options.zonotopeOrder = 200;
%     options.polytopeOrder = 100;
% end

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
options.tFinal = 10;

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
        
        maxValue =findSafetyProperties([-1 0 0], Rset);

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
    num2str(time), ' ' num2str(safe), ' ' num2str(strategy),...
    ' ' num2str(maxValue)];

if show 
    fig = figure(); 
    hold on
    options.projectedDimensions = [3 1];
    options.plotType = 'b';
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    plot(HA,'reachableSet',options); %plot reachable set
    xlabel('t');
    ylabel('v');
    if saveFig
        fname = strcat(filename,'.','png');
        saveas(fig, fullfile(savePath,fname),'png');
    end
end


end