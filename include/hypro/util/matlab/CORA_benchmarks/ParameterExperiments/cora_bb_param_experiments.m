function cora_bb_param_experiments()

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

options.taylorTerms = 1;
options.zonotopeOrder = 20;
options.polytopeOrder = 10;

options.errorOrder=1e-12;
options.maxProjectionError=0.1;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';
options.originContained = 0;

%set input:
for i = 1:1
    options.timeStepLoc{i} = 0.01;
    options.uLoc{i} = 0;
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

% Reachability ------------------------------------------------------------
    tic;
    [HA] = reach(HA,options);
    reachabilityT = toc;
    disp(['Reachability needed: ', num2str(reachabilityT)]);

    
% Visualization -------------------------------------------------------   
figure(); 
hold on
options.projectedDimensions = [2 1];

options.plotType = 'b';
plot(HA,'reachableSet',options); %plot reachable set
plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
set(gca,'FontSize',15);
xlabel('v');
ylabel('x');

end