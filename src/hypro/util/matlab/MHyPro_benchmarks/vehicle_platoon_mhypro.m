function [reachabilityTime, verificationTime, time, safe] = vehicle_platoon_mhypro(saveFig, savePath, figName, bad, diff,settings,setRepr,aggr, plotting)

timeHorizon = 12;

% Create Automaton
automaton = MHyProHAutomaton();
dummy_reset = MHyProReset();
dummy_reset.setMatrix(eye(11));
dummy_reset.setVector(zeros(11,1));

%-----------------------------------------------%
%              Location qc
%-----------------------------------------------%
loc_qc = MHyProLocation();
loc_qc.setName('qc');

% [e1, e1prime, a1, e2, e2prime, a2, e3, e3prime, a3, t, gc]

% Set flow: x' = Ac * x & t' = 1 & gc' = 1
Ac = [0 1 0 0 0 0 0 0 0 0 0 0;...
        0 0 -1 0 0 0 0 0 0 0 0 0;...
        1.605 4.868 -3.5754 -0.8198 0.427 -0.045 -0.1942 0.3626 -0.0946 0 0 0;...
        0 0 0 0 1 0 0 0 0 0 0 0;...
        0 0 1 0 0 -1 0 0 0 0 0 0;...
        0.8718 3.814 -0.0754 1.1936 3.6258 -3.2396 -0.595 0.1294 -0.0796 0 0 0;...
        0 0 0 0 0 0 0 1 0 0 0 0;...
        0 0 0 0 0 1 0 0 -1 0 0 0;...
        0.7132 3.573 -0.0964 0.8472 3.2568 -0.0876 1.2726 3.072 -3.1356 0 0 0;...
        0 0 0 0 0 0 0 0 0 0 0 1;...
        0 0 0 0 0 0 0 0 0 0 0 1;...
        0 0 0 0 0 0 0 0 0 0 0 0];

loc_qc.setFlow(Ac);

% Set inv: t <= 2 & gc <= timeHorizon
inv_qc = MHyProCondition([0 0 0 0 0 0 0 0 0 1 0; 0 0 0 0 0 0 0 0 0 0 1], [2;timeHorizon]);
loc_qc.setInvariant(inv_qc);

%-----------------------------------------------%
%              Location qn
%-----------------------------------------------%
loc_qn = MHyProLocation();
loc_qn.setName('qn');

% Set flow: x' = An * x & t' = 1 & gc' = 1
% [e1, e1prime, a1, e2, e2prime, a2, e3, e3prime, a3, t]
An  = [0 1 0 0 0 0 0 0 0 0 0 0;...
        0 0 -1 0 0 0 0 0 0 0 0 0;...
        1.605 4.868 -3.5754 0 0 0 0 0 0 0 0 0;...
        0 0 0 0 1 0 0 0 0 0 0 0;...
        0 0 1 0 0 -1 0 0 0 0 0 0;...
        0 0 0 1.1936 3.6258 -3.2396 0 0 0 0 0 0;...
        0 0 0 0 0 0 0 1 0 0 0 0;...
        0 0 0 0 0 1 0 0 -1 0 0 0;...
        0.7132 3.573 -0.0964 0.8472 3.2568 -0.0876 1.2726 3.072 -3.1356 0 0 0;
        0 0 0 0 0 0 0 0 0 0 0 1;...
        0 0 0 0 0 0 0 0 0 0 0 1;...
        0 0 0 0 0 0 0 0 0 0 0 0];

loc_qn.setFlow(An);

% Set inv: t <= 2  & gc <= timeHorizon
inv_qn = MHyProCondition([0 0 0 0 0 0 0 0 0 1 0; 0 0 0 0 0 0 0 0 0 0 1], [2;timeHorizon]);
loc_qn.setInvariant(inv_qn);

%-----------------------------------------------%
%              Location sink
%-----------------------------------------------%
sink = MHyProLocation();
sink.setName('sink');
sink.setFlow(zeros(11));


qc = automaton.addLocation(loc_qc);
qn = automaton.addLocation(loc_qn);
s = automaton.addLocation(sink);

%-----------------------------------------------%
%              Transitions
%-----------------------------------------------%

% qc --> qn
tran1 = MHyProTransition();
% Set guard: t >= 2
guard1 = MHyProCondition();
guard1.setMatrix([0 0 0 0 0 0 0 0 0 -1 0]);
guard1.setVector(-2);
% Set reset: t := 0
reset = MHyProReset();
temp = eye(11);
temp(10,10) = 0;
reset.setMatrix(temp);
reset.setVector(zeros(11,1));

tran1.setAggregation(aggr);
tran1.setGuard(guard1);
tran1.setSource(qc);
tran1.setTarget(qn);
tran1.setReset(reset);
tran1.setLabels({MHyProLabel('tran1')});

qc.addTransition(tran1);

% qn --> qc
tran2 = MHyProTransition();
% Set guard: t >= 2
guard2 = MHyProCondition();
guard2.setMatrix([0 0 0 0 0 0 0 0 0 -1 0]);
guard2.setVector(-2);

