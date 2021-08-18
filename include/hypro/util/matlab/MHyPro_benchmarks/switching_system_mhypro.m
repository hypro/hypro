function [reachabilityTime, verificationTime, time, safe] = switching_system_mhypro(saveFig, savePath, figName, bad, diff,settings,setRepr,aggr, plotting)

% vars: [x1,x2,x3,x4,x5,gc]

timeHorizon = 1;

% Create Automaton
automaton = MHyProHAutomaton();
dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(6));
dummy_reset.setVector([0; 0; 0; 0; 0; 0]);

%-----------------------------------------------%
%              Location loc1
%-----------------------------------------------%
loc_1 = MHyProLocation();
loc_1.setName('loc1');

% Set flow:
% x1' = -0.8047*x1 + 8.7420*x2 - 2.4591*x3 - 8.2714*x4 - 1.8640*x5
% x2' = -8.6329*x1 - 0.5860*x2 - 2.1006*x3 + 3.6035*x4 - 1.8423*x5
% x3' = 2.4511*x1 + 2.2394*x2 - 0.7538*x3 - 3.6934*x4 + 2.4585*x5
% x4' = 8.3858*x1 - 3.1739*x2 + 3.7822*x3 - 0.6249*x4 + 1.8829*x5
% x5' = 1.8302*x1 + 1.9869*x2 - 2.4539*x3 - 1.7726*x4 - 0.7911*x5
% gc' = 1

flow_1 = [-0.8047,8.7420,-2.4591,-8.2714,-1.8640, 0, 0;...
-8.6329,-0.58560,-2.1006,3.60345,-1.8423, 0, 0;...
2.4511,2.23948,-0.7538,-3.6934,2.4585, 0, 0;...
8.3858,-3.1739,3.7822,-0.6249,1.8829, 0, 0;...
1.8302,1.9869,-2.4539,-1.7726,-0.7911, 0, 0;...
0,0,0,0,0,0,1; 0,0,0,0,0,0,0];

loc_1.setFlow(flow_1);

% Set inv: x1 >= 3 & gc <= timeHorizon
inv_1 = MHyProCondition([-1,0,0,0,0,0;0,0,0,0,0,1], [-3;timeHorizon]);
loc_1.setInvariant(inv_1);


%-----------------------------------------------%
%              Location loc2
%-----------------------------------------------%
loc_2 = MHyProLocation();
loc_2.setName('loc2');

% Set flow:
%     x1' = -0.8316*x1 + 8.7658*x2 - 2.4744*x3 - 8.2608*x4 - 1.9033*x5
%     x2' = -0.8316*x1 - 0.5860*x2 - 2.1006*x3 + 3.6035*x4 - 1.8423*x5
%     x3' = 2.4511*x1 + 2.2394*x2 - 0.7538*x3 - 3.6934*x4 + 2.4585*x5
%     x4' = 8.3858*x1 - 3.1739*x2 + 3.7822*x3 - 0.6249*x4 + 1.8829*x5
%     x5' = 1.5964*x1 + 2.1936*x2 - 2.5872*x3 - 1.6812*x4 - 1.1324*x5
% gc' = 1
flow_2 = [-0.8316,8.7658,-2.4744,-8.2608,-1.9033,0,0;...
-0.8316,-0.5860,-2.1006,3.6035,-1.84230,0,0;...
2.4511,2.2394,-0.7538,-3.6934,2.4585,0,0;...
8.3858,-3.1739,3.7822,-0.6249,1.8829,0,0;...
1.5964,2.1936,-2.5872,-1.6812,-1.1324,0,0;...
0,0,0,0,0,0,1;0,0,0,0,0,0,0];

loc_2.setFlow(flow_2);

% Set inv: x1 >= 2 & gc <= timeHorizon
inv_2 = MHyProCondition([-1,0,0,0,0,0;0,0,0,0,0,1], [-2;timeHorizon]);
loc_2.setInvariant(inv_2);


%-----------------------------------------------%
%              Location loc3
%-----------------------------------------------%
loc_3 = MHyProLocation();
loc_3.setName('loc3');

