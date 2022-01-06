function [reachabilityTime, verificationTime, time, safe] = two_tanks_mhypro(saveFig, savePath, figName, bad, diff,settings,setRepr,aggr, plotting)

timeHorizon = 2;
% Create Automaton
automaton = MHyProHAutomaton();
dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(3));
dummy_reset.setVector([0; 0; 0]);

%-----------------------------------------------%
%              Location loc1
%-----------------------------------------------%
loc_1 = MHyProLocation();
loc_1.setName('loc1');

% Set flow: x1' = -x1 - 2 , x2' = x1 gc' = 1
flow1 = [-1 0 0 -2; 1 0 0 0; 0 0 0 1; 0 0 0 0];
loc_1.setFlow(flow1);

% Set inv: x1 >= -1 & x2 <= 1 & gc <= timeHorizon
inv_1 = MHyProCondition([-1 0 0; 0 1 0; 0 0 1], [1; 1; timeHorizon]);
loc_1.setInvariant(inv_1);

%-----------------------------------------------%
%              Location loc2
%-----------------------------------------------%
loc_2 = MHyProLocation();
loc_2.setName('loc2');

% Set flow: x1' = -x1 + 3, x2' = x1 & gc' = 1
flow_2 = [-1 0 0 3; 1 0 0 0; 0 0 0 1; 0 0 0 0];
loc_2.setFlow(flow_2);

% Set inv: x2 <= 1 & gc <= timeHorizon
inv_2 = MHyProCondition([0 1 0; 0 0 1], [1;timeHorizon]);
loc_2.setInvariant(inv_2);

%-----------------------------------------------%
%              Location loc3
%-----------------------------------------------%
loc_3 = MHyProLocation();
loc_3.setName('loc3');

% Set flow: x1' = -x1 - 2, x2' = x1 - x2 - 5 gc' = 1
flow_3 = [-1 0 0 -2; 1 -1 0 -5; 0 0 0 1; 0 0 0 0];
loc_3.setFlow(flow_3);

% Set inv: x1 >= -1 & x2 >= 0 & gc <= timeHorizon
inv_3 = MHyProCondition([-1 0 0; 0 -1 0; 0 0 1], [1; 0; timeHorizon]);
loc_3.setInvariant(inv_3);

%-----------------------------------------------%
%              Location loc4
%-----------------------------------------------%
loc_4 = MHyProLocation();
loc_4.setName('loc4');

% Set flow: x1' = -x1 + 3, x2' = x1 - x2 - 5 gc' = 1
flow4 = [-1 0 0 3; 1 -1 0 -5; 0 0 0 1; 0 0 0 0];
loc_4.setFlow(flow4);

% Set inv: x1 <= 1 & x2 >= 0 & gc <= timeHorizon
inv_4 = MHyProCondition([1 0 0; 0 -1 0; 0 0 1], [1; 0; timeHorizon]);
loc_4.setInvariant(inv_4);

%-----------------------------------------------%
%              Location sink
%-----------------------------------------------%
sink = MHyProLocation();
sink.setName('sink');
sink.setFlow(zeros(3));


l1 = automaton.addLocation(loc_1);
l2 = automaton.addLocation(loc_2);
l3 = automaton.addLocation(loc_3);
l4 = automaton.addLocation(loc_4);
s = automaton.addLocation(sink);

%-----------------------------------------------%
%              loc1 --> loc2
%-----------------------------------------------%

tran1 = MHyProTransition();
% x1 = -1
guard1 = MHyProCondition();
guardVector = [-1; 1];
guardMatrix = [1 0 0; -1 0 0];
guard1.setMatrix(guardMatrix);
guard1.setVector(guardVector);
tran1.setAggregation(aggr);
tran1.setGuard(guard1);
tran1.setReset(dummy_reset);
tran1.setSource(l1);
tran1.setTarget(l2);
tran1.setLabels({MHyProLabel('tran1')});
l1.addTransition(tran1);


%-----------------------------------------------%
%              loc1 --> loc3
%-----------------------------------------------%

tran2 = MHyProTransition();
% x2 = 1
guard2 = MHyProCondition();
guardVector = [1; -1];
guardMatrix = [0 1 0; 0 -1 0];
guard2.setMatrix(guardMatrix);
guard2.setVector(guardVector);
tran2.setAggregation(aggr);
tran2.setGuard(guard2);
tran2.setReset(dummy_reset);
tran2.setSource(l1);
tran2.setTarget(l3);
tran2.setLabels({MHyProLabel('tran2')});

l1.addTransition(tran2);

