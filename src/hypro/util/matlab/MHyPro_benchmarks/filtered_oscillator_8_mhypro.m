function [reachabilityTime, verificationTime, time, safe] = filtered_oscillator_8_mhypro(saveFig, savePath, figName, bad, diff,settings,setRepr,aggr, plotting)

% vars = [x,y,f4a_x1,f4a_x2,f4a_x3,f8_x1,f4b_x1,f4b_x2,f4b_x3,z,gc]
timeHorizon = 4;

% Create Automaton
automaton = MHyProHAutomaton();
dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(11));
dummy_reset.setVector(zeros(11,1));

%-----------------------------------------------%
%              Location loc1
%-----------------------------------------------%
loc1 = MHyProLocation();
loc1.setName('loc1');

% Set flow:
flow_loc1 = [-2 0 0 0 0 0 0 0 0 0 0 1.4;...
             0 -1 0 0 0 0 0 0 0 0 0 -0.7;...
             5  0 -5 0 0 0 0 0 0 0 0 0;...
             0 0 5 -5 0 0 0 0 0 0 0 0;...
             0 0 0 5 -5 0 0 0 0 0 0 0;...
             0 0 0 0 5 -5 0 0 0 0 0 0;...
             0 0 0 0 0 5 -5 0 0 0 0 0;...
             0 0 0 0 0 0 5 -5 0 0 0 0;...
             0 0 0 0 0 0 0  5 -5 0 0 0;...
             0 0 0 0 0 0 0 0 5 -5 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 1;...
             0 0 0 0 0 0 0 0 0 0 0 0];
loc1.setFlow(flow_loc1);

% Set inv: x <= 0 & y + 0.714286x >= 0 & gc <= timeHorizon
invMat = [1,0,0,0,0,0,0,0,0,0,0;-0.714286,-1,0,0,0,0,0,0,0,0,0;0,0,0,0,0,0,0,0,0,0,1];
inv_loc1 = MHyProCondition(invMat, [0;0;timeHorizon]);
loc1.setInvariant(inv_loc1);


%-----------------------------------------------%
%              Location loc2
%-----------------------------------------------%
loc2 = MHyProLocation();
loc2.setName('loc2');

flow_loc2 = [-2 0 0 0 0 0 0 0 0 0 0 -1.4;...
             0 -1 0 0 0 0 0 0 0 0 0 0.7;...
             5  0 -5 0 0 0 0 0 0 0 0 0;...
             0 0 5 -5 0 0 0 0 0 0 0 0;...
             0 0 0 5 -5 0 0 0 0 0 0 0;...
             0 0 0 0 5 -5 0 0 0 0 0 0;...
             0 0 0 0 0 5 -5 0 0 0 0 0;...
             0 0 0 0 0 0 5 -5 0 0 0 0;...
             0 0 0 0 0 0 0  5 -5 0 0 0;...
             0 0 0 0 0 0 0 0 5 -5 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 1;...
             0 0 0 0 0 0 0 0 0 0 0 0];
loc2.setFlow(flow_loc2);

% Set inv: x <= 0 & y + 0.714286x <= 0 & gc <= timeHorizon
invMat = [1,0,0,0,0,0,0,0,0,0,0;0.7142869,1,0,0,0,0,0,0,0,0,0;0,0,0,0,0,0,0,0,0,0,1];
inv_loc2 = MHyProCondition(invMat, [0;0;timeHorizon]);
loc2.setInvariant(inv_loc2);

%-----------------------------------------------%
%              Location loc3
%-----------------------------------------------%
loc3 = MHyProLocation();
loc3.setName('loc3');

% Set flow:
flow_loc3 = [-2 0 0 0 0 0 0 0 0 0 0 1.4;...
             0 -1 0 0 0 0 0 0 0 0 0 -0.7;...
             5  0 -5 0 0 0 0 0 0 0 0 0;...
             0 0 5 -5 0 0 0 0 0 0 0 0;...
             0 0 0 5 -5 0 0 0 0 0 0 0;...
             0 0 0 0 5 -5 0 0 0 0 0 0;...
             0 0 0 0 0 5 -5 0 0 0 0 0;...
             0 0 0 0 0 0 5 -5 0 0 0 0;...
             0 0 0 0 0 0 0  5 -5 0 0 0;...
             0 0 0 0 0 0 0 0 5 -5 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 1;...
             0 0 0 0 0 0 0 0 0 0 0 0];
