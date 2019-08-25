function log = boost_v1_cora(saveFig,savePath,filename, diff, show, timeStep, tTerms, zOrder, pOrder, strategy)

% Zono Girard
HA = boost_v1_ha_zG();
options.enclosureEnables = [1 2];
options.guardIntersect = 'zonoGirard';
Zdelta = zeros(4,1);


% options
Zcenter = [0;0;0;0];

options.R0 = zonotope([Zcenter,diag(Zdelta)]); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation

options.startLoc = 1; %initial location
options.finalLoc = 0; %0: no final location
options.tStart = 0; %start time
options.tFinal = 0.001;
options.taylorTerms = 5;
options.zonotopeOrder = 2;
options.polytopeOrder = 2;
options.errorOrder=0.1;
options.maxProjectionError=inf;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.originContained = 0;


%set input:
% Vs  == 20
for i = 1:2
    options.timeStepLoc{i} = 0.0000001;
    options.uLoc{i} = interval(20, 20);
    options.uLocTrans{i} = options.uLoc{1};
    options.Uloc{i} = zonotope(options.uLoc{1});
end

% Reachability ------------------------------------------------------------
    tic;
    [HA] = reach(HA,options);
    reachabilityT = toc;
    safe = 0;
    verificationT = 0;
    time = 0;
    % Verification --------------------------------------------------------
%     if diff ~= 0
%         tic;
%         Rset = get(HA, 'reachableSet');
%         Rset = Rset.OT;
%         
%         %maxValue = findSafetyProperties([0 1], Rset)
%         if diff == 4
%             % special: x >= 0 
%             spec = [1 0 0];
%         elseif diff == 3
%             %hard: v <= 10.6138
%             spec = [0 1 10.6138];
%         elseif diff == 2
%             %medium: v <= 10.6569
%             spec = [0 1 10.6569];
%         elseif diff == 1
%             %easy: v <= 10.7
%             spec = [0 1 10.7]; 
%         end
%         
%         safe = verifySafetyPropertiesCORA(spec, Rset);
%         verificationT = toc;
%         time = reachabilityT + verificationT;
%     end
    
    log = ['boost_v1_cora ', num2str(diff), ' ',...
    num2str(reachabilityT), ' ',  num2str(verificationT), ' ',...
    num2str(time), ' ' num2str(safe), ' ', num2str(strategy)];
    
% Visualization -------------------------------------------------------
if show    
    fig = figure(); 
    hold on
    options.projectedDimensions = [1 4];

    options.plotType = 'b';
    plot(HA,'reachableSet',options); %plot reachable set
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    if diff == 1
        x = [15;15;10.7;10.7];
        y = [15;-2;-2;15];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    elseif diff == 2
        x = [15;15;10.6569;10.6569];
        y = [15;-2;-2;15];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    elseif diff == 3
        x = [15;15;10.6138;10.6138];
        y = [15;-2;-2;15];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    elseif diff == 4
        x = [12;-15;-15;12];
        y = [0;0;-5;-5];
        pgon = polyshape([x,y], 'Simplify', false);
        plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
    end
    xlabel('v');
    ylabel('x');
    
    if saveFig
        fname = strcat(filename,'.','png');
        saveas(fig, fullfile(savePath,fname),'png');
    end
end
end