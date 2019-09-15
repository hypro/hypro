function log = cora_rr_param_experiments()

HA = rod_reactor_HA_cora();
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';

% options
Zcenter = interval([510;20;20],[520;20;20]);
options.R0 = zonotope(Zcenter); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation

options.taylorTerms = 1;
options.zonotopeOrder = 50;
options.polytopeOrder = 10;
options.errorOrder=2;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.originContained = 0;
%options.intersectInvariant =1;

%set input:
for i = 1:3
    options.timeStepLoc{i} = 0.01;
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
disp(['Time needed for the reachability: ', num2str(reachabilityT)]);

% Visualization -------------------------------------------------------  
figure(); 
hold on
options.projectedDimensions = [1 3];

options.plotType = 'b';
plot(HA,'reachableSet',options); %plot reachable set
plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
end