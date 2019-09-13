function log = two_tanks_cora(saveFig,savePath,filename, diff, show, timeStep, tTerms, zOrder, pOrder, strategy)

HA = two_tanks_ha();
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';
Zdelta = [0.5;0];

% options
Zcenter = [2;1];
options.R0 = zonotope([Zcenter,diag(Zdelta)]); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation

options.taylorTerms = tTerms;
options.zonotopeOrder = zOrder;
options.polytopeOrder = pOrder;

options.errorOrder=2;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.originContained = 0;
%options.intersectInvariant =1;

%set input:
for i = 1:4
    options.timeStepLoc{i} = timeStep;
    %options.uLoc{i} = interval([-0.01;-0.01],[0.01;0.01]);
    options.uLoc{i} = interval([0;0],[0;0]);
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
        Rset = get(HA, 'reachableSet');
        Rset = Rset.OT;
        
        maxValue = findSafetyProperties([0 -1], Rset)
        
        if diff == 1
            %easy: x2 >= -0.7
            spec = [0 -1 0.7];
        elseif diff == 2
            %medium: x2 >= -0.7
            spec = [0 -1 0.7];
        elseif diff == 3
            %hard: x2 >= -0.5068
            spec = [0 -1 0.5068];
        elseif diff == 4
            %spec_ x1 >= -1
            spec= [-1 0 1];
        end

        safe = verifySafetyPropertiesCORA(spec, Rset);
        verificationT = toc;
        time = reachabilityT + verificationT;
    end
log = ['two_tanks ', num2str(diff), ' ',...
num2str(reachabilityT), ' ',  num2str(verificationT), ' ',...
num2str(time), ' ' num2str(safe), ' ' num2str(strategy)];

% Visualization -------------------------------------------------------
if show    
    fig = figure(); 
    hold on
    options.projectedDimensions = [1 2];

    options.plotType = 'b';
    plot(HA,'reachableSet',options); %plot reachable set
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    set(gca,'FontSize',15);
    if diff == 1
        y = [-0.7;-0.7;-1;-1];
        x = [2.5;-1.5;-1.5;2.5];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    elseif diff == 2
        y = [-0.7;-0.7;-1;-1];
        x = [2.5;-1;-1;2.5];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    elseif diff ==  3
        y = [-0.5068;-0.5068;-1.5;-1.5];
        x = [2.5;-1.5;-1.5;2.5];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    elseif diff == 4
        y = [1;1;-1.5;-1.5];
        x = [-1;-1.5;-1.5;-1];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    end
    xlabel('x1');
    ylabel('x2');
    if saveFig
        fname = strcat(filename,'.','png');
        saveas(fig, fullfile(savePath,fname),'png');
    end
end
end