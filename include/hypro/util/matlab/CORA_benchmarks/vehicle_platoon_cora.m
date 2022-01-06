function log = vehicle_platoon_cora(saveFig,savePath,filename, diff, show, timeStep, tTerms, zOrder, pOrder, strategy)

HA = vehicle_platoon_ha();
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';
Zdelta = [0.1*ones(9,1);0];

% options
Zcenter = ones(10,1);
Zcenter(10) = 0;
options.R0 = zonotope([Zcenter,diag(Zdelta)]); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation

options.taylorTerms = 1;
options.zonotopeOrder = 5; % ab 4 schwachsinn
options.polytopeOrder = 10;
options.errorOrder=2;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.originContained = 0;
%options.intersectInvariant =1;

%set input:
for i = 1:2
    options.timeStepLoc{i} = 0.02;
    options.uLoc{i} = 0;
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

% First location
options.startLoc = 1; %initial location
options.finalLoc = 0; %0: no final location
options.tStart = 0; %start time
options.tFinal = 12;

tic;
[HA] = reach(HA,options);
reachabilityT = toc;
disp(['Time needed for the reachability: ', num2str(reachabilityT)]);
    % Verification --------------------------------------------------------
    if diff ~= 0
        tic;
        Rset = get(HA, 'reachableSet');
        Rset = Rset.OT;
        
        %maxValue = findSafetyProperties([1 0 0 0 0 0 0 0 0 0], Rset);
        
        if diff == 1
            %easy: e1 <= 1.7
            spec = [1 0 0 0 0 0 0 0 0 0 1.7];
        elseif diff == 2
            %medium: e1 <= 1.66815
            spec = [1 0 0 0 0 0 0 0 0 0 1.66815];
        elseif diff == 3
            %hard: e1 <= 1.6363
            spec = [1 0 0 0 0 0 0 0 0 0 1.6363];
        elseif diff == 4
            %spec: 0.855e1 +e3 <= -0.05
            spec = [0.855 0 0 0 0 0 1 0 0 0 -0.05];
        end
        safe = verifySafetyPropertiesCORA(spec, Rset);
        verificationT = toc;
        time = reachabilityT + verificationT;
    end
log = ['vehicle_platoon ', num2str(diff), ' ',...
num2str(reachabilityT), ' ',  num2str(verificationT), ' ',...
num2str(time), ' ' num2str(safe), ' ', num2str(strategy)];

% Visualization -------------------------------------------------------
if show    
    fig = figure(); 
    hold on
    options.projectedDimensions = [1 7];

    options.plotType = 'b';
    plot(HA,'reachableSet',options); %plot reachable set
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    set(gca,'FontSize',15);
    if diff == 1
        y = [1.7;1.7;2;2];
        x = [2.5;0;0;2.5];
        pgon = polyshape([y,x], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    elseif diff == 2
        y = [-0.7;-0.7;-1;-1];
        x = [2;-1;-1;2];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    elseif diff == 3
        y = [2;2;1.7;1.7];
        x = [1.8;0;0;1.8];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    elseif diff == 4
        k = 0 : 2;
        spec1 = 0.7*k -0.05;
        upper = -0.1 + 0*k;
        hold on;
        k1 = [k, fliplr(k)];
        inBetweenUpper = [spec1, fliplr(upper)];
        fill(k1,inBetweenUpper,[0.831, 0, 0], 'FaceAlpha',0.5, 'EdgeColor','none');
    end
    xlabel('e1');
    ylabel('e3');
    if saveFig
        fname = strcat(filename,'.','png');
        saveas(fig, fullfile(savePath,fname),'png');
    end
end
end