tran2.setAggregation(aggr);
tran2.setGuard(guard2);
tran2.setSource(qn);
tran2.setTarget(qc);
tran2.setReset(reset);
tran2.setLabels({MHyProLabel('tran2')});
qn.addTransition(tran2);

% qn --> sink

sink_guard = MHyProCondition();
sink_guard.setMatrix([0 0 0 0 0 0 0 0 0 0 -1; 0 0 0 0 0 0 0 0 0 0 1]);
sink_guard.setVector([-timeHorizon;timeHorizon]);

tran1s = MHyProTransition();
tran1s.setAggregation(0);
tran1s.setGuard(sink_guard);
tran1s.setSource(qn);
tran1s.setTarget(s);
tran1s.setReset(dummy_reset);
tran1s.setLabels({MHyProLabel('tran1s')});
qn.addTransition(tran1s);

% qc --> sink

tran2s = MHyProTransition();
tran2s.setAggregation(0);
tran2s.setGuard(sink_guard);
tran2s.setSource(qc);
tran2s.setTarget(s);
tran2s.setReset(dummy_reset);
tran2s.setLabels({MHyProLabel('tran2s')});
qc.addTransition(tran2s);

%-----------------------------------------------%
%                 Initial set
%-----------------------------------------------%

% e1 = [0.9 1.1] e1prime = [0.9 1.1] a1 = [0.9 1.1] e2 = [0.9 1.1] e2prime
% =[0.9 1.1] a2 = [0.9 1.1] e3 = [0.9 1.1] e3prime = [0.9 1.1] a3 = [ 0.9 1.1]
% t = [0 0] gc = [0 0]
boxVector = [-0.9 * ones(9,1);0; 0; 1.1*ones(9,1);0;0];
boxMatrix = [-1*eye(11); eye(11)];
         
initialCond = MHyProCondition(boxMatrix, boxVector);
automaton.addInitialState(qc, initialCond);

%-----------------------------------------------%
%                 Bad States
%-----------------------------------------------%

% unsafe: e1 >= 1.7 in qc and qn

if bad
    if diff == 1
%         %easy
%         badState = MHyProCondition();
%         badState.setMatrix([-1 0 0 0 0 0 0 0 0 0 0 0]); 
%         badState.setVector(-1.7);
%         badStates(1).loc = qc;
%         badStates(1).cond = badState;
%         badStates(2).loc = qn;
%         badStates(2).cond = badState;
        %easy: e1 <= 1.7
            spec = [1 0 0 0 0 0 0 0 0 0 0 1.7];
    elseif diff == 2
        %medium
%         badState = MHyProCondition();
%         badState.setMatrix([-1 0 0 0 0 0 0 0 0 0 0 0]); 
%         badState.setVector(-1.66815);
%         badStates(1).loc = qc;
%         badStates(1).cond = badState;
%         badStates(2).loc = qn;
%         badStates(2).cond = badState;
        %medium: e1 <= 1.66815
            spec = [1 0 0 0 0 0 0 0 0 0 0 1.66815];
    elseif diff == 3
        %hard
%         badState = MHyProCondition();
%         badState.setMatrix([-1 0 0 0 0 0 0 0 0 0 0 0]); 
%         badState.setVector(-1.6363);
%         badStates(1).loc = qc;
%         badStates(1).cond = badState;
%         badStates(2).loc = qn;
%         badStates(2).cond = badState;
        %hard: e1 <= 1.6363
            spec = [1 0 0 0 0 0 0 0 0 0 0 1.6363];
    elseif diff == 4
        %hard
%         badState = MHyProCondition();
%         badState.setMatrix([-0.7 0 0 0 0 0 -1 0 0 0 0 0]); 
%         badState.setVector(0.05);
%         badStates(1).loc = qc;
%         badStates(1).cond = badState;
%         badStates(2).loc = qn;
%         badStates(2).cond = badState;
        %spec: 0.855e1 +e3 <= -0.05
            spec = [0.855 0 0 0 0 0 1 0 0 0 0 -0.05];
    end
    %automaton.setLocalBadStates(badStates);
end


%-----------------------------------------------%
%                 Reachability
%-----------------------------------------------%

% Add basic settings
settings.timeBound = 5;
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

if plotting == 1
    dim = [1 7];
    labs = ["e1", "e3"];
    ext = 'png';
    reach.plot(flowpipes, dim, labs,saveFig,savePath,figName,ext);
    if bad
        if diff == 0
            y = [2;2;1.7;1.7];
            x = [1.8;0;0;1.8];
            pgon = polyshape([x,y], 'Simplify', false);
            plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
        elseif diff == 1
            y = [-0.7;-0.7;-1;-1];
            x = [2.5;-1;-1;2.5];
            pgon = polyshape([x,y], 'Simplify', false);
            plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
        else
            y = [2;2;1.7;1.7];
            x = [1.8;0;0;1.8];
            pgon = polyshape([x,y], 'Simplify', false);
            plot(pgon,'FaceColor',[0.831, 0, 0], 'FaceAlpha',0.5,'EdgeColor', 'none');
        end
    end
elseif plotting == 2
    dim = [1 7 10];
    labs = ["e1", "e3", "t"];
    ext = 'png';
    reach.plot3D(flowpipes, dim, labs,saveFig,savePath,figName,ext);
end

end

