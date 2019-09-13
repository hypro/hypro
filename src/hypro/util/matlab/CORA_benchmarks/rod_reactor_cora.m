function log = rod_reactor_cora(saveFig,savePath,filename, diff, show, timeStep, tTerms, zOrder, pOrder, strategy)

HA = rod_reactor_HA_cora();
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';

% options
Zcenter = interval([510;20;20],[520;20;20]);
options.R0 = zonotope(Zcenter); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation

options.taylorTerms = tTerms;
options.zonotopeOrder = zOrder;
options.polytopeOrder = pOrder;
options.errorOrder=0;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.originContained = 0;
%options.intersectInvariant =1;

%set input:
for i = 1:3
    options.timeStepLoc{i} = timeStep;
    options.uLoc{i} = 0;
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

% First location
options.startLoc = 2; %initial location
options.finalLoc = 0; %0: no final location
options.tStart = 0; %start time
options.tFinal = 15;

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
       
        %maxValue = findSafetyProperties([0 0 1], Rset)
        
        if diff == 1
            %easy: c2 <= 41.1
            spec = [0 0 1 41.1];
        elseif diff == 2
            %medium: c1 >= 34.93 & c2 >= 34.93
            spec = [0 -1 0 -34.93; 0 0 -1 -34.93];
        elseif diff == 3
            %hard: c2 <= 40.86
            spec = [0 0 1 40.86];
        elseif diff == 4
            %spec: x <= 550
            spec = [1 0 0 550];
        end

        safe = verifySafetyPropertiesCORA(spec, Rset);
        verificationT = toc;
        time = reachabilityT + verificationT;
    end
log = ['rod_reactor ', num2str(diff), ' ',...
num2str(reachabilityT), ' ',  num2str(verificationT), ' ',...
num2str(time), ' ' num2str(safe), ' ' num2str(strategy)];

% Visualization -------------------------------------------------------
if show    
    fig = figure(); 
    hold on
    options.projectedDimensions = [1 3];

    options.plotType = 'b';
    plot(HA,'reachableSet',options); %plot reachable set
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    set(gca,'FontSize',15);
    if diff == 1
        y = [60;60;41.1;41.1];
        x = [560;500;500;560];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    elseif diff == 2
        y = [60;60;34.93;34.93];
        x = [560;500;500;560];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    elseif diff == 3
        y = [60;60;40.86;40.86];
        x = [560;500;500;560];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    elseif diff == 4
        k = 550 : 600;
        spec1 = 0*k + 50;
        upper = 15 + 0*k;
        k1 = [k, fliplr(k)];
        inBetweenUpper = [spec1, fliplr(upper)];
        fill(k1,inBetweenUpper,[0.831, 0, 0], 'FaceAlpha',0.5, 'EdgeColor','none');
    end
    xlabel('x');
    ylabel('c2');
    if saveFig
        fname = strcat(filename,'.','png');
        saveas(fig, fullfile(savePath,fname),'png');
    end
end

x=[550,550];
y=[20,40];
plot(x,y,'m')
end