% Set flow:
% x1' = -0.9275*x1 + 8.8628*x2 - 2.5428*x3 - 8.2329*x4 - 2.0324*x5
% x2' = -0.8316*x1 - 0.5860*x2 - 2.1006*x3 + 3.6035*x4 - 1.8423*x5
% x3' = 2.4511*x1 + 2.2394*x2 - 0.7538*x3 - 3.6934*x4 + 2.4585*x5
% x4' = 8.3858*x1 - 3.1739*x2 + 3.7822*x3 - 0.6249*x4 + 1.8829*x5
% x5' = 0.7635*x1 + 3.0357*x2 - 3.1814*x3 - 1.4388*x4 - 2.2538*x5
% gc' = 1
flow_3 = [-0.9275,8.8628,-2.5428,-8.2329,-2.0324,0,0;...
-0.8316,-0.5860,-2.1006,3.6035,-1.8423,0,0;...
2.4511,2.2394,-0.7538,-3.6934,2.4585,0,0;...
8.3858,-3.1739,3.7822,-0.6249,1.8829,0,0;...
0.7635,3.0357,-3.1814,-1.4388,-2.2538,0,0;...
0,0,0,0,0,0,1;0,0,0,0,0,0,0];


loc_3.setFlow(flow_3);
% Set inv: x1 >= 1 & gc <= timeHorizon
inv_3 = MHyProCondition([-1 0 0 0 0 0; 0 0 0 0 0 1], [-1;timeHorizon]);
loc_3.setInvariant(inv_3);


%-----------------------------------------------%
%              Location loc4
%-----------------------------------------------%
loc_4 = MHyProLocation();
loc_4.setName('loc4');

% Set flow:
%   x1' == -1.4021*x1 + 10.1647*x2 - 3.3937*x3 - 8.5139*x4 - 2.9602*x5
%   x2' == -0.8316*x1 - 0.5860*x2 - 2.1006*x3 + 3.6035*x4 - 1.8423*x5
%   x3' == 2.4511*x1 + 2.2394*x2 - 0.7538*x3 - 3.6934*x4 + 2.4585*x5
%   x4' == 8.3858*x1 - 3.1739*x2 + 3.7822*x3 - 0.6249*x4 + 1.8829*x5 &
%   x5' == -3.3585*x1 + 14.3426*x2 - 10.5703*x3 - 3.8785*x4 - 10.3111*x5
% gc' = 1
flow_4 = [-1.4021,10.1647,-3.3937,-8.5139,-2.9602,0,0;...
-0.8316,-0.5860,-2.1006,3.6035,-1.8423,0,0;...
2.4511,2.2394,-0.7538,-3.6934,2.4585,0,0;
8.3858,-3.1739,3.7822,-0.6249,1.8829,0,0;...
-3.3585,14.3426,-10.5703,-3.8785,-10.3111,0,0;...
0,0,0,0,0,0,1;0,0,0,0,0,0,0];


loc_4.setFlow(flow_4);
% Set inv: x1 >= 0 & gc <= timeHorizon
inv_4 = MHyProCondition([-1 0 0 0 0 0; 0 0 0 0 0 1], [0;timeHorizon]);
loc_4.setInvariant(inv_4);


%-----------------------------------------------%
%              Location loc5
%-----------------------------------------------%
loc_5 = MHyProLocation();
loc_5.setName('loc5');

% Set flow:
%     x1' = -1.4021*x1 + 10.1647*x2 - 3.3937*x3 - 8.5139*x4 - 2.9602*x5
%     x2' = -0.8316*x1 - 0.5860*x2 - 2.1006*x3 + 3.6035*x4 - 1.8423*x5
%     x3' = 2.4511*x1 + 2.2394*x2 - 0.7538*x3 - 3.6934*x4 + 2.4585*x5
%     x4' = 8.3858*x1 - 3.1739*x2 + 3.7822*x3 - 0.6249*x4 + 1.8829*x5
%     x5' = -3.3585*x1 + 14.3426*x2 - 10.5703*x3 - 3.8785*x4 - 10.3111*x5
% gc' = 1
    
flow_5 = [-1.4021,10.1647,-3.3937,-8.5139,-2.9602,0,0;...
-0.83160,-0.5860,-2.1006,3.6035,-1.8423,0,0;...
2.4511,2.2394,-0.7538,-3.6934,2.4585,0,0;...
8.3858,-3.1739,3.7822,-0.6249,1.8829,0,0;...
-3.3585,14.3426,-10.5703,-3.8785,-10.3111,0,0;...
0,0,0,0,0,0,1;0,0,0,0,0,0,0];

