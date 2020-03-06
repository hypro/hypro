function intersectInvariant_experiments()

HA = intersectInvariant_experiments_ha();
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';

% options
Zcenter = interval([0;0],[0.001;0]);
options.R0 = zonotope(Zcenter); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation

options.taylorTerms = 100;
options.zonotopeOrder = 200;
options.polytopeOrder = 100;
options.errorOrder=0;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.originContained = 0;

%set input:
for i = 1:2
    options.timeStepLoc{i} =0.05;
    options.uLoc{i} = 0;
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

% First location
options.startLoc = 1; %initial location
options.finalLoc = 0; %0: no final location
options.tStart = 0; %start time
options.tFinal = 20;

options.intersectInvariant = 0;

[HA] = reach(HA,options);

% Visualization -------------------------------------------------------

    figure(); 
    hold on
    x = 0:25;
    y = 10.02 + 0*x;
    plot(x,y,'m');
    x = 0:25;
    y = 10.1 + 0*x;
    plot(x,y,'g');
    options.projectedDimensions = [2 1];
    options.plotType = 'b';
    plot(HA,'reachableSet',options); %plot reachable set
    plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
    
    
    
%     k = 0 : 3;
%     spec1 = -1*k + 3;
%     upper = -1*k + 3.0303;
%     hold on;
%     k1 = [k, fliplr(k)];
%     inBetweenUpper = [spec1, fliplr(upper)];
%     fill(k1,inBetweenUpper,[0.831, 0, 0], 'FaceAlpha',0.5, 'EdgeColor','none');

end