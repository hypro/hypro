function log = cora_bouncing_ball(saveFig,savePath,filename, diff, show, timeStep, tTerms, zOrder, pOrder, strategy)

HA = cora_bouncing_ball_ha();
Zdelta = [0.1;0;0];


% options
Zcenter = [10.1;0;0];
options.R0 = zonotope([Zcenter,diag(Zdelta)]); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation

% First location
options.startLoc = 1; %initial location
options.finalLoc = 0; %0: no final location
options.tStart = 0; %start time
options.tFinal = 4;
%options.intersectInvariant =1;

options.taylorTerms = tTerms;
options.zonotopeOrder = zOrder;
options.polytopeOrder = pOrder;

options.errorOrder=1e-12;
options.maxProjectionError=0.1;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';
options.originContained = 0;

%set input:
for i = 1:1
    options.timeStepLoc{i} = timeStep;
    options.uLoc{i} = 0;
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end


if 0
    N = 1;
    tic;
    for i=1:N
        %set initial state, input
        if i == 1
            %simulate center
            options.x0 = center(options.R0);
        elseif i < 5
            % simulate extreme points
            options.x0 = randPointExtreme(options.R0);
        else
            % simulate random points
            options.x0 = randPoint(options.R0);
        end 

        %simulate hybrid automaton
        HAsim = simulate(HA,options);
        simRes{i} = get(HAsim,'trajectory');
    end
    toc;
    disp(['Time needed for the simulation: ', num2str(toc)]);

    % Visualization -------------------------------------------------------
    figure 
    hold on
    box on
    options.projectedDimensions = [2 1];
    options.plotType = {'b','m','g'};
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    set(gca,'FontSize',15);
    for i = 1:length(simRes)
       for j = 1:length(simRes{i}.x)
           plot(simRes{i}.x{j}(:,options.projectedDimensions(1)), ...
                simRes{i}.x{j}(:,options.projectedDimensions(2)),'k'); 
       end
    end
    xlabel('t');
    ylabel('x');
    
    figure 
    hold on
    box on
    options.projectedDimensions = [3 2];
    options.plotType = {'b','m','g'};
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set

    for i = 1:length(simRes)
       for j = 1:length(simRes{i}.x)
           plot(simRes{i}.x{j}(:,options.projectedDimensions(1)), ...
                simRes{i}.x{j}(:,options.projectedDimensions(2)),'k'); 
       end
    end
    xlabel('t');
    ylabel('d');
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
        
        %maxValue = findSafetyProperties([0 1], Rset)
        if diff == 4
            % special: x >= 0 
            spec = [1 0 0];
        elseif diff == 3
            %hard: v <= 10.6138
            spec = [0 1 10.6138];
        elseif diff == 2
            %medium: v <= 10.6569
            spec = [0 1 10.6569];
        elseif diff == 1
            %easy: v <= 10.7
            spec = [0 1 10.7]; 
        end
        
        safe = verifySafetyPropertiesCORA(spec, Rset);
        verificationT = toc;
        time = reachabilityT + verificationT;
    end
    
    log = ['bouncing_ball ', num2str(diff), ' ',...
    num2str(reachabilityT), ' ',  num2str(verificationT), ' ',...
    num2str(time), ' ' num2str(safe), ' ', num2str(strategy)];
    
% Visualization -------------------------------------------------------
if show    
    fig = figure(); 
    hold on
    options.projectedDimensions = [2 1];

    options.plotType = 'b';
    plot(HA,'reachableSet',options); %plot reachable set
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    set(gca,'FontSize',15);
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
    
%     x = [15;15;10.7;10.7];
%     y = [15;-2;-2;15];
%     pgon = polyshape([x,y], 'Simplify', false);
%     plot(pgon,'FaceColor',[0.447, 0.447, 0.454], 'FaceAlpha',0.5,'EdgeColor', 'none');
%     



% HAsim = simulate(HA,options);
% simRes{i} = get(HAsim,'trajectory');
% % figure 
% % hold on
% % % box on
% options.projectedDimensions = [3 1];
% options.plotType = {'b','m','g'};
% plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
% for i = 1:length(simRes)
%    for j = 1:length(simRes{i}.x)
%        plot(simRes{i}.x{j}(:,options.projectedDimensions(1)), ...
%             simRes{i}.x{j}(:,options.projectedDimensions(2)),'r');
%         set(gca,'FontSize',18)
%    end
% end
% xlabel('t');
% ylabel('x');
% 
% x = 0:2;
% y = x*0+0;
% plot(x,y,'m')
% 
% 
% offset = 0.012; % How much away from the marker the text should be.
% x = [1.41;1.42;1.43;1.44;1.45];
% y = [0.4485;0.3097;0.1699;0.02911;-0.1126];
% index = 1:5;
% plot(x(index), y(index), 'or', 'LineWidth', 2);
% grid on;
% for k = 1 : length(y)
%     caption = sprintf('t=%.2f, x=%.2f', x(k), y(k));
%     text(x(k) + offset, y(k) + offset, caption, 'BackgroundColor', 'w', 'FontSize',15);
% end
% plot(1.435, 0, 'ok', 'LineWidth', 3);
% caption = sprintf('t=%.3f, x=%.3f',1.435, 0);
% text(1.435 - 0.045, 0 + 0.004, caption, 'BackgroundColor', 'y', 'FontSize',15);
% end


end