loc3.setFlow(flow_loc3);

% Set inv: x >= 0 & y + 0.714286x >= 0 & gc <= timeHorizon
invMat = [-1,0,0,0,0,0,0,0,0,0,0;-0.714286,-1,0,0,0,0,0,0,0,0,0;0,0,0,0,0,0,0,0,0,0,1];
inv_loc3 = MHyProCondition(invMat, [0;0;timeHorizon]);
loc3.setInvariant(inv_loc3);

%-----------------------------------------------%
%              Location loc4
%-----------------------------------------------%
loc4 = MHyProLocation();
loc4.setName('loc4');

% Set flow: x' = -2x - 1.4 & y' = -y + 0.7 & x1' = 5x - 5x1 &
% x_2' = 5x1 - 5x2 & x3' = 5x2 -  5x3 & z' = 5x3 - 5z & gc' = 1
flow_loc4 = [-2 0 0 0 0 0 0 0 0 0 0 -1.4;...
             0 -1 0 0 0 0 0 0 0 0 0 0.7;...
             5  0 -5 0 0 0 0 0 0 0 0 0;...
             0 0 5 -5 0 0 0 0 0 0 0 0;...
             0 0 0 5 -5 0 0 0 0 0 0 0;...
             0 0 0 0 5 -5 0 0 0 0 0 0;...
             0 0 0 0 0 5 -5 0 0 0 0 0;...
             0 0 0 0 0 0 5 -5 0 0 0 0;...
             0 0 0 0 0 0 0  5 -5 0 0 0;...
             0 0 0 0 0 0 0 0 5 -5 0 0;...
             0 0 0 0 0 0 0 0 0 0 0 1;...
             0 0 0 0 0 0 0 0 0 0 0 0];
loc4.setFlow(flow_loc4);

% Set inv: x >= 0 & y + 0.714286x <= 0 & gc <= timeHorizon
invMat = [-1 0 0 0 0 0 0 0 0 0 0; 0.714286 1 0 0 0 0 0 0 0 0 0; 0 0 0 0 0 0 0 0 0 0 1];
inv_loc4 = MHyProCondition(invMat, [0;0;timeHorizon]);
loc4.setInvariant(inv_loc4);

%-----------------------------------------------%
%              Location sink
%-----------------------------------------------%
sink = MHyProLocation();
sink.setName('sink');

flow_sink = zeros(11);
sink.setFlow(flow_sink);

l1 = automaton.addLocation(loc1);
l2 = automaton.addLocation(loc2);
l3 = automaton.addLocation(loc3);
l4 = automaton.addLocation(loc4);
s = automaton.addLocation(sink);

%-----------------------------------------------%
%              loc1 -> loc3
%-----------------------------------------------%

tran1 = MHyProTransition();
% Set guard: x = 0 & 0.714286x + y >= 0
guardMatrix = [1 0 0 0 0 0 0 0 0 0; -1 0 0 0 0 0 0 0 0 0; -0.714286 -1 0 0 0 0 0 0 0 0];
guard1 = MHyProCondition();
guard1.setMatrix(guardMatrix);
guard1.setVector([0;0;0]);

tran1.setAggregation(aggr);
tran1.setGuard(guard1);
tran1.setSource(l1);
tran1.setTarget(l3);
tran1.setReset(dummy_reset);
tran1.setLabels({MHyProLabel('tran1')});

l1.addTransition(tran1);

%-----------------------------------------------%
%              loc3 -> loc4
%-----------------------------------------------%

tran2 = MHyProTransition();
% Set guard: x >= 0 & 0.714286x + y = 0
guardMatrix = [-1 0 0 0 0 0 0 0 0 0; -0.714286 -1 0 0 0 0 0 0 0 0; 0.714286 1 0 0 0 0 0 0 0 0];
guard2 = MHyProCondition();
guard2.setMatrix(guardMatrix);
guard2.setVector([0;0;0]);

tran2.setAggregation(aggr);
tran2.setGuard(guard2);
tran2.setSource(l3);
tran2.setTarget(l4);
tran2.setReset(dummy_reset);
tran2.setLabels({MHyProLabel('tran2')});