%-----------------------------------------------%
%              loc2 --> loc3
%-----------------------------------------------%

tran3 = MHyProTransition();
% x2 = 1
guard3 = MHyProCondition();
guardVector = [1; -1];
guardMatrix = [0 1 0; 0 -1 0];
guard3.setMatrix(guardMatrix);
guard3.setVector(guardVector);
tran3.setAggregation(aggr);
tran3.setReset(dummy_reset);
tran3.setGuard(guard3);
tran3.setSource(l2);
tran3.setTarget(l3);
tran3.setLabels({MHyProLabel('tran3')});

l2.addTransition(tran3);

%-----------------------------------------------%
%              loc3--> loc1
%-----------------------------------------------%

tran4 = MHyProTransition();
% x2 = 0
guard4 = MHyProCondition();
guardVector = [0; 0];
guardMatrix = [0 1 0; 0 -1 0];
guard4.setMatrix(guardMatrix);
guard4.setVector(guardVector);

tran4.setAggregation(aggr);
tran4.setReset(dummy_reset);
tran4.setGuard(guard4);
tran4.setSource(l3);
tran4.setTarget(l1);
tran4.setLabels({MHyProLabel('tran4')});

l3.addTransition(tran4);

%-----------------------------------------------%
%              loc3 --> loc4
%-----------------------------------------------%

tran5 = MHyProTransition();
% x1 = -1
guard5 = MHyProCondition();
guardVector = [-1; 1];
guardMatrix = [1 0 0; -1 0 0];
guard5.setMatrix(guardMatrix);
guard5.setVector(guardVector);
tran5.setAggregation(aggr);
tran5.setGuard(guard5);
tran5.setReset(dummy_reset);
tran5.setSource(l3);
tran5.setTarget(l4);
tran5.setLabels({MHyProLabel('tran5')});

l3.addTransition(tran5);

%-----------------------------------------------%
%              loc4 --> loc3
%-----------------------------------------------%

tran6 = MHyProTransition();
% x1 = 1
guard6 = MHyProCondition();
guardVector = [1; -1];
guardMatrix = [1 0 0; -1 0 0];
guard6.setMatrix(guardMatrix);
guard6.setVector(guardVector);
tran6.setAggregation(aggr);
tran6.setGuard(guard6);
tran6.setReset(dummy_reset);
tran6.setSource(l4);
tran6.setTarget(l3);
tran6.setLabels({MHyProLabel('tran6')});

l4.addTransition(tran6);

%-----------------------------------------------%
%              loc4 --> loc2
%-----------------------------------------------%

tran7 = MHyProTransition();
% x2 = 0
guard7 = MHyProCondition();
guardVector = [0; 0];
guardMatrix = [0 1 0; 0 -1 0];
guard7.setMatrix(guardMatrix); 
guard7.setVector(guardVector);
tran7.setAggregation(aggr);
tran7.setGuard(guard7);
tran7.setReset(dummy_reset);
tran7.setSource(l4);
tran7.setTarget(l2);
tran7.setLabels({MHyProLabel('tran7')});

l4.addTransition(tran7);

%-----------------------------------------------%
%              loc1 --> sink
%-----------------------------------------------%

% 
sink_guard = MHyProCondition();
guardVector = [-timeHorizon; timeHorizon];
guardMatrix = [0 0 -1; 0 0 1];
sink_guard.setMatrix(guardMatrix); 
sink_guard.setVector(guardVector);

tran1s = MHyProTransition();
tran1s.setAggregation(0);
tran1s.setGuard(sink_guard);
tran1s.setReset(dummy_reset);
tran1s.setSource(l1);
tran1s.setTarget(s);
tran1s.setLabels({MHyProLabel('tran1s')});

l1.addTransition(tran1s);

%-----------------------------------------------%
%              loc2 --> sink
%-----------------------------------------------%

tran2s = MHyProTransition();
tran2s.setAggregation(0);
tran2s.setGuard(sink_guard);
tran2s.setReset(dummy_reset);
tran2s.setSource(l2);
tran2s.setTarget(s);
tran2s.setLabels({MHyProLabel('tran2s')});

l2.addTransition(tran2s);

%-----------------------------------------------%
%              loc3 --> sink
%-----------------------------------------------%

tran3s = MHyProTransition();
tran3s.setAggregation(0);
tran3s.setGuard(sink_guard);
tran3s.setReset(dummy_reset);
tran3s.setSource(l3);
tran3s.setTarget(s);
tran3s.setLabels({MHyProLabel('tran3s')});

l3.addTransition(tran3s);

