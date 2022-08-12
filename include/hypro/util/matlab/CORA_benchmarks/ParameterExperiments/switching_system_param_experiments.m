function switching_system_param_experiments()

HA = cora_linear_switching_system_ha();
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';
Zdelta = 1e-4*ones(5,1);

% options
Zcenter = [3.1;4;0;0;0];
options.R0 = zonotope([Zcenter,diag(Zdelta)]); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation

options.taylorTerms = 1;
options.zonotopeOrder = 4; % 3 schwachsinn
options.polytopeOrder = 1;

options.errorOrder=2;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.originContained = 0;
options.intersectInvariant =1;

%set input:
for i = 1:5
    options.timeStepLoc{i} = 0.01;
    options.uLoc{i} = 0;
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

% First location
options.startLoc = 1; %initial location
options.finalLoc = 0; %0: no final location
options.tStart = 0; %start time
options.tFinal = 1;

tic;
[HA] = reach(HA,options);
reachabilityT = toc;

disp(['Time needed for reachability: ', num2str(reachabilityT)]);

% Visualization -------------------------------------------------------
  
figure(); 
hold on
options.projectedDimensions = [1 3];

options.plotType = 'b';
plot(HA,'reachableSet',options); %plot reachable set
plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
set(gca,'FontSize',15);

xlabel('x1');
ylabel('x3');


end