l3.addTransition(tran2);

%-----------------------------------------------%
%              loc4 -> loc2
%-----------------------------------------------%

tran3 = MHyProTransition();
% Set guard: x = 0 & 0.714286x + y <= 0
guardMatrix = [-1 0 0 0 0 0 0 0 0 0; 1 0 0 0 0 0 0 0 0 0; 0.714286 1 0 0 0 0 0 0 0 0];
guard3 = MHyProCondition();
guard3.setMatrix(guardMatrix);
guard3.setVector([0;0;0]);

tran3.setAggregation(aggr);
tran3.setGuard(guard3);
tran3.setSource(l4);
tran3.setTarget(l2);
tran3.setReset(dummy_reset);
tran3.setLabels({MHyProLabel('tran3')});

l4.addTransition(tran3);

%-----------------------------------------------%
%              loc2 -> loc1
%-----------------------------------------------%

tran4 = MHyProTransition();
% Set guard: x <= 0 & 0.714286x + y = 0
guardMatrix = [1,0,0,0,0,0,0,0,0,0;-0.714286,-1,0,0,0,0,0,0,0,0;0.714286,1,0,0,0,0,0,0,0,0];
guard4 = MHyProCondition();
guard4.setMatrix(guardMatrix);
guard4.setVector([0;0;0]);

tran4.setAggregation(aggr);
tran4.setGuard(guard4);
tran4.setSource(l2);
tran4.setTarget(l1);
tran4.setReset(dummy_reset);
tran4.setLabels({MHyProLabel('tran4')});

l2.addTransition(tran4);

%-----------------------------------------------%
%              loc1 -> sink
%-----------------------------------------------%

guardMatrix = [0,0,0,0,0,0,0,0,0,-1;0,0,0,0,0,0,0,0,0,1];
sink_guard = MHyProCondition();
sink_guard.setMatrix(guardMatrix);
sink_guard.setVector([-timeHorizon;timeHorizon]);

tran1s = MHyProTransition();
tran1s.setAggregation(0);
tran1s.setGuard(sink_guard);
tran1s.setSource(l1);
tran1s.setTarget(s);
tran1s.setReset(dummy_reset);
tran1s.setLabels({MHyProLabel('tran1s')});

l1.addTransition(tran1s);

%-----------------------------------------------%
%              loc2 -> sink
%-----------------------------------------------%

tran2s = MHyProTransition();
tran2s.setAggregation(0);
tran2s.setGuard(sink_guard);
tran2s.setSource(l2);
tran2s.setTarget(s);
tran2s.setReset(dummy_reset);
tran2s.setLabels({MHyProLabel('tran2s')});

l2.addTransition(tran2s);

%-----------------------------------------------%
%              loc3 -> sink
%-----------------------------------------------%

tran3s = MHyProTransition();
tran3s.setAggregation(0);
tran3s.setGuard(sink_guard);
tran3s.setSource(l3);
tran3s.setTarget(s);
tran3s.setReset(dummy_reset);
tran3s.setLabels({MHyProLabel('tran3s')});

l3.addTransition(tran3s);

%-----------------------------------------------%
%              loc4 -> sink
%-----------------------------------------------%

tran4s = MHyProTransition();
tran4s.setAggregation(0);
tran4s.setGuard(sink_guard);
tran4s.setSource(l4);
tran4s.setTarget(s);
tran4s.setReset(dummy_reset);
tran4s.setLabels({MHyProLabel('tran4s')});

l4.addTransition(tran4s);

%-----------------------------------------------%
%                 Bad States
%-----------------------------------------------%

% unsafe: y >= 0.5

if bad
    if diff == 1
        %easy
%         badState = MHyProCondition();
%         badState.setMatrix([0 -1 0 0 0 0 0 0 0 0 0]);
%         badState.setVector(-0.5);
%         badStates(1).loc = l1;
%         badStates(1).cond = badState;
%         badStates(2).loc = l2;
%         badStates(2).cond = badState;
%         badStates(3).loc = l3;
%         badStates(3).cond = badState;
%         badStates(4).loc = l4;
%         badStates(4).cond = badState;
%         %easy: y <= 0.5
            spec = [0 1 0 0 0 0 0 0 0 0 0 0.5];
    elseif diff == 2
        %medium