%-----------------------------------------------%
%              loc4 --> sink
%-----------------------------------------------%

tran4s = MHyProTransition();
tran4s.setAggregation(0);
tran4s.setGuard(sink_guard);
tran4s.setReset(dummy_reset);
tran4s.setSource(l4);
tran4s.setTarget(s);
tran4s.setLabels({MHyProLabel('tran4s')});

l4.addTransition(tran4s);


%-----------------------------------------------%
%                 Bad States
%-----------------------------------------------%


if bad
    if diff == 1
        %easy
%         badState = MHyProCondition();
%         badState.setMatrix([0 1 0]);
%         badState.setVector(-0.7);
%         badStates(1).loc = l1;
%         badStates(1).cond = badState;
%         badStates(2).loc = l2;
%         badStates(2).cond = badState;
%         badStates(3).loc = l3;
%         badStates(3).cond = badState;
%         badStates(4).loc = l4;
%         badStates(4).cond = badState;
        %easy: x2 >= -0.7
            spec = [0 -1 0 0.7];
    elseif diff == 2
        %medium
%         badState = MHyProCondition();
%         badState.setMatrix([0 1 0]);
%         badState.setVector(-0.7);
%         badStates(1).loc = l1;
%         badStates(1).cond = badState;
%         badStates(2).loc = l2;
%         badStates(2).cond = badState;
%         badStates(3).loc = l3;
%         badStates(3).cond = badState;
%         badStates(4).loc = l4;
%         badStates(4).cond = badState;
        %medium: x2 >= -0.7
            spec = [0 -1 0 0.7];
    elseif diff == 3
        %hard
%         badState = MHyProCondition();
%         badState.setMatrix([0 1 0]);
%         badState.setVector(-0.7);
%         badStates(1).loc = l1;
%         badStates(1).cond = badState;
%         badStates(2).loc = l2;
%         badStates(2).cond = badState;
%         badStates(3).loc = l3;
%         badStates(3).cond = badState;
%         badStates(4).loc = l4;
%         badStates(4).cond = badState;
        %hard: x2 >= -0.5068
            spec = [0 -1 0 0.5068];
    elseif diff == 4
        %spec
%         badState = MHyProCondition();
%         badState.setMatrix([1 0 0]);
%         badState.setVector(-1);
%         badStates(1).loc = l1;
%         badStates(1).cond = badState;
%         badStates(2).loc = l2;
%         badStates(2).cond = badState;
%         badStates(3).loc = l3;
%         badStates(3).cond = badState;
%         badStates(4).loc = l4;
%         badStates(4).cond = badState;
        %spec_ x1 >= -1
            spec= [-1 0 0 1];
    end
    %automaton.setLocalBadStates(badStates); 
end

%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% x1 = [1.5, 2.5] x2 = [1, 1] gc = [0 0]
boxVector = [2.5; -1.5; 1; -1; 0; 0];
boxMatrix = [1 0 0; -1 0 0; 0 1 0; 0 -1 0; 0 0 1; 0 0 -1];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(l3, initialCond);

%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

% Add basic settings
settings.timeBound = 2;
settings.jumpDepth = 2;

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
        safe = reach.verify(flowpipes, spec);
%     safe = 1 - reach.reachedBadStates();
    verificationTime = toc;
end

time = reachabilityTime + verificationTime;
% disp(['Time needed for reachability: ', num2str(reachabilityTime)]);
% disp(['Time needed for verification: ', num2str(verificationTime)]);
% disp(['Overall time needed: ', num2str(time)]);

if plotting == 1
    dim = [1 2];
    labs = ["x1", "x2"];
    ext = 'png';
    reach.plot(flowpipes, dim, labs,saveFig,savePath,figName,ext);
    set(gca,'FontSize',15);
    if bad
        if diff == 1
            y = [-0.7;-0.7;-1;-1];
            x = [2.5;-1;-1;2.5];
            pgon = polyshape([x,y], 'Simplify', false);
            plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
        elseif diff == 2
            y = [-0.7;-0.7;-1;-1];
            x = [2.5;-1;-1;2.5];
            pgon = polyshape([x,y], 'Simplify', false);
            plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
        elseif diff == 3
            y = [-0.7;-0.7;-1;-1];
            x = [2.5;-1;-1;2.5];
            pgon = polyshape([x,y], 'Simplify', false);
            plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
        elseif diff == 4
            y = [1;1;-1.5;-1.5];
            x = [-1;-1.5;-1.5;-1];
            pgon = polyshape([x,y], 'Simplify', false);
            plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
        end
    end
end

end




