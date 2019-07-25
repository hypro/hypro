function log = cora_linear_switching_system(saveFig,savePath,filename, diff, show,timeStep, tTerms, zOrder, pOrder,strategy)

HA = linear_switch_ha();
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';
Zdelta = 1e-4*ones(5,1);

% options
Zcenter = [3.1;4;0;0;0];
options.R0 = zonotope([Zcenter,diag(Zdelta)]); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation

options.taylorTerms = tTerms;
options.zonotopeOrder = zOrder;
options.polytopeOrder = pOrder;

options.errorOrder=2;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.originContained = 0;

%set input:
for i = 1:5
%     options.timeStepLoc{i} = 0.001;
    options.timeStepLoc{i} = timeStep;
    options.uLoc{i} = 0;
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

% First location
options.startLoc = 1; %initial location
options.finalLoc = 0; %0: no final location
options.tStart = 0; %start time
options.tFinal = 1;

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
        
        %maxValue = findSafetyProperties([0 0 1 0 0],Rset);
        
        if diff == 1
            %easy: x3 <= 1.5
            spec = [0 0 1 0 0 1.5];
        elseif diff == 2
            %medium: x3 <= 1.4942
            spec = [0 0 1 0 0 1.4942];
        else
            %hard: x3 <= 1.4884
            spec = [0 0 1 0 0 1.4884];
        end
        safe = verifySafetyPropertiesCORA(spec, Rset);
        verificationT = toc;
        time = reachabilityT + verificationT;
    end
log = ['switching_system ', num2str(diff), ' ',...
num2str(reachabilityT), ' ',  num2str(verificationT), ' ',...
num2str(time), ' ' num2str(safe), ' ', num2str(strategy)];

% Visualization -------------------------------------------------------
if show   
    fig = figure(); 
    hold on
    options.projectedDimensions = [1 3];

    options.plotType = 'b';
    plot(HA,'reachableSet',options); %plot reachable set
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    if diff == 0
        y = [2;2;1.5;1.5];
        x = [4;-2;-2;4];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    elseif diff == 1
        y = [2;2;1.4942;1.4942];
        x = [4;-2;-2;4];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    else
        y = [2;2;1.4884;1.4884];
        x = [4;-2;-2;4];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    end
    xlabel('x1');
    ylabel('x3');
    if saveFig
        fname = strcat(filename,'.','png');
        saveas(fig, fullfile(savePath,fname),'png');
    end
end

end