%         badState = MHyProCondition();
%         badState.setMatrix([0 -1 0 0 0 0 0 0 0 0 0]);
%         badState.setVector(-0.4845);
%         badStates(1).loc = l1;
%         badStates(1).cond = badState;
%         badStates(2).loc = l2;
%         badStates(2).cond = badState;
%         badStates(3).loc = l3;
%         badStates(3).cond = badState;
%         badStates(4).loc = l4;
%         badStates(4).cond = badState;
%         %medium: y <= 0.4845
            spec = [0 1 0 0 0 0 0 0 0 0 0 0.4845];
    elseif diff == 3
        %hard
%         badState = MHyProCondition();
%         badState.setMatrix([0 -1 0 0 0 0 0 0 0 0 0]);
%         badState.setVector(-0.469);
%         badStates(1).loc = l1;
%         badStates(1).cond = badState;
%         badStates(2).loc = l2;
%         badStates(2).cond = badState;
%         badStates(3).loc = l3;
%         badStates(3).cond = badState;
%         badStates(4).loc = l4;
%         badStates(4).cond = badState;
         %hard: y <= 0.469
          spec = [0 1 0 0 0 0 0 0 0 0 0 0.469];
    elseif diff == 4
        %special 0.8*x1 + y <= 0.566
%         badState = MHyProCondition();
%         badState.setMatrix([0 -1 -0.8 0 0 0 0]);
%         badState.setVector(-0.566);
%         badStates(1).loc = l1;
%         badStates(1).cond = badState;
%         badStates(2).loc = l2;
%         badStates(2).cond = badState;
%         badStates(3).loc = l3;
%         badStates(3).cond = badState;
%         badStates(4).loc = l4;
%         badStates(4).cond = badState;
        spec = [0 1 0 0 0 0.8 0 0 0 0 0 0.566];
    end

    %automaton.setLocalBadStates(badStates);
end


%-----------------------------------------------%
%              Initial Set
%-----------------------------------------------%
% x = [0.2, 0.3], y = [-0.1, 0.1] z,f4a_x1,f4a_x2,f4a_x3,f8_x1
%   f4b_x1,f4b_x2,f4b_x3,gc = 0
boxVector = [0.3; 0.1;0;0;0;0;0;0;0;0;0;-0.2;0.1;0;0;0;0;0;0;0;0;0];
boxMatrix = [eye(11); -1*eye(11)];
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
    safe = reach.verify(flowpipes, spec);
%     safe = 1 - reach.reachedBadStates();
    verificationTime = toc;
    else

end



time = reachabilityTime + verificationTime;
% disp(['Time needed for reachability: ', num2str(reachabilityTime)]);
% disp(['Time needed for verification: ', num2str(verificationTime)]);
% disp(['Overall time needed: ', num2str(time)]);

if plotting == 1
    dim = [2 6];
    labs = ["y", "f8x1"];
    ext = 'png';
    reach.plot(flowpipes, dim, labs,saveFig,savePath,figName,ext);
    fplot(@(x) -0.714286*x, [0 0.8],'g');
    set(gca,'FontSize',15);
    if bad
        if diff == 1
            x = [0.8;0.8;0.5;0.5];
            y = [1;-1;-1;1];
            pgon = polyshape([x,y], 'Simplify', false);
            plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
        elseif diff == 2
            x = [0.8;0.8;0.4845;0.4845];
            y = [1;-1;-1;1];
            pgon = polyshape([x,y], 'Simplify', false);
            plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
        elseif diff == 3
            x = [0.8;0.8;0.469;0.469];
            y = [1;-1;-1;1];
            pgon = polyshape([x,y], 'Simplify', false);
            plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
        elseif diff == 4
            k = -0.6 : 1;
            spec1 = -0.8*k + 0.566;
            upper = 1.1 + 0*k;
            hold on;
            k1 = [k, fliplr(k)];
            inBetweenUpper = [spec1, fliplr(upper)];
            fill(k1,inBetweenUpper,[0.831, 0, 0], 'FaceAlpha',0.5, 'EdgeColor','none');
        end
    end
elseif plotting == 2
    dim = [1 2 6];
    labs = ["x", "y", "f8x1"];
    ext = 'png';
    reach.plot3D(flowpipes, dim, labs,saveFig,savePath,figName,ext);
end

end