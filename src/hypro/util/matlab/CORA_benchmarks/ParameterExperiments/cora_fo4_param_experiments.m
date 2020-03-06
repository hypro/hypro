function cora_fo4_param_experiments()

HA = filtered_oscillator_4_ha();
options.enclosureEnables = [3 5];
options.guardIntersect = 'polytope';

Zdelta = [0.05;0.1;0;0;0;0];

% options
Zcenter = [0.25;0;0;0;0;0];
options.R0 = zonotope([Zcenter,diag(Zdelta)]); %initial state for reachability analysis
options.x0 = center(options.R0); %initial state for simulation

options.taylorTerms = 2;
options.zonotopeOrder = 100;
options.polytopeOrder = 10;


options.errorOrder=2;
options.reductionTechnique = 'girard';
options.isHyperplaneMap = 0;
options.originContained = 0;
%options.intersectInvariant =1;

%set input:
for i = 1:4
    options.timeStepLoc{i} = 0.005;
    options.uLoc{i} = 0;
    options.uLocTrans{i} = options.uLoc{i};
    options.Uloc{i} = zonotope(options.uLoc{i});
end

% First location
options.startLoc = 3; %initial location
options.finalLoc = 0; %0: no final location
options.tStart = 0; %start time
options.tFinal = 4;


tic;
[HA] = reach(HA,options);
reachabilityT = toc;
disp(['Reachability analysis needed: ', num2str(reachabilityT)]);

% Visualization -------------------------------------------------------
 figure(); 
hold on
options.projectedDimensions = [3 2];

options.plotType = 'b';
plot(HA,'reachableSet',options); %plot reachable set
plotFilled(options.R0,options.projectedDimensions,'w','EdgeColor','k'); %plot initial set
set(gca,'FontSize',15);    
xlabel('x1');
ylabel('y');
    


end
