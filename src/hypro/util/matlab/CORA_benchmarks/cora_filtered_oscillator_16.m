function log = cora_filtered_oscillator_16(saveFig,savePath,filename, diff, show, timeStep, tTerms, zOrder, pOrder, strategy)

HA = filtered_oscillator_16_ha();
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';
Zdelta = [0.05;0.1;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0];

% options
Zcenter = [0.25;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0];
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
    options.uLoc{i} = 0;
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

% First location
options.startLoc = 3; %initial location
options.finalLoc = 0; %0: no final location
options.tStart = 0; %start time
options.tFinal = 4;

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
        
        if diff == 1
            %easy: y <= 0.5
            spec = [0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0.5];
        elseif diff == 2
            %medium: y <= 0.4819
            spec = [0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0.4819];
        else
            %hard: y <= 0.4637
            spec = [0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0.4637];
        end
        safe = verifySafetyPropertiesCORA(spec, Rset);
        verificationT = toc;
        time = reachabilityT + verificationT;
    end
log = ['filtered_oscillator_16 ', num2str(diff), ' ',...
num2str(reachabilityT), ' ',  num2str(verificationT), ' ',...
num2str(time), ' ' num2str(safe), ' ' num2str(strategy)];
    
% Visualization -------------------------------------------------------
if show    
    fig = figure(); 
    hold on
    options.projectedDimensions = [1 6];

    options.plotType = 'b';
    plot(HA,'reachableSet',options); %plot reachable set
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    set(gca,'FontSize',15);
    if diff == 1
        x = [0.8;0.8;0.5;0.5];
        y = [1;-1;-1;1];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    elseif diff == 2
        x = [0.8;0.8;0.4946;0.4946];
        y = [1;-1;-1;1];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    elseif diff == 3
        x = [0.8;0.8;0.4892;0.4892];
        y = [1;-1;-1;1];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    end
    xlabel('x');
    ylabel('f8x1');
    if saveFig
        fname = strcat(filename,'.','png');
        saveas(fig, fullfile(savePath,fname),'png');
    end
end
end