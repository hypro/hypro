function log = filtered_oscillator_16_mhypro(saveFig, savePath, figName, bad, diff,settings,setRepr,aggr, plotting, strategy)

% vars = [ state var x,y,f8a_f4a_x1,f8a_f4a_x2,f8a_f4a_x3,f8a_x1,f8a_f4b_x1,
%    f8a_f4b_x2,f8a_f4b_x3,x1,f8b_f4a_x1,f8b_f4a_x2,f8b_f4a_x3,f8b_x1,
%    f8b_f4b_x1,f8b_f4b_x2,f8b_f4b_x3,z]

% Create Automaton
automaton = MHyProHAutomaton();
dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(18));
dummy_reset.setVector(zeros(18,1));

%-----------------------------------------------%
%              Location loc1
%-----------------------------------------------%
loc1 = MHyProLocation();
loc1.setName('loc1');

% Set flow:
flow_loc1 = [-2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1.4;...
             0 -1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -0.7;...
             5  0 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
loc1.setFlow(flow_loc1);

% Set inv: x <= 0 & y + 0.714286x >= 0
invMat = [1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
    -0.714286 -1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
inv_loc1 = MHyProCondition(invMat, [0;0]);
loc1.setInvariant(inv_loc1);


%-----------------------------------------------%
%              Location loc2
%-----------------------------------------------%
loc2 = MHyProLocation();
loc2.setName('loc2');

flow_loc2 = [-2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -1.4;...
             0 -1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0.7;...
             5  0 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
loc2.setFlow(flow_loc2);

% Set inv: x <= 0 & y + 0.714286x <= 0
invMat = [1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
    0.714286 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
inv_loc2 = MHyProCondition(invMat, [0;0]);
loc2.setInvariant(inv_loc2);

%-----------------------------------------------%
%              Location loc3
%-----------------------------------------------%
loc3 = MHyProLocation();
loc3.setName('loc3');

% Set flow:
flow_loc3 = [-2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1.4;...
             0 -1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -0.7;...
             5  0 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0  5 -5 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
loc3.setFlow(flow_loc3);

% Set inv: x >= 0 & y + 0.714286x >= 0
invMat = [-1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
    -0.714286 -1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
inv_loc3 = MHyProCondition(invMat, [0;0]);
loc3.setInvariant(inv_loc3);

%-----------------------------------------------%
%              Location loc4
%-----------------------------------------------%
loc4 = MHyProLocation();
loc4.setName('loc4');

% Set flow:
flow_loc4 = [-2 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -1.4;...
             0 -1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0.7;...
             5  0 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0  5 -5 0 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 -5 0;...
             0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
loc4.setFlow(flow_loc4);

% Set inv: x >= 0 & y + 0.714286x <= 0
invMat = [-1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
    0.714286 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
inv_loc4 = MHyProCondition(invMat, [0;0]);
loc4.setInvariant(inv_loc4);

l1 = automaton.addLocation(loc1);
l2 = automaton.addLocation(loc2);
l3 = automaton.addLocation(loc3);
l4 = automaton.addLocation(loc4);

%-----------------------------------------------%
%              loc1 -> loc3
%-----------------------------------------------%

tran1 = MHyProTransition();
% Set guard: x = 0 & 0.714286x + y >= 0
guardMatrix = [1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
    -1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0; -0.714286 -1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
guard1 = MHyProCondition();
guard1.setMatrix(guardMatrix);
guard1.setVector([0;0;0]);

tran1.setAggregation(aggr);
tran1.setGuard(guard1);
tran1.setSource(l1);
tran1.setTarget(l3);
tran1.setLabels({MHyProLabel('tran1')});

l1.addTransition(tran1);

%-----------------------------------------------%
%              loc3 -> loc4
%-----------------------------------------------%

tran2 = MHyProTransition();
% Set guard: x >= 0 & 0.714286x + y = 0
guardMatrix = [-1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
    -0.714286 -1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
    0.714286 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
guard2 = MHyProCondition();
guard2.setMatrix(guardMatrix);
guard2.setVector([0;0;0]);

tran2.setAggregation(aggr);
tran2.setGuard(guard2);
tran2.setSource(l3);
tran2.setTarget(l4);
tran2.setLabels({MHyProLabel('tran2')});

l3.addTransition(tran2);

% test
locT = l3.getTransitions();
assert(length(locT) == 1);
lab1 = locT{1}.getLabels();
assert(isequal(lab1{1}.getName(), 'tran2'));
g = tran2.getGuard();
assert(g == guard2);
s = tran2.getSource();
t = tran2.getTarget();
assert(s == l3);
assert(t == l4);
% test end

%-----------------------------------------------%
%              loc4 -> loc2
%-----------------------------------------------%

tran3 = MHyProTransition();
% Set guard: x = 0 & 0.714286x + y <= 0
guardMatrix = [-1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
                1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;...
                0.714286 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
guard3 = MHyProCondition();
guard3.setMatrix(guardMatrix);
guard3.setVector([0;0;0]);

tran3.setAggregation(aggr);
tran3.setGuard(guard3);
tran3.setSource(l4);
tran3.setTarget(l2);
tran3.setLabels({MHyProLabel('tran3')});

l4.addTransition(tran3);

%-----------------------------------------------%
%              loc2 -> loc1
%-----------------------------------------------%

tran4 = MHyProTransition();
% Set guard: x <= 0 & 0.714286x + y = 0
guardMatrix = [1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
        0.714286 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0;
        -0.714286 -1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0];
guard4 = MHyProCondition();
guard4.setMatrix(guardMatrix);
guard4.setVector([0;0;0]);

tran4.setAggregation(aggr);
tran4.setGuard(guard4);
tran4.setSource(l2);
tran4.setTarget(l1);
tran4.setLabels({MHyProLabel('tran4')});

l2.addTransition(tran4);

%-----------------------------------------------%
%                 Bad States
%-----------------------------------------------%

% unsafe: y >= 0.5

if bad
    if diff == 0
        %easy
        badState = MHyProCondition();
        badState.setMatrix([0 -1 0 0 0 0]);
        badState.setVector(-0.5);
        badStates(1).loc = l1;
        badStates(1).cond = badState;
        badStates(2).loc = l2;
        badStates(2).cond = badState;
        badStates(3).loc = l3;
        badStates(3).cond = badState;
        badStates(4).loc = l4;
        badStates(4).cond = badState;
%         spec = [0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0.5];
    elseif diff == 1
        %medium
        badState = MHyProCondition();
        badState.setMatrix([0 -1 0 0 0 0]);
        badState.setVector(-0.4946);
        badStates(1).loc = l1;
        badStates(1).cond = badState;
        badStates(2).loc = l2;
        badStates(2).cond = badState;
        badStates(3).loc = l3;
        badStates(3).cond = badState;
        badStates(4).loc = l4;
        badStates(4).cond = badState;
%         spec = [0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0.4946];
    else
        %hard
        badState = MHyProCondition();
        badState.setMatrix([0 -1 0 0 0 0]);
        badState.setVector(-0.4892);
        badStates(1).loc = l1;
        badStates(1).cond = badState;
        badStates(2).loc = l2;
        badStates(2).cond = badState;
        badStates(3).loc = l3;
        badStates(3).cond = badState;
        badStates(4).loc = l4;
        badStates(4).cond = badState;
%         spec = [0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0.4892];
    end

    automaton.setLocalBadStates(badStates);
end

%-----------------------------------------------%
%              Initial Set
%-----------------------------------------------%
%
boxVector = [0.3; 0.1;zeros(16,1); -0.2; 0.1; zeros(16,1)];
boxMatrix = [eye(18); -1*eye(18)];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(l3, initialCond);

%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

% Add basic settings
settings.timeBound = 4;
settings.jumpDepth = 5;

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
log = ['filterd_oscillator_16 ', num2str(strategy), ' ', num2str(diff), ' ',...
    num2str(reachabilityTime), ' ',  num2str(verificationTime), ' ',...
    num2str(time), ' ' num2str(safe)];

if plotting == 1
    dim = [1 6];
    labs = ["x", "f8x1"];
    ext = 'png';
    reach.plot(flowpipes, dim, labs,saveFig,savePath,figName,ext);
elseif plotting == 2
    dim = [1 2 3];
    labs = ["x", "y", "f8x1"];
    ext = 'png';
    reach.plot3D(flowpipes, dim, labs,saveFig,savePath,figName,ext);
end

end