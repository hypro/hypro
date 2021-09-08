function log = rendezvousSX4np_cora(saveFig,savePath,filename, diff, show,timeStep, tTerms, zOrder, pOrder, strategy)

R0 = zonotope([[-900; -400; 0; 0; 0],diag([25;25;0;0;0])]);

% initial set
options.x0=center(R0); % initial state for simulation
options.R0=R0; % initial state for reachability analysis

% other
options.startLoc = 1; % initial location
options.finalLoc = 0; % no final location
options.tStart=0; % start time
options.tFinal=20; % final time
options.intermediateOrder = 2;
options.originContained = 0;

options.taylorTerms = tTerms;
options.zonotopeOrder = zOrder;
options.polytopeOrder = pOrder;
%options.intersectInvariant =1;
    
options.reductionTechnique = 'girard';
options.isHyperplaneMap=0;
options.enclosureEnables = [3, 5]; % choose enclosure method(s)
options.filterLength = [5,7];
options.guardIntersect = 'polytope';
options.errorOrder = 2;

% specify hybrid automata
HA = rendezvousSX4np_ha(); % automatically converted from SpaceEx

for i = 1:5
    options.timeStepLoc{i} = timeStep;
    options.uLoc{i} = 0;
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
        
        %maxValue = findSafetyProperties([0 0 1 0 0; 0 0 0 1 0], Rset);
        
        if diff == 1
            %easy: vx <= 18 vy <= 10
            spec = [0 0 1 0 0 18; 0 0 0 1 0 10];
        elseif diff == 2
            %medium: vx <= 17.95 vy <= 9.7364
            spec = [0 0 1 0 0 17.95; 0 0 0 1 0 9.7364];
        elseif diff == 3
            %hard: vx <= 17.8679 vy <= 9.4415
            spec = [0 0 1 0 0 17.8679; 0 0 0 1 0 9.4415];
        elseif diff == 4
            % spec: −0.558⋅vx+vy≤0.1
            spec = [0 0 -0.558 1 0 0.1];
        end
        safe = verifySafetyPropertiesCORA(spec, Rset);
        verificationT = toc;
        time = reachabilityT + verificationT;
    end
log = ['rendezvous ', num2str(diff), ' ',...
    num2str(reachabilityT), ' ',  num2str(verificationT), ' ',...
    num2str(time), ' ' num2str(safe), ' ', num2str(strategy)];

% Visualization -------------------------------------------------------
if show    
    fig = figure(); 
    hold on
    options.projectedDimensions = [3 4];

    options.plotType = 'b';
    plot(HA,'reachableSet',options); %plot reachable set
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    set(gca,'FontSize',15);
    if diff == 1
        y = [12;12;10;10];
        x = [20;-5;-5;20];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
        x = [20;20;18;18];
        y = [12;-2;-2;12];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    elseif diff == 2
        y = [12;12;9.72075;9.72075];
        x = [20;-5;-5;20];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
        x = [20;20;17.93395;17.93395];
        y = [12;-2;-2;12];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    elseif diff == 3
        y = [12;12;9.4415;9.4415];
        x = [20;-5;-5;20];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
        x = [20;20;17.8679;17.8679];
        y = [12;-2;-2;12];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    elseif diff == 4
        k = 0 : 18;
        spec1 = 0.558*k + 0.1;
        upper = 12 + 0*k;
        hold on;
        k1 = [k, fliplr(k)];
        inBetweenUpper = [spec1, fliplr(upper)];
        fill(k1,inBetweenUpper,[0.831, 0, 0], 'FaceAlpha',0.5, 'EdgeColor','none');
    end
    xlabel('vx');
    ylabel('vy');
    if saveFig
        fname = strcat(filename,'.','png');
        saveas(fig, fullfile(savePath,fname),'png');
    end
end
end
