function [reachabilityTime, verificationTime, time, safe] = rendezvous_4np_mhypro(saveFig, savePath, figName, bad, diff,settings,setRepr,aggr, plotting)

% Create Automaton
automaton = MHyProHAutomaton();
dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(5));
dummy_reset.setVector([0; 0; 0; 0; 0]);

% Variables: [x; y; vx; vy; t]

%-----------------------------------------------%
%              Location p2
%-----------------------------------------------%

loc_p2 = MHyProLocation();
loc_p2.setName('p2');

% Set flow:
% x'==vx & y'==vy &
% vx'==-0.057599765881773*x+0.000200959896519766*y-2.89995083970656*vx+0.00877200894463775*vy &
% vy'==-0.000174031357370456*x-0.0665123984901026*y-0.00875351105536225*vx-2.90300269286856*vy
% t'==1 

flow_p2 = [0,0,1,0,0,0;...
           0,0,0,1,0,0;...
           -0.05759976588,0.0002009598965,-2.89995084,0.008772008945,0,0;...
           -0.0001740313574,-0.06651239849,-0.008753511055,-2.903002693,0,0;...
           0,0,0,0,0,1];

loc_p2.setFlow(flow_p2);

% Set invariant: x <= -100

inv_p2 = MHyProCondition([1 0 0 0 0], -100);
loc_p2.setInvariant(inv_p2);

%-----------------------------------------------%
%              Location p3
%-----------------------------------------------%

loc_p3 = MHyProLocation();
loc_p3.setName('p3');

% Set flow: 
% x'==vx & y'==vy &
% vx'==-0.575999943070835*x+0.000262486079431672*y-19.2299795908647*vx+0.00876275931760007*vy &
% vy'==-0.000262486080737868*x-0.575999940191886*y-0.00876276068239993*vx-19.2299765959399*vy
% t' ==1

flow_p3 = [0,0,1,0,0,0;...
           0,0,0,1,0,0;...
          -0.5759999431,0.0002624860794,-19.22997959,0.008762759318,0,0;...
          -0.0002624860807,-0.5759999402,-0.008762760682,-19.2299766,0,0;...
          0,0,0,0,0,1];
      
loc_p3.setFlow(flow_p3);

% Set invariant: y>=-100 & x+y>=-141.1 & x>=-100 & y-x<=141.1 & y<=100 &
%     x+y<=141.1 & x<=100 & y-x>=-141.1
invMatrix = [0,-1,0,0,0;...
            -1,-1,0,0,0;...
            -1,0,0,0,0;...
            -1,1,0,0,0;...
            0,1,0,0,0;...
            1,1,0,0,0;...
            1,0,0,0,0;...
            1,-1,0,0,0];
invVec = [100;141.1;100;141.1;100;141.1;100;141.1];

inv_p3 = MHyProCondition(invMatrix, invVec);
loc_p3.setInvariant(inv_p3);


p2 = automaton.addLocation(loc_p2);
p3 = automaton.addLocation(loc_p3);

%-----------------------------------------------%
%              p2 -> p3
%-----------------------------------------------%

tran = MHyProTransition();
% Set guard: y>=-100 & x+y >=-141.1 & x>=-100 & y-x<=141.1 & y<=100 &
%            x+y<=141.1 & x<=100 & y-x>=-141.1
guardMatrix = [0,-1,0,0,0;-1,-1,0,0,0;-1,0,0,0,0;-1,1,0,0,0;0,1,0,0,0;1,1,0,0,0;1,0,0,...
0,0;1,-1,0,0,0];
guardVector = [100;141.1;100;141.1;100;141.1;100;141.1];
guard = MHyProCondition();
guard.setMatrix(guardMatrix); % First set the matrix then the vector!?
guard.setVector(guardVector);

dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(5));
dummy_reset.setVector([0; 0; 0;0;0]);

tran.setAggregation(aggr);
tran.setGuard(guard);
tran.setSource(p2);
tran.setTarget(p3);
tran.setReset(dummy_reset);
tran.setLabels({MHyProLabel('tran')});

p2.addTransition(tran);

%-----------------------------------------------%
%                 Bad States
%-----------------------------------------------%


if bad
    if diff == 0
        %easy
        badState = MHyProCondition();
        badState.setMatrix([0 0 -1 0 0;0 0 0 -1 0]);
        badState.setVector([-18;10]);
        badStates(1).loc = p2;
        badStates(1).cond = badState;
        badStates(2).loc = p3;
        badStates(2).cond = badState;
%         spec = [0 0 1 0 0 18; 0 0 0 1 0 10];
    elseif diff == 1
        %medium
        badState = MHyProCondition();
        badState.setMatrix([0 0 -1 0 0;0 0 0 -1 0]);
        badState.setVector([-17.93395;9.72075]);
        badStates(1).loc = p2;
        badStates(1).cond = badState;
        badStates(2).loc = p3;
        badStates(2).cond = badState;
%         spec = [0 0 1 0 0 17.93395; 0 0 0 1 0 9.72075];
    else
        %hard
        badState = MHyProCondition();
        badState.setMatrix([0 0 -1 0 0;0 0 0 -1 0]);
        badState.setVector([-17.8679;9.4415]);
        badStates(1).loc = p2;
        badStates(1).cond = badState;
        badStates(2).loc = p3;
        badStates(2).cond = badState;
%         spec = [0 0 1 0 0 17.8679; 0 0 0 1 0 9.4415];
    end
    
    automaton.setLocalBadStates(badStates);
end

%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% x = [-925; -875] y = [-425; -375] vx,vy,t = 0
boxVector = [-875; -375; 0; 0 ;0; 925; 425; 0; 0; 0];
boxMatrix = [eye(5);-1*eye(5)];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(p2, initialCond);


%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%


% Add basic settings
settings.timeBound = 20;
settings.jumpDepth = 10;

reach = MHyProReach(automaton);
reach.setSettings(settings);
reach.setRepresentationType(setRepr);

tic;
flowpipes = reach.computeForwardReachability();
reachabilityTime = toc;
verificationTime = 0;
safe = 0;
if bad
    tic;
    %     safe = reach.verify(flowpipes, spec);
    safe = 1 - reach.reachedBadStates();
    verificationTime = toc;
end

time = reachabilityTime + verificationTime;
% disp(['Time needed for reachability: ', num2str(reachabilityTime)]);
% disp(['Time needed for verification: ', num2str(verificationTime)]);
% disp(['Overall time needed: ', num2str(time)]);

if plotting == 1
    dim = [3 4];
    labs = ["vx", "vy"];
    ext = 'png';
    reach.plot(flowpipes, dim, labs,saveFig,savePath,figName,ext);
elseif plotting == 2
    dim = [3 4 5];
    labs = ["vx", "vy", "t"];
    ext = 'png';
    reach.plot3D(flowpipes, dim, labs,saveFig,savePath,figName,ext);
end

end