function cora_vp_param_experiments()

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


% Visualization -------------------------------------------------------
figure(); 
hold on
options.projectedDimensions = [1 7];

options.plotType = 'b';
plot(HA,'reachableSet',options); %plot reachable set
plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
set(gca,'FontSize',15);
    xlabel('e1');
    ylabel('e3');

options.taylorTerms = 100;
options.zonotopeOrder = 5; % ab 4 schwachsinn
options.polytopeOrder = 10;

tic;
[HA] = reach(HA,options);
reachabilityT = toc;
disp(['Time needed for the reachability: ', num2str(reachabilityT)]);


% Visualization -------------------------------------------------------

options.projectedDimensions = [1 7];

options.plotType = 'g';
plot(HA,'reachableSet',options); %plot reachable set
plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
set(gca,'FontSize',15);

end