loc_5.setFlow(flow_5);
% Set inv: x1 <= 1 & gc <= timeHorizon
inv_5 = MHyProCondition([1 0 0 0 0 0; 0 0 0 0 0 1], [1;timeHorizon]);
loc_5.setInvariant(inv_5);

%-----------------------------------------------%
%              Location sink
%-----------------------------------------------%
sink = MHyProLocation();
sink.setName('sink');
sink.setFlow(zeros(6));

%-----------------------------------------------%
%              Add locations to HA
%-----------------------------------------------%

l1 = automaton.addLocation(loc_1);
l2 = automaton.addLocation(loc_2);
l3 = automaton.addLocation(loc_3);
l4 = automaton.addLocation(loc_4);
l5 = automaton.addLocation(loc_5);
s = automaton.addLocation(sink);

%-----------------------------------------------%
%              loc1 --> loc2
%-----------------------------------------------%
tran1 = MHyProTransition();
% Set guard: x1 = 3 
guard1 = MHyProCondition();
guard1.setMatrix([-1,0,0,0,0,0;1,0,0,0,0,0]); 
guard1.setVector([-3;3]);

tran1.setAggregation(aggr);
tran1.setGuard(guard1);
tran1.setSource(l1);
tran1.setTarget(l2);
tran1.setReset(dummy_reset);
tran1.setLabels({MHyProLabel('tran1')});

l1.addTransition(tran1);

%-----------------------------------------------%
%              loc2 --> loc3
%-----------------------------------------------%
tran2 = MHyProTransition();
% Set guard: x1 = 2 
guard2 = MHyProCondition();
guard2.setMatrix([-1,0,0,0,0,0;1,0,0,0,0,0]); 
guard2.setVector([-2;2]);

tran2.setAggregation(aggr);
tran2.setGuard(guard2);
tran2.setSource(l2);
tran2.setTarget(l3);
tran2.setReset(dummy_reset);
tran2.setLabels({MHyProLabel('tran2')});

l2.addTransition(tran2);

%-----------------------------------------------%
%              loc3 --> loc4
%-----------------------------------------------%
tran3 = MHyProTransition();
% Set guard: x1 = 1 
guard3 = MHyProCondition();
guard3.setMatrix([1 0 0 0 0 0; -1 0 0 0 0 0]); 
guard3.setVector([1;-1]);

tran3.setAggregation(aggr);
tran3.setGuard(guard3);
tran3.setSource(l3);
tran3.setTarget(l4);
tran3.setReset(dummy_reset);
tran3.setLabels({MHyProLabel('tran3')});

l3.addTransition(tran3);

%-----------------------------------------------%
%              loc4 --> loc5
%-----------------------------------------------%
tran4 = MHyProTransition();
% Set guard: x1 = 0 
guard4 = MHyProCondition();
guard4.setMatrix([-1,0,0,0,0,0;1,0,0,0,0,0]); 
guard4.setVector([0;0]);

tran4.setAggregation(aggr);
tran4.setGuard(guard4);
tran4.setSource(l4);
tran4.setTarget(l5);
tran4.setReset(dummy_reset);
tran4.setLabels({MHyProLabel('tran4')});

l4.addTransition(tran4);

%-----------------------------------------------%
%              loc1 --> sink
%-----------------------------------------------%

% Set guard: gc == timeHorizon
sink_guard = MHyProCondition();
sink_guard.setMatrix([-1,0,0,0,0,0;1,0,0,0,0,0]); 
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
%              loc2 --> sink
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
%              loc3 --> sink
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
%              loc4 --> sink
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
%              loc5 --> sink
%-----------------------------------------------%

tran5s = MHyProTransition();
tran5s.setAggregation(0);
tran5s.setGuard(sink_guard);
tran5s.setSource(l5);
tran5s.setTarget(s);
tran5s.setReset(dummy_reset);
tran5s.setLabels({MHyProLabel('tran5s')});

l5.addTransition(tran5s);

%-----------------------------------------------%
%                 Bad States
%-----------------------------------------------%

if bad
    if diff == 1
        %easy
