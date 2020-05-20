function cora_tt_param_experiments()

HA = two_tanks_ha();
options.enclosureEnables = [1];
options.guardIntersect = 'polytope';
Zdelta = [0.5;0];

% options
Zcenter = [2;1];
options.R0 = zonotope([Zcenter,diag(Zdelta)]); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation

options.taylorTerms = 1;
options.zonotopeOrder = 2;
options.polytopeOrder = 10;

options.errorOrder=2;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.originContained = 0;
%options.intersectInvariant =1;

%set input:
for i = 1:4
    options.timeStepLoc{i} = 0.01;
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
disp(['Time needed for reachability: ', num2str(reachabilityT)]);

% Visualization -------------------------------------------------------

figure(); 
hold on
options.projectedDimensions = [1 2];

options.plotType = 'b';
plot(HA,'reachableSet',options); %plot reachable set
plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
end