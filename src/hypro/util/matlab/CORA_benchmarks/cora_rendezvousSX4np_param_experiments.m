function cora_rendezvousSX4np_param_experiments()

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

options.taylorTerms = 1;
options.zonotopeOrder = 1;
options.polytopeOrder = 10;
%options.intersectInvariant =1;
    
options.reductionTechnique = 'girard';
options.isHyperplaneMap=0;
options.enclosureEnables = [1]; % choose enclosure method(s)
options.filterLength = [5,7];
options.guardIntersect = 'polytope';
options.errorOrder = 2;

% specify hybrid automata
HA = rendezvousSX4np_ha(); % automatically converted from SpaceEx

for i = 1:5
    options.timeStepLoc{i} = 0.01;
    options.uLoc{i} = 0;
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

% Reachability ------------------------------------------------------------
tic;
[HA] = reach(HA,options);
reachabilityT = toc;
disp(['Time needed for the reachability: ', num2str(reachabilityT)]);

% Visualization -------------------------------------------------------
figure(); 
hold on
options.projectedDimensions = [3 4];

options.plotType = 'b';
plot(HA,'reachableSet',options); %plot reachable set
plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set

end