%         badState = MHyProCondition();
%         badState.setMatrix([0 0 -1 0 0 0]);
%         badState.setVector(-1.5);
%         badStates(1).loc = l1;
%         badStates(1).cond = badState;
%         badStates(2).loc = l2;
%         badStates(2).cond = badState;
%         badStates(3).loc = l3;
%         badStates(3).cond = badState;
%         badStates(4).loc = l4;
%         badStates(4).cond = badState;
%         badStates(5).loc = l5;
%         badStates(5).cond = badState;
        %easy: x3 <= 1.5
        spec = [0 0 1 0 0 0 1.5];
    elseif diff == 2
        %medium
%         badState = MHyProCondition();
%         badState.setMatrix([0 0 -1 0 0 0]);
%         badState.setVector(-1.4942);
%         badStates(1).loc = l1;
%         badStates(1).cond = badState;
%         badStates(2).loc = l2;
%         badStates(2).cond = badState;
%         badStates(3).loc = l3;
%         badStates(3).cond = badState;
%         badStates(4).loc = l4;
%         badStates(4).cond = badState;
%         badStates(5).loc = l5;
%         badStates(5).cond = badState;
        %medium: x3 <= 1.4942
        spec = [0 0 1 0 0 0 1.4942];
    elseif diff == 3
        %hard
%         badState = MHyProCondition();
%         badState.setMatrix([0 0 -1 0 0 0]);
%         badState.setVector(-1.4884);
%         badStates(1).loc = l1;
%         badStates(1).cond = badState;
%         badStates(2).loc = l2;
%         badStates(2).cond = badState;
%         badStates(3).loc = l3;
%         badStates(3).cond = badState;
%         badStates(4).loc = l4;
%         badStates(4).cond = badState;
%         badStates(5).loc = l5;
%         badStates(5).cond = badState;
         %hard: x3 <= 1.4884
        spec = [0 0 1 0 0 0 1.4884];
    elseif diff == 4
%         badState = MHyProCondition();
%         badState.setMatrix([-0.17 0 -1 0 0 0]);
%         badState.setVector(-0.53);
%         badStates(1).loc = l1;
%         badStates(1).cond = badState;
%         badStates(2).loc = l2;
%         badStates(2).cond = badState;
%         badStates(3).loc = l3;
%         badStates(3).cond = badState;
%         badStates(4).loc = l4;
%         badStates(4).cond = badState;
        spec = [-0.18 0 1 0 0 0 -0.615];
    end
  %  automaton.setLocalBadStates(badStates);
end


%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% x1 = [3.1, 3.1] x2 = [4,4] x3 = [0,0] x4 = [0,0] x5 = [0,0] gc = [0,0]
boxVector = [3.1;4;0;0;0;0;-3.1;-4;0;0;0;0];
boxMatrix = [eye(6);-1*eye(6)];
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(l1, initialCond);

%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%


% Add basic settings
settings.timeBound = 1;
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
end

time = reachabilityTime + verificationTime;
% disp(['Time needed for reachability: ', num2str(reachabilityTime)]);
% disp(['Time needed for verification: ', num2str(verificationTime)]);
% disp(['Overall time needed: ', num2str(time)]);

if plotting == 1
    dim = [1 3];
    labs = ["x1", "x3"];
    ext = 'png';
    reach.plot(flowpipes, dim, labs,saveFig,savePath,figName,ext);
    set(gca,'FontSize',15);
    if bad
        if diff == 1
            y = [2;2;1.5;1.5];
            x = [4;-2;-2;4];
            pgon = polyshape([x,y], 'Simplify', false);
            plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
        elseif diff == 2
            y = [2;2;1.4942;1.4942];
            x = [4;-2;-2;4];
            pgon = polyshape([x,y], 'Simplify', false);
            plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
        elseif diff == 3
            y = [2;2;1.4884;1.4884];
            x = [4;-2;-2;4];
            pgon = polyshape([x,y], 'Simplify', false);
            plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
        elseif diff == 4
            k = -1.3 : 4;
            spec1 = 0.18*k - 0.61;
            upper = -1 + 0*k;
            hold on;
            k1 = [k, fliplr(k)];
            inBetweenUpper = [spec1, fliplr(upper)];
            fill(k1,inBetweenUpper,[0.831, 0, 0], 'FaceAlpha',0.5, 'EdgeColor','none');
        end
    end
elseif plotting == 2
    dim = [1 2 3];
    labs = ["x1", "x2", "x3"];
    ext = 'png';
    reach.plot3D(flowpipes, dim, labs,saveFig,savePath,figName,ext);
end

end
